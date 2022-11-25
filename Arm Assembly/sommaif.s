@faccio somma se i valori in r0 e r1 sono uguali altrimenti faccio la sottrazione
	.text
	.global main
	.type main, %function

main:	
	mov r0,#1	@r0 vale 1	
	mov r1,#2	@r1 vale 2
	cmp r0,r1	@comparo r1 e r2
	bne else	@se son diversi fai ramo else
	add r2,r0,r1 @altrimenti sommali e registra in r2
	b endif		@salto incondizionato a endif

else:
	sub r2,r1,r0	@se sono diversi entra in questo ramo e fa la sottrazione tra r1 e r0 e salva in r2

endif:
	mov pc,lr @return
