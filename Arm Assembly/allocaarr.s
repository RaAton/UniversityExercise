@creo in memoria 4 celle consecutive in cui salvo i multipli di 4 e ritorno errori con stringhe e chiamate di sistema
	.data
str1:	.string "successo"
str2:	.string "errore"


	.text
	.global main
	.type main, %function
	
main:	
	mov r0, #1	@alloco 1 in r0
	lsl r0, #4	@shifto a sx r0 per avere 16
	bl malloc	@creo spazio pari a 16
	cmp r0, #0	@errore nel caso non ce la facesse
	beq err
	mov r1, r0 	@l'indirizzo creato va ricordato
	mov r0, #0	@inizializzo r0 per contatore (i=0)
loop:
	str r0, [r1,r0]
	add r0 , r0 , #4	@i ++ ( in byte i +=4) 
	cmp r0 , #16 		@siamo alla fine 
	beq fine		@se si esci 
	b loop	

err:
	ldr r0, =str2	@prende l'errore in r0
	bl printf	@stampa errore
	mov r7, #1	@descrive tipo di syscall
	svc 0		@r7 = 1 quindi exit

fine:
	ldr r0,=str1	@cattura errore in r0
	push {r1}	@salva r1 perchè print lo sporca	
	bl printf	
	pop {r1}	@adesso lo può tirare di nuovo fuori
	mov r0,r1	@la free viene chiamata su r0
	bl free		@libera memoria allocata
	mov r7, #1	@per uscire
	svc 0
