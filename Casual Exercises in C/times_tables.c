/*
Scrivere un programma che, preso in input un intero x,
stampi la tabellina di x fino al 10
*/

#include<stdio.h>

int main(){
    int x; 
    scanf("%d",&x);
    for (int i = 1; i<=10;i++){
        printf("%d\n",x*i);
    }
}