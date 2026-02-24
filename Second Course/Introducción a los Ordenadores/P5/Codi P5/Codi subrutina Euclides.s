.data
	a: .word 252
	b: .word 105
	resultat: .word 0
.text 
	la a0, a
	lw a1, 0(a0)
	lw a2, 4(a0)
    call subrutina
    sw a3, 8(a0)	    # Es guarda el valor de a1 en la posició de memòria [a0] + 8
    j end2              # Salt incondicional per evitar tornar a fer la subrutina.
      
.text
subrutina:
    addi sp, sp, -8
    sw a1, 0(sp)
    sw a2, 4(sp)
# Bucle que realitza l'algorisme d'Euclides
loop:
	beq a1, a2, end 	# condició del  while, és a dir si a1 == a2, es salta a end
	bgt a1, a2, cert 	# si es compleix que a1 > a2 
	j fals 			    # salt incondicional si no es compleix que a1 > a2, és a dir vol dir que a1 < 2
cert:
	sub a1, a1, a2		# a1 = a1-a2
	j loop			    # Salt incondicional enrere per tornar a fer el loop
fals:
	sub a2, a2, a1	    # a2 = a2-a1
	j loop			    # Salt incondicional enrere per tornar a fer el loop
end:
    mv a3, a1
    lw a1, 0(sp)
    lw a2, 4(sp)				
    ret
    
# Per evitar el while true proposat en el codi de factorial, es fa un salt incondicional a aquesta posició de memòria 

end2:
    nop                 
                                   