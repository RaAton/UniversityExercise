/*
Scrivere un programma che legge da standard input un array di interi, e, utilizzando una funzione, crea un secondo array con le somme delle copie adiacenti di elementi. Il programma stampa il secondo array ottenuto.

Per un array a di lunghezza n il risultato del calcolo è un array b di lunghezza n-1 dove b[i]=a[i]+a[i+1] . Nel caso in cui n<2 il programma non stampa niente.

Il programma deve fare il controllo dell'input: se l'utente non inserisce un intero valide viene stampato il messaggio "Errore in input, inserisci un intero valido\n" e viene ripetuta la lettura da standard input.

L'input contiene prima il numero di elementi dell'array e poi gli elementi stessi. In output l'array viene stampato un elemento per riga.

*/
#include <stdio.h>

int readInt(){
	int x;
	while(scanf("%d",&x)==0){
		printf("Errore in input, inserisci un intero valido\n");
		scanf("%*[^\n]\n");
	}
	return x;
}
int main(){
    int len = readInt();
    int array1[len];
    for(int i = 0; i<len; i++){
        array1[i]=readInt();
    }
    int array2[len-1];
    for(int j = 0;j<len-1;j++){
        array2[j] = array1[j]+array1[j+1];
        printf("%d\n",array2[j]);
    }
    return 0;
}