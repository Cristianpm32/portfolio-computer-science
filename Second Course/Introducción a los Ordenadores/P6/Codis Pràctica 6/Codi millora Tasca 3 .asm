.org 100h
	ei 					; Enable interruption
	lxi H, 500h				; Stack pointer en 500h
	sphl
	lxi H, e000h			; Associem la pantalla de text al registre HL

	loop:					; Fem loop infinit
		jmp loop
	hlt

	rai:					; Subrutina per controlar la interrupció
		in 00h			; Guardem en acumulador el contingut del teclat
		mov M,A			; Movem al registre HL el contingunt del acumulador
		inx H				; Incrementem H
		ei
		ret

.org 24h					; Aquí agafem la interrupció
	call rai				; Cridem a la subrutina
	ret
