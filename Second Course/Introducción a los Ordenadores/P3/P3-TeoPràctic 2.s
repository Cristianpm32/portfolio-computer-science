.data
    a: .word 7
    b: .word 3
.text
    la a0, a # Direccionament implícit
    lw a1, 0(a0) # Direccionament indexat
    lw a2, 4(a0) # Direccionament indexat
loop:
    beqz a1, end  # Direccionament relatiu
    addi a1, a1, -1 # Direccionament immediat
    addi a2, a2, 2 # Direccionament immediat
    j loop # Direccionament directe
end:
    sw a1, 0(a0) # Direccionament indexat
    
    
