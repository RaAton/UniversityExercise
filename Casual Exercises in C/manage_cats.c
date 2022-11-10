/*
Si scriva un programma di gestione di un gattile che per 4 volte legga:
- Un codice identificativo del gatto (un intero);
- L'età del gatto in anni (un intero);
- Il peso del gatto in Kg (un float);
- Il tipo di cibo assunto dal gatto, espresso come 0 per le crocchette, 1 per le scatolette, 2 per il tonno in scatola.

Nello stesso ordine in cui sono stati immessi i dati dei gatti si stampino, uno per linea
i codici identificativi e il tipo di cibo di tutti i gatti che hanno problemi di dieta in giovane età, 
ovvero abbiano meno di 4 anni e peso maggiore alla media dei gatti.
A fianco del codice identificativo, si stampi, separato da uno spazio, il tipo di cibo assunto dal gatto,
ovvero crocchette, scatolette oppure tonno
*/
#include <stdio.h>

typedef struct cat{
    int codice;
    int anno;
    float peso;
    int cibo;
}Gatto;

Gatto inserisci(){
    Gatto cat;
    scanf("%d %d %f %d", &cat.codice,&cat.anno,&cat.peso,&cat.cibo);
    return cat;
}

int main(){
    Gatto vet[4];
    float media;
    for(int i = 0;i < 4; i++){
        vet[i] = inserisci();
        media += vet[i].peso;
        }
    media = media/4;
    for(int i = 0;i < 4; i++){
        if(vet[i].anno < 4 && media<vet[i].peso){
            switch(vet[i].cibo){
                case 0: printf("%d Crocchette",vet[i].codice); break;
                case 1: printf("%d Scatolette",vet[i].codice); break;
                case 2: printf("%d Tonno",vet[i].codice);
            }
        }
    }
    return 0;
}