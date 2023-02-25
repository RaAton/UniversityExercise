/*
Scrivere un programma che legga da tastiera due vettori di solita dimensione
data e ne crei un altro con la somma dei rispettivi. 
*/

#include <stdio.h>

void inserisci(int dim,int vet[dim]){
    for(int i = 0;i < dim ; i++){
        scanf("%d", &vet[i]);
    }

}

void stampa(int dim,int vet[dim]){
    printf("[");
    for(int i = 0; i < dim-1;i++){
        printf("%d,",vet[i]);
    }
    printf("%d]\n",vet[dim-1]);
}

void somvet(int dim,int vetsum[dim],int vet1[dim],int vet2[dim]){
    for(int i = 0; i < dim;i++){
        vetsum[i]=vet1[i]+vet2[i];
    }
}

int main(){
    int dim = 5;
    int vet1[dim];
    int vet2[dim];
    int vetsum[dim];
    inserisci(dim,vet1);
    inserisci(dim,vet2);
    stampa(dim,vet1);
    stampa(dim,vet2);
    somvet(dim,vetsum,vet1,vet2);
    stampa(dim,vetsum);
    return 0;
}