#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <math.h>
#include <fcntl.h>

#define MAX_NUM_ARGS 2          //Gli argomenti devono essere 2
#define MAX_PATH_LENGTH 256     //Lunghezza massima del path

//Macro per controllare gli errori
#define ec_1(s,m) \
    if ( (s) == 1) {perror(m); exit(EXIT_FAILURE);}
 

//definizione delle funzioni
void scorri(char* path);
double calcmedia(double *valori, int n);
double devstd(double *valori, int n);


//Inizio del programma
int main(int argc, char *argv[]){

    ec_1(argc != MAX_NUM_ARGS,"Errore nel numero di argomenti"); 

    //grafica
    printf("n\t\tavg\t\tstd\t\tname\n");   
    printf("--------------------------------------------------------\n");
    scorri(argv[1]);    //chiamata funzione sulla cartella padre
    printf("--------------------------------------------------------\n");
    return 0;
}


//Funzione per scorrere la directory e file
void scorri(char* percorso){

    int len = strlen(percorso);
    char path[(len+1)];
    strcpy(path, percorso);     //copio il path passato come argomento nella variabile path
    DIR *dir = opendir(path);   //apro la directory
    struct dirent *ent;         
    printf("Directory:  %s\n", path);
    while((ent = readdir(dir)) != NULL){        //scorro la directory
        if(ent->d_type==DT_REG && strstr(ent->d_name,".dat")!=NULL){    //se il file è un file regolare e ha estensione .dat
            char new_path[2*(len+1)];     
            sprintf(new_path, "%s/%s", path, ent->d_name);    //creo il nuovo path
            FILE*in=fopen(new_path,"r");    //apro il file
            ec_1(in==NULL,"Errore nell'apertura del file");
            char* line1 = NULL;
            size_t len1 = 0;
            int n = 0;
            double *valori = NULL;


            fseek(in, 0, SEEK_END);
            if (ftell(in) == 0) {
                printf("%d\t\t%.2f\t\t%.2f\t\t%s\n",n,0.00,0.00,ent->d_name);    //stampo i risultati per il file
                continue;
            }
            rewind(in);

            while(getline(&line1, &len1, in)!=-1){  //primo ciclo per contare il numero di valori
                if(line1[0]=='\n'){
                    continue;
                }
                double valore;
                if(sscanf(line1,"%lf",&valore)==1){
                    n++;
                }
            }
            fseek(in,0,SEEK_SET);   //riporto il puntatore all'inizio del file
            valori = malloc(n * sizeof(double));    //alloco lo spazio per i valori
            int i = 0;
            char* line2 = NULL;
            size_t len2 = 0;
            while(getline(&line2, &len2, in)!=-1){  //secondo ciclo per salvare i valori nel vettore
                if(line2[0]=='\n'){
                    continue;
                }
                double valore;
                if(sscanf(line2,"%lf",&valore)==1){
                    valori[i] = valore;
                    i++;
                }
            }
            printf("%d\t\t%.2f\t\t%.2f\t\t%s\n",n,calcmedia(valori,n),devstd(valori,n),ent->d_name);    //stampo i risultati per il file
            free(valori);   //libero lo spazio per i valori
            fclose(in);    //chiudo il file
        }
    }
    rewinddir(dir); //riporto il puntatore all'inizio della directory
    while((ent = readdir(dir)) != NULL){    //scorro la directory
        if(strcmp(ent->d_name,".") ==0 || strcmp(ent->d_name,"..")==0){     //escludo . e .. 
            continue;
        }else if(ent->d_type==DT_DIR){      //se il file è una directory
            char new_path[2*(len+1)];
            sprintf(new_path, "%s/%s", path, ent->d_name);    //creo il nuovo path
            scorri(new_path);       //richiamo la funzione per la nuova directory
        }
    }
    closedir(dir);  //chiudo la directory
}


//Funzione per calcolare la media
double calcmedia(double *valori, int n) {
    double somma = 0.0;
    for (int i = 0; i < n; i++) {
        somma += valori[i];
    }
    return somma / n;
}

//Funzione per calcolare la deviazione standard
double devstd(double *valori, int n) {
    double media = calcmedia(valori, n);
    double varianza = 0.0;
    for (int i = 0; i < n; i++) {
        varianza += pow(valori[i] - media, 2);
    }
    varianza /= n;
    return sqrt(varianza);
}
