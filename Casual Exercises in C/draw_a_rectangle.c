/*
    Scrivere un programma che legga da tastiera due interi h e l e
    stampi un rettangolo fatto da asterischi, con altezza h e lunghezza l.
*/

#include <stdio.h>

int main(){
    int h;
    int l;
    scanf("%d",&h);
    scanf("%d",&l);
    for(int i = 0; i < l ; i++){
        printf("*");
    }
    if(h==1){
        return 0;
    }
    for(int i = 1; i < h-1; i++ ){
        printf("\n*");
        for(int j = 1;j < l-1; j++){
            printf(" ");
        }
        printf("*");
    }
    printf("\n");
    for(int i = 0; i < l ; i++){
        printf("*");
    }
    return 0;
}