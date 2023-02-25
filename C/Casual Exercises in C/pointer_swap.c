/*
Implementare una funzione tswap(int*x, int*y, int*z) che riceva in input tre variabili e ne scambi i valori in modo che:
- x prenda il valore di z
- y prenda il valore di x
- z prenda il valore di y
Leggere da input un array di tre interi e invocare la funzione passando gli indirizzi delle tre celle.
*/
#include <stdio.h>

void tswap(int*x, int*y, int*z){
    int save1 = *x;
    int save2 = *y;
    *x = *z;
    *y = save1;
    *z = save2;
} //scambio indirizzi

void inserisci(int dim,int vet[dim]){
    for(int i = 0;i < dim ; i++){
        scanf("%d", &vet[i]);
    }
}   //inserimento

void stampa(int dim,int arr[dim]){
    for(int i = 0; i < dim; i++){
        printf("%d\n",arr[i]);
    }
}   //stampa array

int main(){
    int arr[3];        
    inserisci(3,arr);  
    tswap(&arr[0],&arr[1],&arr[2]);
    stampa(3,arr);
    return 0;
}