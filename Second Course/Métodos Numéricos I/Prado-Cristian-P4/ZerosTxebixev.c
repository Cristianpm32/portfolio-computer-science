// Autor: Cristian Prado Méndez
// Fitxer: ZerosTxebixev.c
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "newtraph.c"

int main(void)
{
    int n = 5;
    double tol = 1e-6;
    double arrel = -1;
    int itermax = 10000;
    double **arrels = (double **)calloc(n, sizeof(double **));
    for (int i = 0; i < n; i++)
    {
        arrels[i] = (double *)calloc(n, sizeof(double *));
    }
    arrels[0][0] = 0;
    double punt_mig;
    for (int i = 1; i < n; i++)
    {
        punt_mig = (-1 + arrels[i - 1][0]) / 2;
        newtraph(i+1, punt_mig, itermax, tol, &arrel);
        arrels[i][0] = arrel;
        for (int j = 1; j < i; j++)
        {
            punt_mig = (arrels[i - 1][j - 1] + arrels[i - 1][j]) / 2;
            newtraph(i+1, punt_mig, itermax, tol, &arrel);
            arrels[i][j] = arrel;
        }
        punt_mig = (arrels[i - 1][i - 1] + 1) / 2;
        newtraph(i+1, punt_mig, itermax, tol, &arrel);
        arrels[i][i] = arrel;
    }

    FILE *fitxer = fopen("arrels.res", "w");
    for (int i = 0; i < n; i++)
    {
        fprintf(fitxer, "Grau %d: \n\n", i + 1);

        for (int j = 0; j <= i; j++)
        {
            fprintf(fitxer, "%.15lf\n", arrels[i][j]);
        }
        fprintf(fitxer, "\n");
    }
}