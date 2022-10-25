/*
Scrivere un programma che legge da standard input un array di interi, e, utilizzando una funzione, crea un secondo array con le somme delle copie adiacenti di elementi. Il programma stampa il secondo array ottenuto.

Per un array a di lunghezza n il risultato del calcolo è un array b di lunghezza n-1 dove b[i]=a[i]+a[i+1] . Nel caso in cui n<2 il programma non stampa niente.

Il programma deve fare il controllo dell'input: se l'utente non inserisce un intero valide viene stampato il messaggio "Errore in input, inserisci un intero valido\n" e viene ripetuta la lettura da standard input.

L'input contiene prima il numero di elementi dell'array e poi gli elementi stessi. In output l'array viene stampato un elemento per riga.
*/

#include <stdlib.h>
#include <stdio.h>

typedef struct struct_nodo{
  int val;
  struct struct_nodo*sx;
  struct struct_nodo*dx;
}Nodo;

typedef Nodo*Radice;

void insert(int val,Radice*radix){
  if(val<(*radix)->val){
    if((*radix)->sx==NULL){
      Nodo*n=(Nodo*)malloc(sizeof(Nodo));
      n->val=val;
      n->dx=NULL;
      n->sx=NULL;
      (*radix)->sx=n;
      }else{
      insert(val,&(*radix)->sx);
    }
  }else{
    if((*radix)->dx==NULL){
      Nodo*n=(Nodo*)malloc(sizeof(Nodo));
      n->val=val;
      n->dx=NULL;
      n->sx=NULL;
      (*radix)->dx=n;
      }else{
      insert(val,&(*radix)->dx);
      }
  }
}

void printAscending(Radice radix){
  if(radix==NULL){
    return;
  }
  
    printAscending(radix->sx); 
    printf("%d ",radix->val);
    printAscending(radix->dx);
}


int find(int trova,Radice radix){
  if(radix==NULL){
    return 0;
  }
  if(radix->val==trova){
    return 1;
  }
  if(trova<radix->val){
    return find(trova,radix->sx);
  }else{
    return find(trova,radix->dx);
  }
  return 0;
}


int main(){
  Radice radix;
  int cont;
  scanf("%d",&cont);
  if(cont==0){
    printf("\nFalse");
    return 0;
  }
  int val;
  scanf("%d",&val);
  Nodo*n=(Nodo*)malloc(sizeof(Nodo));
  n->val=val;
  n->sx=NULL;
  n->dx=NULL;
  radix=n;
  for(int i=0;i<cont-1;i++){
    scanf("%d",&val);
    insert(val,&radix); 
  }
  printAscending(radix);
  int trova;
  scanf("%d",&trova);
  if(find(trova,radix)==1){
    printf("\nTrue");
  }else{
    printf("\nFalse");
  }
  return 0;
}