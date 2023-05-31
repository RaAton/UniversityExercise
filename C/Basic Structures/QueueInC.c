#include <stdio.h>
#include <stdlib.h>

typedef struct struct_nodo{
int val;
struct struct_nodo*next;
}Nodo;

typedef Nodo*Testa;
typedef Nodo*Coda;

void push(int val,Testa*tes,Coda*cod){
  Nodo*n=(Nodo*)malloc(sizeof(Nodo));
  n->val=val;
  n->next=*cod;
  *cod=n;
  if(*tes==NULL){
    *tes=n;
  }
}//inserisce elemento in fondo coda

void pop(Testa*tes,Coda*cod){
  
}//toglie elemento in cima alla coda

int peek(Testa*tes){
  return (*tes)->val;
}//restituisce elemento in cima alla coda

int length(Coda*cod){
  if(*cod==NULL){
    return 0;
  }else{
    return 1 + length(&((*cod)->next));
  }
}  //calcola lunghezza coda in modo ricorsivo

void print(Coda*cod){
  if(*cod==NULL){
    return;
  }else{
    print(&((*cod)->next));
    printf("%d\n",(((*cod)->val)));
  }
}//stampa elementi partendo dal primo in modo ricorsivo

int main(){
  Testa t=NULL;
  Coda c=NULL;
  int controllo=1;
  int num;
  while(1){
    scanf("%d",&num);
    if(controllo==0 && num==0){
        printf("Lista con %d elementi",length(&c));
        print(&c);
        exit(1);
    }
    if(num%2!=0){
      push(num, &t, &c);
    }
    if(num%2==0 && num!=0){
      push(num/2, &t, &c);
    }
    if(num==0){
      if((*t).val%2==0 || length(&c)>4){
        pop(&t, &c);
      }
      controllo=num;
    }
  }
  return 0;
}