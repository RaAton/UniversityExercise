/*
Scrivere una funzione che, dato un array di interi e la sua lunghezza,
lo ordini utilizzando l'algoritmo Selection Sort e stampi l'array ordinato.
*/

/*
#include <stdio.h> 


int main() { 
   int a[10] = {5,8,0,1,4,2,4,3,9,7}; 
   int i, j, min, t;

//t è la variabile temporanea utilizzata per lo scambio 

   for(i=0; i<9; i++){ 
      min=i; 
      for (j = i+1;j < 10; j++){ 
         if (a[j]<a[min]) 
            min=j; 
      } 
      t = a[min];
//si trova l'elemento più piccolo dell'array e si scambia con l'elemento alla posizione i 
      a[min] = a[i]; 
      a[i] = t;  
    }

   for(i=0; i<10; i++){
      printf("%d ", a[i]);		
   }	
}
*/

#include <stdio.h>

void inserisci(int dim,int arr[]){
    for(int i = 0; i < dim; i++ ){
        scanf("%d",&arr[i]);
    }
}

void selection_sort(int dim,int arr[dim]){
    int j, min, t;
    for(int i=0; i<dim-1; i++){ 
      min=i; 
      for (j = i+1;j < dim; j++){ 
         if (arr[j]<arr[min]) 
            min=j; 
      } 
      t = arr[min];
      arr[min] = arr[i]; 
      arr[i] = t;  
    }

}

void stampa(int dim,int arr[dim]){
    for(int i = 0; i < dim; i++){
        printf("%d\n",arr[i]);
    }
}

int main(){
    int dim;
    scanf("%d",&dim);
    int arr[dim];
    inserisci(dim,arr);
    selection_sort(dim,arr);
    stampa(dim,arr);
    return 0;
}