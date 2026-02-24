.data 
Dades: .word 3083, 17
.text # directiva d’inici de programa 
main:
    add a0, zero , zero
    la a3, Dades # a3 actuarà com a punter
    lw a1, 0(a3) 
    lw a2, 4(a3) 
loop: 
    add a0, a0, a1
    addi a2, a2,-1 
    bgtz a2, loop 
end: 
    nop #final de programa 
