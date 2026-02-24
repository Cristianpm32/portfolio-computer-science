//Nom: Cristian Prado Méndez
// Arxiu: avalua.c

#include <stdio.h>

double avalua(double z, double* x, double* c, int n){
    double b = c[n-1];
    for(int i = n-2; i >= 0 ; i--){
        b = b*(z-x[i]) + c[i];
    }
    return b;
}