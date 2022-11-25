@algoritmo per sommatoria di 5 con uso della push/pop e chiamata di sistema
	.text
	.global main
	.type main, %function

main:
	mov r0,#0	@ contatore i=0
	push {r4}	@salvo r4 nello stack
	mov r4,#5	@inserisco 5 in r4
	mov r1,#0	@cont somma

for:
	cmp r0,r4	@guardo se il cont è arrivato alla fine
	bne fine	@se vero esco
	add r1, r1, r0	@sommo
	add r0, #1	@aggiorno contatore 
	b for		@ricomincio il ciclo
fine:	
	pop {r4}	@riprendo r4 dallo stack
	mov r7, #1	@modifica di r7 per svc
	svc 0		@uscita con chiamata di sistema
