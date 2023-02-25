/*
Scrivere un programma C che legge da standard input due matrici di interi
dimensione r1Xc1 e r2Xc2 e stampa la somma delle due matrici,
solo se possibile (r1==r2 e c1==c2).
*/
#include <stdio.h>

int dimensione_corretta(int*d){
    int con;
    con = scanf("%d",d);
    if(con==0){
        printf("Errore in input\n");
        return 1;
    }
    return 0;
}   //controllo che abbiamo dimensioni di interi

void inserimento_mat(int r, int c,int mat[r][c]){
    for(int i = 0; i < r ; i++){
        for(int j = 0; j<c ; j++){
            scanf("%d",&mat[i][j]);
        }
    }
}   //inserimento in matrice

int controllo(int r1,int c1,int r2,int c2){
    if(r1==r2 && c1==c2){
        return 1;
    }else{
        return 0;
    }
}   //controllo dimensioni compatibili matrici

void somma_mat(int r,int c,int mat1[r][c],int mat2[r][c],int mat_somma[r][c]){
    for(int i = 0; i < r ; i++){
        for(int j = 0; j<c ; j++){
            mat_somma[i][j]=mat1[i][j]+mat2[i][j];
        }
    }
}   //somma matrici

void stampa_mat(int r,int c,int mat[r][c]){
    for(int i = 0; i < r ; i++){
        for(int j = 0; j<c ; j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }
}   //stampa matrice

int main(){
    //dichiarazione x dimensioni
    int r1,c1,r2,c2;

    //creazione prima matrice
    if(dimensione_corretta(&r1) ||  dimensione_corretta(&c1)){
        return 0;
    }
    int mat1[r1][c1];
    inserimento_mat(r1,c1,mat1);

    //creazione seconda matrice
    if(dimensione_corretta(&r2) ||  dimensione_corretta(&c2)){
        return 0;
    }
    int mat2[r2][c2];
    inserimento_mat(r2,c2,mat2);
    
    //controllo e funzione somma
    int mat_somma[r1][c1];
    if(controllo(r1,c1,r2,c2)){
        somma_mat(r1,c1,mat1,mat2,mat_somma);
    }else{
        printf("Le matrici non si possono sommare\n");
        return 0;
    }
    stampa_mat(r1,c1,mat_somma);

    return 0;
}