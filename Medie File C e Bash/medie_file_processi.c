#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <string.h>
#include <math.h>
#include <semaphore.h>
#include <sys/wait.h>
#include <sys/mman.h>

#define LUNGHEZZA 256


typedef struct struttura_file{
    int n;
    float avg;
    float std;
    char name[LUNGHEZZA];
}datifile;


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




void put(char path[LUNGHEZZA], int* bb, int* head, int* tail,int N, sem_t* mutex, sem_t*full, sem_t* empty){
    sem_wait(full);
    sem_wait(mutex);
    memcpy(bb+(*head)*(LUNGHEZZA+1), path, LUNGHEZZA);
    *head=(*head+1)%N;
    sem_post(mutex);
    sem_post(empty);
}

void get(char *path,int* bb, int* head, int* tail,int N, sem_t* mutex, sem_t*full, sem_t* empty){
    sem_wait(empty);
    sem_wait(mutex);
    memcpy(path, bb+(*tail)*(LUNGHEZZA+1), LUNGHEZZA);
    path[LUNGHEZZA] = '\0';
    *tail=(*tail+1)%N;
    sem_post(mutex);
    sem_post(full); 
}


void scorriDir(char path[LUNGHEZZA], int* bb, int* head, int* tail,int N, sem_t* mutex, sem_t*full, sem_t* empty){
    DIR *dir = opendir(path);
    if(dir == NULL){
        perror("Errore nell'apertura della cartella");
        exit(EXIT_FAILURE);
    }
    struct dirent *ent;
    while((ent= readdir(dir))!=NULL){
        if(ent->d_type==DT_REG && strstr(ent->d_name,".dat")!=NULL){
            char pathfile[LUNGHEZZA];
            memset(pathfile, 0, LUNGHEZZA);
            strncpy(pathfile, path, strlen(path));
            strcat(pathfile, "/");
            strcat(pathfile, ent->d_name);
            pathfile[strlen(pathfile)] = '\0';
            put(pathfile, bb, head, tail, N, mutex, full, empty);
            
        }
    }
    rewinddir(dir);
    while((ent = readdir(dir)) != NULL){
        if(strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0){
            continue;
        }else if(ent->d_type==DT_DIR){
            char pathdir[LUNGHEZZA];
            memset(pathdir, 0, LUNGHEZZA);
            strncpy(pathdir, path, strlen(path));
            strcat(pathdir, "/");
            strcat(pathdir, ent->d_name);
            pathdir[strlen(pathdir)] = '\0';
            scorriDir(pathdir, bb, head, tail, N, mutex, full, empty);
        }
    }  
    closedir(dir);
}



int main(int argc, char*argv[]){  //argv[1] = path, argv[2] = W, argv[3] = N
    if(argc != 4){
        perror("Errore nel numero di argomenti");
        exit(1);
    }

    //path cartella iniziale
    char path[LUNGHEZZA];
    memset(path, 0, LUNGHEZZA);
    strncpy(path, argv[1], LUNGHEZZA);
    path[LUNGHEZZA] = '\0';

    const int W = atoi(argv[2]);    //worker
    const int N = atoi(argv[3]);    //grandezza buffer circolare

    //creazione SMS
    char *shmName = "/lorenzobandini";
    int fd = shm_open(shmName, O_CREAT | O_TRUNC | O_RDWR, S_IRUSR | S_IWUSR);
    if(fd == -1){
        perror("Errore nella creazione della memoria condivisa");
        exit(EXIT_FAILURE);
    }
    if(ftruncate(fd,2*sizeof(int)+N*(LUNGHEZZA+1)*sizeof(char)) == -1){
        perror("Errore nella creazione della memoria condivisa");
        exit(EXIT_FAILURE);
    }

    //mappatura SMS
    int* bb=mmap(NULL, 2*sizeof(int)+N*(LUNGHEZZA+1)*sizeof(char), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    int* head=bb+N*(LUNGHEZZA+1)*sizeof(char);
    int* tail=head+sizeof(int);
    *head=0;
    *tail=0;
    close(fd);
    

    //creazione semafori
    sem_t*mutex=mmap(NULL, 3*sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    sem_t*full=mutex+sizeof(sem_t);
    sem_t*empty=mutex+2*sizeof(sem_t);
    sem_init(mutex,1,1);
    sem_init(full,1,N);
    sem_init(empty,1,0);

    //creazione pipe
    int pipefd[2];
    if(pipe(pipefd)==-1){
        perror("Errore nella creazione della pipe");
        exit(EXIT_FAILURE);
    }

    printf("\tn\t\tavg\t\tdev\t\tfile\n");
    printf("\n--------------------------------------------------------------------------------\n");

   

    //processo server
    int pid=fork();
    if(pid==-1){
        perror("Errore nella creazione del processo");
        exit(EXIT_FAILURE);
    }
    if(pid==0){
        close(pipefd[0]);
        close(pipefd[1]);
        scorriDir(path, bb, head, tail, N, mutex, full, empty);
        for(int i=0; i<W; i++){
            put("", bb, head, tail, N, mutex, full, empty);
        }
        exit(EXIT_SUCCESS);
    }

    //processi worker
    for(int i=0; i<W;i++){
        int pid=fork();
        if(pid==-1){
            perror("Errore nella creazione del processo");
            exit(EXIT_FAILURE);
        }
        if(pid==0){
            close(pipefd[0]);
            for(;;){
                char pathfile[LUNGHEZZA];
                memset(pathfile, 0, LUNGHEZZA);
                get(pathfile, bb, head, tail, N, mutex, full, empty);
                pathfile[LUNGHEZZA] = '\0';
                if(strcmp(pathfile, "") == 0){
                    datifile* dati = malloc(sizeof(datifile));  
                    dati->n = 0;
                    dati->avg = 0.0;
                    dati->std = 0.0;
                    strcpy(dati->name, "");
                    write(pipefd[1], dati, sizeof(datifile));
                    exit(EXIT_SUCCESS);
                }
                FILE*in=fopen(pathfile, "r");
                if(in==NULL){
                    perror("Errore nell'apertura del file");
                    exit(EXIT_FAILURE);
                }
                char* line1 = NULL;
                size_t len1 = 0;
                int n = 0;
                double *valori = NULL;
                fseek(in, 0, SEEK_END);
                if (ftell(in) == 0) {
                    datifile* dati = malloc(sizeof(datifile));
                    dati->n = 0;
                    dati->avg = 0.0;
                    dati->std = 0.0;
                    strcpy(dati->name, pathfile);
                    write(pipefd[1], dati, sizeof(datifile));
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
                datifile* dati = malloc(sizeof(datifile));
                dati->n = n;
                dati->avg = calcmedia(valori,n);
                dati->std = devstd(valori,n);
                strcpy(dati->name, pathfile);
                write(pipefd[1], dati, sizeof(datifile));
                free(line1);
                free(line2);
                free(valori);   
                fclose(in);    
            }

        }
    }

    //processo collector
    pid=fork();
    if(pid==-1){
        perror("Errore nella creazione del processo");
        exit(EXIT_FAILURE);
    }
    if(pid==0){
        int cont=0;
        close(pipefd[1]);
        for(;;){
            datifile* dati = malloc(sizeof(datifile));
            read(pipefd[0], dati, sizeof(datifile));
            if(strcmp(dati->name, "") != 0){
                printf("\t%d\t\t%.2f\t\t%.2f\t\t%s\n", dati->n, dati->avg, dati->std, dati->name);
            }else{
                cont++;
                if(cont==W){
                    exit(EXIT_SUCCESS);
                }
            }
             
        }
    }
 
    //chiusura pipe
    close(pipefd[0]);
    close(pipefd[1]);

    //attesa terminazione processi
    for(int i=0; i<W+2; i++){ 
        wait(NULL);
    }

    printf("\n--------------------------------------------------------------------------------\n");

    //rimozione SMS
    munmap(bb, (N+2)* sizeof(int));

    //rimozione semafori
    sem_destroy(mutex);
    sem_destroy(full);
    sem_destroy(empty);
    munmap(mutex, 3*sizeof(sem_t));
    
    return 0;
}