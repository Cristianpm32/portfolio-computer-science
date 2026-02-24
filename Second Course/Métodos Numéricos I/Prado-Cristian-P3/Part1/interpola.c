//Nom: Cristian Prado Méndez
// Arxiu: interpola.c

#include <stdio.h>
#include <stdlib.h>
#include "triangular.c"
void interpola(double* x, double* f, int n, double* c){
    double **matriu = (double**)calloc(n, sizeof(double**));
    for(int i = 0; i < n; i++){
        matriu[i] =(double*)calloc(n, sizeof(double*));
        matriu[i][0] = 1;
        for(int j = 1; j <= i; j++){
            matriu[i][j] = (x[i]-x[j-1])*matriu[i][j-1];
        }
    }
    resolSistema(matriu, f,c, n);
}