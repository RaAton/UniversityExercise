@funzione atoi
    .text
    .global myatoi
    .type myatoi, %function

    @r0 ho puntatore a stringa
myatoi:
    mov r1, #0 @contatore numero finale
for:   
    ldr r2, [r0], #1    @carico in r2 carattere puntato e poi scorro di uno
    cmp r2, #'0'        @controllo sei il prossimo carattere è null
    moveq r0, #-1       @nel caso restituisco errore
    beq fine            @esco
    mul r1, r1, #10     @moltiplico per 10
    cmp r2, 0x31        @guardo tutti i casi in ASCII
    addeq r1, r1, #1
    b for
    cmp r2, 0x32
    addeq r1, r1, #2
    b for
    cmp r2, 0x33
    addeq r1, r1, #3
    b for
    cmp r2, 0x34
    addeq r1, r1, #4
    b for
    cmp r2, 0x35
    addeq r1, r1, #5
    b for
    cmp r2, 0x36
    addeq r1, r1, #6
    b for
    cmp r2, 0x37
    addeq r1, r1, #7
    b for
    cmp r2, 0x38
    addeq r1, r1, #8
    b for
    cmp r2, 0x39
    addeq r1, r1, #9
    b for
fine:
    mov pc,lr