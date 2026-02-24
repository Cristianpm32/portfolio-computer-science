.data 30h					; Guardem tots els nombre del 0 al 5
	zero: 	db 01110111b
	un:		db 01000100b
	dos:		db 00111110b
	tres:		db 01101110b
	quatre:	db 01001101b
	cinc:		db 01101011b

.data 43h					; Guardem el clear, tot 0
	clear: 	db 00000000b

.org 100h
	loop:					; Fem loop infinit
		jmp loop
	thlt

	rai:					; Subrutina per controlar la interrupció
		in 00h			; Guardem en acumulador el contingut del teclat
		mov C,A			; Movem al registre C el contingunt del acumulador
		ldax B			; Movem a l'acumulador el contingut el registre BC
		out 07h			; Mostrem al display 7 el que hi hagi a l'acumulador
		ret

.org 24h					; Aquí agafem la interrupció
	call rai				; Cridem a la subrutina
	ret
