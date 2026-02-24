.data
    mat1: .word 1,2,3,4,5
    mat2: .word 6,7,8,9,0
    mat3: .word 0,0,0,0,0

.text 
    main:
        la a0, mat1 # Direcció de mat1
        la a4, mat2 # Direcció de mat2
        
# Tenint en compte que inicialment 0(a0) representa el primer element de mat1
# i que 20(a0) el primer element de mat2, ens mourem per les matriu mantenint aquesta distància entre posicions.
# Per altra banda, el primer element de mat3 està en 40(a0)
    loop:
        lw a1, 0(a0) # Carreguem el valor de la posició n de mat1
        lw a2, 20(a0) # Carreguem el valor de la posició n de mat2
        add a3, a2, a1 # Fem la suma dels continguts d'aquestes posicions
        sw a3, 40(a0) # Guardem el resultat de la suma
        addi a0,a0,4 # Incrementem a0 per tal d'anar a la següent posició de memòria de 
        beq a0, a4, end # Si s'ha arribat a la primera posició de mat1, sortim del bucle
        j loop    
    end:
        nop