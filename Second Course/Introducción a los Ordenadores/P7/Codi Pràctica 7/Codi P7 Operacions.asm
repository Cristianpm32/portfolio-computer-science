;################################
; MEMORIA DE DADES
;################################
.data 50h
unitat1: db 0  ; unitat que enviara a pantalla
desena1: db 0  ; desena que enviara a pantalla
centena1: db 0 ; centena que enviara a pantalla
unitat2: db 0  ; unitat que enviara a pantalla
desena2: db 0  ; desena que enviara a pantalla
centena2: db 0 ; centena que enviara a pantalla
unitatR: db 0  ; unitat que enviara a pantalla
desenaR: db 0  ; desena que enviara a pantalla
centenaR: db 0 ; centena que enviara a pantalla
carry: db 0   ; mira si hi ha carry
signe1: db 0h   ; guarda el signe del primer valor
signe2: db 0h   ; guarda el signe del segon valor
signeresultat: db 0h ; guarda el signe del resultat
memoria_pantalla: dw e000h ; ens servira per avançar en la pantalla de text
;################################
; MEMORIA DE PROGRAMA
;################################
.org 100h
;#############################################################################################################
; Cal esmentar en aquest codi que els valors van apareixent en pantalla a mesura que es van introduïnt, com si
; fos una calculadora.
;#############################################################################################################



;##########################################
; INTRODUIM EL PRIMER VALOR (SIGNE O XIFRA)
;##########################################

;##############################################################################################################################
; S'ha d'observar que cada vegada que s'introdueix un valor, aquest s'ha d'actualitzar amb les altres xifres del nombre
; de forma que les unitats passen a ser desenes i les desenes a centenes.
;##############################################################################################################################
lhld memoria_pantalla
mov d,h ; Utilitzarem d i e per anar guardant la direcció de memòria de la pantalla, de forma que podem anar treballant de mentres amb el parell HL
mov e,l
in 0h
cpi 30h	; Volem veure si s'ha introduït un signe negatiu, positiu, and (&) o or (|). Això es farà en cada xifra del nombre
jnc continuaOpera ; Es farà el salt si el que s'ha introduït és un nombre
lxi h, signe1
mov M,a
mov h,d
mov l,e
mov M, a
inx h
mov d,h
mov e,l
in 0h
continuaOpera:
sui 30h
lxi h, unitat1
mov M,a
mov b,M
mov h,d
mov l,e
call mostra_digit
inx h
mov d,h
mov e,l
;##################################
; INTRODUIM LA SEGONA XIFRA O SIGNE
;##################################
in 0h
cpi 30h
jc segon_nombre
cpi 40h ; A partir d'aquest valor podem comparar per veure si s'ha introduït un nombre o no, ens interessa veure si | (7Ch) s'ha entrat per teclat
jnc segon_nombre
lxi h, desena1
mov M,b
lxi h, unitat1
sui 30h
mov M,a
mov b,M
lxi h, desena1
mov c,M
mov h,d
mov l,e
call mostra_digit
inx h
mov d,h
mov e,l
;###################################
; INTRODUIM LA TERCERA XIFRA O SIGNE
;###################################
in 0h
cpi 30h 
jc segon_nombre
cpi 40h ; A partir d'aquest valor podem comparar per veure si s'ha introduït un nombre o no, ens interessa veure si | (7Ch) s'ha entrat per teclat
jnc segon_nombre
lxi h, centena1
mov M,c
lxi h, desena1
mov M,b
lxi h, unitat1
sui 30h
mov M,a
mov h,d
mov l,e
call mostra_digit
inx h
mov d,h
mov e,l

;####################################################
; INTRODUIM EL SEGON VALOR I L'OPERACIO QUE VOLEM FER
;####################################################

in 0h
segon_nombre:
lxi h, signe2
mov M, a
mov h,d
mov l,e
mov M,a
inx h
mov d,h
mov e,l

lxi h, unitat2
in 0h
cpi 3Ah
jnc finalOpera
sui 30h
mov M,a
mov b,M
mov h,d
mov l,e
call mostra_digit
inx h
mov d,h
mov e,l
in 0h
cpi 3Ah
jnc finalOpera
lxi h, desena2
mov M,b
lxi h, unitat2
sui 30h
mov M,a
mov b,M
lxi h, desena2
mov c,M
mov h,d
mov l,e
call mostra_digit
inx h
mov d,h
mov e,l
in 0h
cpi 3Ah

; Volem veure que si el que s'ha introduït per pantalla és un igual (=) aleshores fem un salt com finalització de la introducció de nombres.
;Això es farà en cada introducció de xifra

jnc finalOpera 
lxi h, centena2
mov M,c
lxi h, desena2
mov M,b
lxi h, unitat2
sui 30h
mov M,a
mov h,d
mov l,e
call mostra_digit
inx h
mvi a, 3dh
mov M, a
inx h
mov d,h
mov e,l

jmp comparacions ; Es fa un salt a la part de comparacions de nombres i elecció d'operació.

finalOpera:
mov h,d
mov l,e
mov M, a
inx h
mov d,h
mov e,l

comparacions:
;###############################################################################################################################
; COMPARACIÓ ENTRE ELS DOS NOMBRES I SIGNES
; Aquí es farà la comparació dels signes per veure quin cas és l'idoni per operar. Es consideren els casos +/+, +/-, -/+ i -/-.
; A més a més, també es fan les portes OR i AND
;###############################################################################################################################
lxi h, signe1
mov a, M
sui 2dh 
jz restes ; Es comprova si el primer nombre té signe negatiu. En cas positiu, aleshores es fa un salt a restes
	lxi h, signe2
	mov a,M
	sui 2bh ; Es comprova si el segon nombre té signe positiu (suma)
	jz suma
	adi 2bh
	sui 2dh ; Es comprova si el segon nombre té signe negatiu (resta)
	jz diferents
	adi 2dh
	sui 26h ; Es comprova si el segon nombre té signe AND (&)
	jz portaand
	adi 26h
	sui 7ch ; Es comprova si el segon nombre té signe OR (|)
	jz portaor
restes:
	lxi h, signe2
	mov a,M
	sui 2dh
	jnz diferents
	lxi h, signe1
	mov a, M
	lxi h, signeresultat ; Si els dos nombres tenen signe negatiu, aleshores es guarda el signe en signeresultat i es fa una suma
	mov M, a
suma:
	call unitats_suma
	call desenes_suma
	call centenes_suma
	lxi h, carry
	mov a,M
	sui 1h
	jz overflow ;En el cas que hi hagi un valor a carry, aleshores vol dir que tenim overflow, i es fa un salt
	jmp mostrarResultats

;##################################################################################################################################
; COMPARACIÓ ENTRE ELS DOS NOMBRES 
; Aquí es farà la comparació dels nombre per saber quin és més gran, i per tant quin dels dos farà que predomini el signe
; en l'operació. En particular, el procediment que es seguirà és moure a acumulador el contingut de la xifra del primer nombre
; i restar-li la xifra corresponent del segon, en ordre decreixent (centenes, desenes i unitats). Si en algun cas es dona que
; el valor de l'acumulador és negatiu, aleshores el segon nombre en valor absolut és més gran que el primer, i per tant predominarà
; el signe del segon nombre.
;##################################################################################################################################


diferents:
	lxi h, centena1
	mov a, M
	lxi h, centena2
	sub M
	jm canvi
	mov a, 0h
	lxi h, desena1
	mov a, M
	lxi h, desena2
	sub M
	jm canvi
	mov a, 0h
	lxi h, unitat1
	mov a, M
	lxi h, unitat2
	sub M
	jm canvi
	lxi h, signe1
	mov a, 0h
	mov a,M
	lxi h, signeresultat
	mov M, a
	jmp resta

;###################################################################################################################################
; CANVI DE NOMBRES
; Aquí es fa un canvi de forma que el primer nombre passa a ser el segon i el segon passa a ser el primer. D'aquesta forma no es
; tindrà problemes en fer la resta. El procediment és utilitzar els registres B i H juntament amb l'acumulador, i anant actualitzant
; els dos nombres, intercanviant les xifres.
;###################################################################################################################################

canvi:
	mov b, 0h
	lxi h, centena1
	mov a, M
	mov b,a
	lxi h, centena2
	mov a, M
	lxi h, centena1
	mov M, a
	lxi h, centena2
	mov M, b
	mov b, 0h
	lxi h, desena1
	mov a, M
	mov b,a
	lxi h, desena2
	mov a, M
	lxi h, desena1
	mov M, a
	lxi h, desena2
	mov M, b
	mov b, 0h
	lxi h, unitat1
	mov a, M
	mov b,a
	lxi h, unitat2
	mov a, M
	lxi h, unitat1
	mov M, a
	lxi h, unitat2
	mov M, b
	lxi h, signe2
	mov a, 0h
	mov a,M
	lxi h, signeresultat
	mov M, a
resta:
	call unitats_resta
	call desenes_resta
	call centenes_resta
	jmp mostrarResultats
portaand:
	call and
	jmp mostrarResultats
portaor:
	call or

; Finalment, aqui es mostren els resultats de l'operació

mostrarResultats:
lxi h, signeresultat
mov a, M
sui 2dh
jz posar_signe
jmp continuaMostrant
posar_signe:
mov h,d
mov l,e
adi 2dh
mov M, a
inx h
mov d,h
mov e,l
continuaMostrant:
lxi h, centenaR
mov a, M
mov h,d
mov l,e
call mostra_digit
inx h
mov d,h
mov e,l
lxi h, desenaR
mov a, M
mov h,d
mov l,e
call mostra_digit
inx h
mov d,h
mov e,l
lxi h, unitatR
mov a, M
mov h,d
mov l,e
call mostra_digit
inx h
jmp finalPrograma

; En el cas que es produeixi el overflow, aleshores es posaran 3 X's de forma que el resultat serà XXX
overflow:
mov h,d
mov l,e
adi 58h
mov M,a
inx h
mov M,a
inx h
mov M,a
finalPrograma:
hlt

;################################
;SUBRUTINES UTILITZADES
;################################

;Subrutina per mostrar els dígits dels nombres

.org 500h
mostra_digit:
push h
;primer valor en pantalla
adi 30h
mov M,a
pop h
ret

;Subrutina per fer la suma de les unitats

.org 550h
unitats_suma:
push h
lxi h, unitat1
mov a, M
lxi h, unitat2
add M
cpi 0Fh
jnc modifica_unitat2
cpi Ah
jnc modifica_unitat
lxi h, unitatR
mov M, a
jmp final
modifica_unitat:
sui Ah
lxi h, unitatR
mov M,a
lxi h, desenaR
mvi M, 1
jmp final
modifica_unitat2:
sui 10h
adi 6
lxi h, unitatR
mov M,a
lxi h, desenaR
mvi M, 1
final:
pop h
ret

;Subrutina per fer la suma de les desenes

.org 600h
desenes_suma:
push h
lxi h, desenaR
mov a, M
lxi h, desena1
add M
lxi h, desena2
add M
cpi 0Fh
jnc modifica_desena2
cpi Ah
jnc modifica_desena
lxi h, desenaR
mov M, a
jmp final1
modifica_desena:
sui Ah
lxi h, desenaR
mov M,a
lxi h, centenaR
mvi M, 1
jmp final1
modifica_desena2:
sui 10h
adi 6
lxi h, desenaR
mov M,a
lxi h, centenaR
mvi M, 1
final1:
pop h
ret

;Subrutina per fer la suma de les centenes

.org 700h
centenes_suma:
push h
lxi h, centenaR
mov a, M
lxi h, centena1
add M
lxi h, centena2
add M
cpi 0Fh
jnc modifica_centena2
cpi Ah
jnc modifica_centena
lxi h, centenaR
mov M, a
jmp final2
modifica_centena:
sui Ah
lxi h, centenaR
mov M,a
lxi h, carry
mvi M, 1
jmp final2
modifica_centena2:
sui 10h
adi 6
lxi h, centenaR
mov M,a
lxi h, carry
mvi M, 1
final2:
pop h
ret

;Subrutina per fer la resta de les unitats

.org 750
unitats_resta:
push h
lxi h, unitat1
mov a, M
lxi h, unitat2
sub M
jm modifica_uResta
lxi h, unitatR
mov M, a
jmp end
modifica_uResta:
adi Ah
lxi h, unitatR
mov M, a
lxi h, desena2
mov a, M
adi 1
mov M, a
end:
pop h
ret

;Subrutina per fer la resta de les desenes

.org 800h
desenes_resta:
push h
lxi h, desena1
mov a, M
lxi h, desena2
sub M
jm modifica_dResta
lxi h, desenaR
mov M, a
jmp end1
modifica_dResta:
adi Ah
lxi h, desenaR
mov M, a
lxi h, centena2
mov a, M
adi 1
mov M, a
end1:
pop h
ret

;Subrutina per fer la suma de les centenes

.org 850h
centenes_resta:
push h
lxi h, centena1
mov a, M
lxi h, centena2
sub M
jm modifica_cResta
lxi h, centenaR
mov M, a
jmp end2
modifica_cResta:
adi Ah
lxi h, centenaR
mov M, a
lxi h, carry ; Important per després detectar el overflow
mov a, M
adi 1
mov M, a
end2:
pop h
ret

;###############################################################
;	OPERACIONS LÒGIQUES
;###############################################################
.org 1000h

;###############################################################
;		DECODIFICAR DECIMAL - BINARI
;###############################################################
dec_to_bin:
	mvi B, 0h
	mvi H, 0h
	; En primer lloc gestionem les unitats. Simplement sumem el contingut de les unitats al registre L
	lda unitat1
	mov L, A

		
	; Ara es faran les desenes, Ah tants cops com digui el valor de l'acumulador
	lda desena1
	CPI 00h
	jz hex_centenes_valor1
	mvi C, 0Ah ; 0Ah és  10 en decimal

	loop_desenes_valor1:   
	dad B
	dcr A
	jnz loop_desenes_valor1

	; De la mateixa forma amb les centenes
	hex_centenes_valor1:
      lda centena1
	CPI 00h
	JZ hex_end_valor1
    	mvi C, 64h ; 64h és 100 en decimal
    	loop_centenes_valor1:
    	dad B
    	dcr A
    	jnz loop_centenes_valor1

	hex_end_valor1:
	; Finalment guardem el contingut de L a E i el de H a D (parell DE)
    MOV E, L
    MOV D, H

	; Repetim el mateix procès, ara guardant el resultat al parell BC
	; Cal reiniciar les xifres del parell HL
	MVI H, 0h
	MVI L, 0h
	MVI B, 0h
	MVI C, 0h
    ; Xifra 2
    lda unitat2
    mov L, A

    lda desena2
	CPI 00h
	JZ hex_centenes_valor2
    mvi C, 0Ah
    loop_desenes_valor2:
    dad B
    dcr A
    jnz loop_desenes_valor2

	hex_centenes_valor2:
    lda centena2
	CPI 00h
	JZ hex_end_valor2
    mvi C, 64h

    loop_centenes_valor2:
    dad B
    dcr A
    jnz loop_centenes_valor2

	hex_end_valor2:
    MOV C, L
    MOV B, H
	ret

;###############################################################
;		DECODIFICAR BINARI - DECIMAL
;###############################################################
bin_to_dec:

	MVI B, FFh
	MVI C, 9Ch; FF9Ch es -100 en Ca2
	MVI D, 00h; El nombre de centenes
	MVI E, 00h, El nombre de desenes


	loop1:
		DAD B; Restem 100 a HL mentre es pugui
		JNC loop1_1
		INR D
		JMP loop1

	loop1_1:
		MVI B, 00h
		MVI C, 64h
		DAD B
		 
	MVI B, FFh; 
	MVI C, F6h; Aixo es 10 en Ca2
	loop2:
		DAD B ; Restem 10 a HL mentre es pugui
		JNC loop2_2
		INR E
		JMP loop2
	loop2_2: 

		MVI B, 00h
		MVI C, 0Ah
		DAD B
		


	; Finalment guardem les unitats
	MOV A, L
	LXI H, unitatR
	MOV M, A

	LXI H, desenaR
	MOV M, E

	LXI H, centenaR
	MOV M, D
	ret

;###############################################################
;		OPERACIÓ AND
;###############################################################
; Ara que tenim els nombres en binari, es poden fer les portes que es vulgui
and: 
	PUSH H
	PUSH B
	PUSH D
	call dec_to_bin
	MOV A, B
	ANA D
	MOV H, A
	MOV A, C
	ANA E
	MOV L, A ; El resultat apareix al parell de registres HL
	call bin_to_dec

	POP D
	POP B
	POP H
	ret

;###############################################################
;		OPERACIÓ OR
;###############################################################
or:
		PUSH H
	PUSH B
	PUSH D
	call dec_to_bin
	MOV A, B
	ORA D
	MOV H, A
	MOV A, C
	ORA E
	MOV L, A ; El resultat apareix al parell de registres HL
	call bin_to_dec

	POP D
	POP B
	POP H
	ret

