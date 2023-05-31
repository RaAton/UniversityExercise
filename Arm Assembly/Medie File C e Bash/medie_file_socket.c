#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <math.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <time.h>
#include <sys/wait.h>

#include "unboundedqueue.h"

#define MAX_NUM_ARGS 3
#define MAX_LUN_PATH 256

//Macro per controllare gli errori
#define ec_1(s,m) \
    if ( (s) == 1) {perror(m); exit(EXIT_FAILURE);} 


//struttura da passare nel socket
typedef struct dati{
    char path[MAX_LUN_PATH];
    int n;
    double media;
    double devstd;
}dati_t;

//struttura da passare come argomento della funzione del thread
typedef struct arg{
    Queue_t*q;
    int*sockfd;
    pthread_mutex_t* mutex;
}arg_t;

int generaporta();
double calcmedia(double *valori, int n);
double calcdevstd(double *valori, int n, double media);
int contaelementi(FILE*fp);
double* inseriscivalori(FILE*fp,int n);


//scorrimento della directory
void scorriDir(char*path, Queue_t *q){
    DIR *dir;
    struct dirent *ent;

    //apro la directory, errore se non è directory
    dir = opendir(path);
    ec_1(dir == NULL,"Errore nella opendir");

    //scorro la directory
    while((ent = readdir(dir))){

        //se è una directory diversa da . e .. la scorro ricorsivamente
        if(ent->d_type == DT_DIR && strcmp(ent->d_name,".") != 0 && strcmp(ent->d_name,"..") != 0){
            char*new_path = malloc(sizeof(char)*MAX_LUN_PATH);
            strcpy(new_path,path);
            strcat(new_path,"/");
            strcat(new_path,ent->d_name);
            scorriDir(new_path,q);
        //se è un file .dat lo inserisco nella coda
        }else if(ent->d_type == DT_REG && strstr(ent->d_name,".dat")!=NULL){
            char*new_path = malloc(sizeof(char)*MAX_LUN_PATH);
            strcpy(new_path,path);
            strcat(new_path,"/");
            strcat(new_path,ent->d_name);
            ec_1(push(q,new_path)==-1,"Errore push");
        }
    }
    ec_1(closedir(dir)==-1,"Errore closedir");
}

//funzione del thread worker
void* workerfun(void* args){

    //cast degli argomenti a coda
    arg_t*arg = (arg_t*)args;
    Queue_t*q = arg->q;
    int sockfd = *(arg->sockfd);
	pthread_mutex_t* m=((arg_t*)args)->mutex;
    //ciclo che fanno in continuazione i thread
    while(1){

        //pop dalla coda e assegno al mio path
        char*path = (char*)pop(q); 
        
        //se il path è uguale alla stringa "EXIT"
        if(strcmp(path,"EXIT")==0){
            free(path);
            break;
        }
        
        //apriamo path che sappiamo essere un file '.dat'
        FILE*fp = fopen(path,"r");
        ec_1(fp == NULL,"Errore nella fopen");

        //contiamo il numero di elementi
        int n = contaelementi(fp);

        //riporto il puntatore all'inizio e creo array per allocare tutti i valori
        ec_1(fseek(fp,0,SEEK_SET)==-1,"Errore fseek"); 

        //inserire tutti i valori nell'array
        double*valori = inseriscivalori(fp,n);
        

        //chiamo le funzioni per fare i conti 
        double media = calcmedia(valori,n);
        double devstd = calcdevstd(valori,n,media);

        //creo struttura da passare al socket
        dati_t*dati = malloc(sizeof(dati_t));
        strcpy(dati->path,path);
        dati->n = n;
        dati->media = media;
        dati->devstd = devstd;

        
        //passo al collector
        pthread_mutex_lock(m);
        write(sockfd,dati,sizeof(dati_t));
        pthread_mutex_unlock(m);

        //chiudo e faccio pulizia
        fclose(fp);
        free(path);
        free(valori);
        free(dati);
    }
    return NULL;
}


int main(int argc, char *argv[]) {

    //Controllo numero argomenti
    ec_1(argc != MAX_NUM_ARGS,"Errore nel numero di argomenti"); 
    
    //creo processo figlio e controllo errore
    int pid = fork();       
    ec_1(pid == -1,"Errore nella fork");    
    

    if (pid > 0) {     //processo padre : master process
    
        //numero di worker thread
        int w = atoi(argv[1]);  

        //path della directory iniziale
        char*path = malloc(sizeof(char)*MAX_LUN_PATH);
        strcpy(path,argv[2]);   

        //creazione coda e controllo errori
        Queue_t *q = initQueue();
        ec_1(q == NULL,"Errore nella creazione della coda");
        
        //chiamo funzione per riempire la coda di file '.dat' scorrendo ricorsivamente tra le directory
        scorriDir(path,q);

        //inserisco stringhe NULL per la terminazione di ogni thread
        for(int f = 0 ; f<w ; f++ ){
            char*fine = malloc(sizeof(char)*5);
            strcpy(fine,"EXIT");
            push(q,fine);
        } 

        int sockfd;
        struct sockaddr_in servaddr;

        // Creazione del socket
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        ec_1(sockfd==-1,"Errore creazione socket")

        //creazione porta casuale
        int porta = generaporta();

        // Configurazione dell'indirizzo del server
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Indirizzo locale
        servaddr.sin_port = htons(porta); // Numero di porta arbitrario


        // connessione al socket
        ec_1(connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) ==-1,"Errore connessione") 

        pthread_mutex_t m;
	    pthread_mutex_init(&m,NULL);

        //dichiaro w thread
        pthread_t workers[w];
        
        //creazione struct degli argomenti per i thread
        arg_t*args = malloc(sizeof(arg_t));
        args->q = q;
        args->sockfd =&sockfd;
        args->mutex = &m;
        //creo w thread e li chiamo sulla funzione
        for(int i=0;i<w;i++){
            pthread_create(&workers[i],NULL,workerfun,args);
        }

        //aspetto i thread 
        for (int i=0; i<w; i++){
            pthread_join(workers[i], NULL);
        }
        pthread_mutex_destroy(&m);
        //libero memoria
        free(args);
        ec_1(close(sockfd)==-1,"Errore close socket");
        deleteQueue(q);
        free(path);
    }else{         //processo figlio : collector
    
        dati_t*dati = malloc(sizeof(dati_t));
        int sockfd;
        struct sockaddr_in servaddr;

        // Creazione del socket
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        ec_1(sockfd==-1,"Errore creazione socket")

        //creazione porta casuale
        int porta = generaporta();

        //configurazione dell'indirizzo del server
        servaddr.sin_family = AF_INET;
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); // Indirizzo locale
        servaddr.sin_port = htons(porta); // Numero di porta arbitrario

        //bind
        ec_1(bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr))==-1,"Errore bind");

        //listen socket
        ec_1(listen(sockfd,10)==-1,"Errore listen");

        //accept
        int newsockfd = accept(sockfd,NULL,NULL);
        ec_1(newsockfd==-1,"Errore accept");

        fprintf(stdout,"n:\t\tmedia:\t\tdev:\t\tpath:\n");
        fprintf(stdout,("----------------------------------------------------------------------------\n"));
        while(1){
            //ricevo i dati dal socket
            int n = read(newsockfd,dati,sizeof(dati_t));
            if(n==0){
                break;
            }
            fprintf(stdout,"%d\t\t%.2f\t\t%.2f\t\t%s\n",dati->n,dati->media,dati->devstd,dati->path);
        }
        
        close(newsockfd);
        close(sockfd);
        free(dati);
    }
    wait(NULL);
    return 0;
}

//funzione per generare la porta causalmente e evitare conflitti
int generaporta(){
    int min_port = 49152;
    int max_port = 65535;

    // Inizializza il generatore di numeri casuali
    srand(time(NULL));

    // Genera una porta casuale all'interno del range
    return min_port + rand() % (max_port - min_port + 1);
}

//funzione per calcolare la media
double calcmedia(double *valori, int n) {
    double somma = 0.0;
    for (int i = 0; i < n; i++) {
        somma += valori[i];
    }
    return somma / n;
}

//funzione per calcolare la deviazione standard
double calcdevstd(double *valori, int n, double media) {
    double somma = 0.0;
    for (int i = 0; i < n; i++) {
        somma += pow(valori[i] - media, 2);
    }
    return sqrt(somma / n);
}

//funzione per contare il numero di elementi
int contaelementi(FILE*fp){
    char*line = NULL;
    size_t len = 0;
        int n = 0;
        while(getline(&line, &len, fp)!=-1){  //primo ciclo per contare il numero di valori
            if(line[0]=='\n'){
                continue;
            }
            double valore;
            if(sscanf(line,"%lf",&valore)==1){
                n++;
            }
        }
        free(line);
    return n;
}

//funzione per inserire i valori in un array
double* inseriscivalori(FILE*fp,int n){
    double*valori = malloc(sizeof(double)*n);
    char*line = NULL;
    size_t len = 0;
    int i = 0;
    while(getline(&line, &len, fp)!=-1){  //secondo ciclo per inserire i valori nell'array
        if(line[0]=='\n'){
            continue;
        }
        double valore;
        if(sscanf(line,"%lf",&valore)==1){
            valori[i] = valore;
            i++;
        }
    }
    free(line);
    return valori;
}