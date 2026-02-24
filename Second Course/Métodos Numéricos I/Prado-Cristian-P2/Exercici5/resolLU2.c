//Nom: Cristian Prado Méndez

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "resolLU1.c"

int main(void)
{
    long double epsilon = 10e-5, tol = 10.0e-12;
    int n = 6, pivotatge = 0;
    long double increment = (2.0 * epsilon) / 10.0e5;
    printf("Els increments seran de: %LE\n", increment);
    int *p = NULL;
    if (pivotatge == 1)
    {
        p = (int *)calloc(n, sizeof(int *));
    }
    double *det = (double *)calloc(n, sizeof(double));
    for (long double i = 5 - epsilon; i <= 5 + epsilon; i += increment)
    {
        double **matriu = (double **)calloc(n, sizeof(double **));
        for (int j = 0; j < n; j++)
        {
            matriu[j] = (double *)calloc(n, sizeof(double *));
            for (int k = 0; k < n; k++)
            {
                if (k == j)
                {
                    matriu[j][k] = i;
                }
                else
                {
                    matriu[j][k] = -1;
                }
            }
        }
        if (flud(matriu, p, n, tol, det) == 0)
        {
            printf("No s'ha pogut realitzar la factorització LU pel valor lambda = %.15LF \n", i);
        }
    }
}