/*
Scrivere un programma che legge da standard input una matrice di interi e stampa la sua trasposta. Il programma deve utilizzare una funzione per costruire la trasposta.

La trasposta di una matrice inverte le righe e le colonne (le colonne diventano le righe e le righe diventano le colonne). Data una matrice , la trasposta  e definita come .

L'input contiene prima il numero di righe e di colonne, poi gli elementi della matrice riga per riga.
*/

#include <stdio.h>
#include <stdlib.h>

int**creatrasposta(int rig, int col,int matrice[rig][col]){
  int colt = rig;
  int rigt = col;
  int**pt = (int**)calloc(rigt,sizeof(int*));
  for (int i = 0; i < rigt; i++) {
    pt[i]=(int*)calloc(colt,sizeof(int));
    for(int j = 0;j<colt;j++){
      pt[i][j]=matrice[j][i];
    }
  }
  return pt;
}

int main() {
  int righe, colonne;
  scanf("%d %d", &righe, &colonne);
  int matrice[righe][colonne];
  for (int i = 0; i < righe; i++) {
    for (int j = 0; j < colonne; j++) {
      scanf("%d", &matrice[i][j]);
    }
  }
  
  int**puntrasp = creatrasposta(righe, colonne, matrice);
  for (int i = 0; i < colonne; i++) {
    for (int j = 0; j < righe; j++) {
      printf("%d ",puntrasp[i][j]);
    }
    printf("\n");
  }
  return 0;
}