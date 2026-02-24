.data 
Dades: .word -2, 3 # Valors d'exemple
.text # directiva d’inici de programa 
main:
    la a3, Dades # a3 actuarà com a punter
    lw a1, 0(a3) 
    lw a2, 4(a3)
    beq a1, a2,mult 
    j diferents
mult:
    mul a0, a1, a2
    j end
diferents:
    bltz a1, possible
    j positiu
positiu:
    bgtz a2, end
    j possible2
possible:
    bltz a2, ca2
    add a0, a1, a2
    sub a6, a1, a2
    j end
possible2:
    add a0, a1, a2
    sub a6, a1, a2
    j end
ca2:
    not a1, a1
    addi a1, a1, 1
    not a2, a2
    addi a2, a2, 1
    sw a1, 8(a3)
    sw a2, 12(a3)
    j end2
end:
    sw a0, 8(a3)
    sw a6, 12(a3)
    nop
end2:
    nop
