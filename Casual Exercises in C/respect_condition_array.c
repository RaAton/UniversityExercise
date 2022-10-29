/*
Scrivere un programma che legga da tastiera n interi con n dato,
li scriva in un array A e stampi l'indice i del primo
elemento che verifica A[i] = A[i+1]-A[i-1] oppure
stampi -1 nel caso nessun elemento venga trovato
*/

#include <stdio.h>

void verifica(int dim,int arr[]){
    if(arr[0]==arr[1]){
        printf("%d",1);
        return;
    }
    for(int i = 1; i < dim -1 ; i++ ){
        if(arr[i] == arr[i+1]-arr[i-1]){
            printf("%d",i+1);
            return;
        }
    }
    if(arr[dim-1]==-arr[dim-2]){
        printf("%d",dim-1);
        return;
    }
    printf("-1");
}

void inserisci(int dim,int arr[]){
    for(int i = 0; i < dim; i++ ){
        scanf("%d",&arr[i]);
    }
}

int main(){
    int dim;
    scanf("%d",&dim);
    int arr[dim];
    inserisci(dim,arr);
    verifica(dim,arr);
}
