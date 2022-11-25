 @funzione che prende dice se r0 è pari o dispari e registra il risultato nel registro r1 
        .text
        .global main

main:   push {lr}       @salvo lr
        mov r0, #7      @assegno 7 a r0
        mov r1, #0      @assegno 0 a r1

        and r0, r0, #1  @vedo se r0 è pari facendo l'and del primo bit con 1 e salvare in r0
        cmp r0, #0      @se r0 è 0 vuol dire che è dispari, imposta il flag

        bne cont        @flag ne se flag è 0 e quindi salto add ( non faccio +1 perchè il numero è pari )

        add r1, r1, #1  @r1 è 1 se il valore in r0 è dispari

cont:   ldr r0,=str     @salvo in r0 il formato della stringa
        bl printf       @stampo y vale 

        pop {lr}        @riprendo l'indirizzo di ritorno
        mov pc, lr      @ritorno


        .data
str:    .string "y vale %d \n"  @stringa da stampare
