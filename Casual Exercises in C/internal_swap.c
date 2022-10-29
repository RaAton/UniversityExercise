/*
Scrivere un programma che riceve in input n e un array di n interi e 
che scambi in loco tutti gli indici ( inverte l'ordine )
*/
#include <stdio.h>

void inserisci(int dim,int arr[dim]);
void scambia(int dim, int arr[dim]);
void stampa(int dim,int arr[dim]);


int main(){
    int dim;
    scanf("%d",&dim);
    int arr[dim];
    inserisci(dim,arr);
    scambia(dim,arr);
    stampa(dim,arr);
}

void inserisci(int dim,int arr[dim]){
    for(int i = 0; i < dim; i++){
        scanf("%d",&arr[i]);
    }
}
void scambia(int dim,int arr[dim]){
    int app;
    int i = 0;
    int j = dim - 1;
    while(i!=j && i!=j+1){
        app = arr[j];
        arr[j] = arr[i];
        arr[i] = app;
        i++;
        j--;
    }
}
void stampa(int dim,int arr[dim]){
    for(int i = 0; i < dim; i++){
        printf("%d\n",arr[i]);
    }
}