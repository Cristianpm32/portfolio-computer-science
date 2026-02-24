.data
a: .word 6
b: .word 7
resultat: .word 0

.text
    la a0, a
    lw a1, 0(a0)
    lw a2, 4(a0)
    add a3, a1, a2
    sub a4, a1, a2
    mul a5, a3, a4
    sw a5, 8(a0)