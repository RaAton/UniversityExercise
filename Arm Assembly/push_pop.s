@prova per capire ordine di uscita
    .text
    .global main
    .type main, %function
main:
    mov r0, #1
    mov r1, #2
    @ r0 = 1 , r1 = 2
    push {r0,r1}
    pop {r1}
    pop {r0}
    @ r0 = 2 , r1 = 1
    mov pc, lr
    @ ritorno