.data
a: .word 5
b: .word -6
resultat: .word 0
.text
la a0, a
lw a1, 0(a0) # Carreguem a = 0(a0) a a1
lw a2, 4(a0) # Carreguem b = 4(a0) a a2

#Comprovem si a1>=a2 o a1<a2
bge a1, a2, cert # Comprovem si a1>=a2
j fals # Com no s’ha complit a1>=a2, llavors és a1<a2
cert:
    sub a3, a1, a2 # fem la resta a1-a2 i guardem en a3
    j end # Salt incondicional a end
fals:
    sub a3, a2, a1 # fem la resta a2-a1 i guardem en a3
    j end # Salt incondicional a end
end:
    sw a3, 8(a0)