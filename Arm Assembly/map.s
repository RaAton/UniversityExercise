 @prendo un array di stringhe numeriche, le trasformo in numeri e le divido per 4
    .text
    .global map
    .type map, %function

    @r0 puntatore
    @r1 numero di valori
map:
    mov r2, #0  @contatore
for:
    cmp r1, #0  @vedo se sono arrivato alla fine
    beq fine    @nel caso finisco
    ldr r3,[r0],#4  @prendo dalla memoria cio che punta r0 e poi scorro di una posizione
    push {r0, lr}   @preservo lr
    mov r0, r3  @poichè atoi prende r0 come argomento
    bl atoi     @trasformo r0 da stringa a intero
    mov r3, r0  @passo di nuovo r0 che adesso è numero a r3
    pop {r0, lr}    @riprendo lr
    cmp r3, #-1     @nel caso di r3=-1 torno nel for
    beq for     
    lsr r3, #2      @divido per 4 facendo lo shift 
    add r2, r2, r3  @sommo al contatore somma
    sub r1, r1, #1  @tolgo 1 dal contatore cicli
    b for
fine:
    mov pc, lr      @ritorno dalla funzione