.data
comptador: .word 10
resultat: .word 0
.text
la a0, comptador 		# S'assigna a a0 l'adreça de comptador
lw a0, 0(a0) 			# Carreguem el valor de 0(a0) en a0
addi a1, zero, 0 		# Assignem a a1 el valor 0 (F_0)
addi a2, zero, 1 		# Assignem a a2 el valor 1 (F_1)
call subrutina		# S'assigna a a0 l'adreça de resultat
sw a3, 4(a0)  		# Es guarda el valor de a1 en 0(a0)
j end2
.text
subrutina:
    addi sp,sp, -12
    sw a1, 0(sp)
    sw a2, 4(sp)
    sw a0, 8(sp)
# És un loop que funciona mentre a0 > 0
loop:
    blez a0, end 		# Condició per tal de continuar el loop
    add a3,a1, a2 		# Definició de Fibonacci
    addi a1, a2, 0 		# Serveix per guardar valor a2 en a1
    addi a2, a3, 0 		# Serveix per guardar valor a3 en a2
    addi a0, a0, -1 		# Es decrementa el valor de a0 en 1
    j loop 		       # Salt incondicional per tal de repetir el loop
end:
    mv a3, a1
    lw a1, 0(sp)
    lw a2, 4(sp)
    lw a0, 8(sp)
    
# Per evitar el while true proposat en el codi de factorial, es fa un 
# salt incondicional a aquesta posició de memòria 

end2:
    nop