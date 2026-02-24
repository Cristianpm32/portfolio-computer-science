.data 
Dades: .word 3, 3
.text # directiva d’inici de programa 
main:
add a0, zero, zero
la a3, Dades # a3 actuarà com a punter
lw a1, 0(a3) 
lw a2, 4(a3) 
bgt a1, a2, sum
bgt a2, a1, diff
beq a1, a2, mult
sum:
    add a0, a1, a2
    j end
diff: 
    sub a4, a2, a1
    j end
mult:
    mul a0, a1, a2
    j end
end:
nop #final de programa 
