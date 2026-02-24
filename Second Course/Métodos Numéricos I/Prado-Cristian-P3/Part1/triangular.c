//Nom: Cristian Prado Méndez
// Arxiu: triangular.c

#include <stdio.h>
void resolSistema(double **U, double *f, double *c, int n)
{
    double sumatori = 0;
    for (int i = 0; i < n; i++)
    {
        sumatori = 0;
        for (int j = 0; j < i; j++)
        {
            sumatori += c[j] * U[i][j];
        }
        c[i] = (f[i] - sumatori)/U[i][i];
    }
}