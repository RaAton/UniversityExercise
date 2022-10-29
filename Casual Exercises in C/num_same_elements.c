/*
    Scrivere un programma che accetti in input due array di interi distinti di dimensioni n e m date
    e restituisca in output il numero di elementi che occorrono in entrambi gli array.
    Si assuma che gli array vengano inseriti in maniera strettamente crescente.
*/

#include <stdio.h>

void inserisci(int dim,int vet[dim]){
    for(int i = 0;i < dim ; i++){
        scanf("%d", &vet[i]);
    }

}

int occorrenze(int dim1,int dim2,int vet1[dim1],int vet2[dim2]){
    int occ = 0;
    int i = 0;
    int j = 0;
    for(int cont = 0; cont < dim1+dim2; cont++){
        if(vet1[i]==vet2[j]){
            occ++;
        }
        if(vet1[i]<vet2[j]){
            i++;
        }else{
            j++;
        }
    }
    return occ;
}

int main(){
    int dim1;
    scanf("%d",&dim1);
    int vet1[dim1];
    int dim2;
    inserisci(dim1,vet1);
    scanf("%d",&dim2);
    int vet2[dim2];
    inserisci(dim2,vet2);
    printf("%d",occorrenze(dim1,dim2,vet1,vet2));
    return 0;
}