//Nom: Cristian Prado Méndez

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "resolLU1.c"

int main(void)
{
    long double tol = 1e-12;
    int n = 5, pivotatge = 1;
    double *det = (double *)calloc(n, sizeof(double));
    double **matriu = (double **)calloc(n, sizeof(double *));
    int *p = NULL;
    for (int i = 0; i < n; i++)
    {
        matriu[i] = (double *)calloc(n, sizeof(double));
        for (int j = 0; j < n; j++)
        {
            matriu[i][j] = pow(sqrt(i + 2), j);
        }
    }
    double norma_a = calculaNorma(matriu, n, n);
    if (pivotatge == 1)
    {
        p = (int *)calloc(n, sizeof(int *));
    }
    int det_si_no = flud(matriu, p, n, tol, det);
    double **l = (double **)calloc(n, sizeof(double *));
    double **u = (double **)calloc(n, sizeof(double *));
    for (int i = 0; i < n; i++)
    {
        l[i] = (double *)calloc(n, sizeof(double));
        u[i] = (double *)calloc(n, sizeof(double));

        for (int j = 0; j < n; j++)
        {
            if (i < j)
            {
                u[i][j] = matriu[i][j];
                l[i][j] = 0;
            }
            else if (i > j)
            {
                l[i][j] = matriu[i][j];
                u[i][j] = 0;
            }
            else
            {
                u[i][j] = matriu[i][j];
                l[i][j] = 1;
            }
        }
    }
    double determinant = 1;
    for (int i = 0; i < n; i++)
    {
        determinant *= u[i][i];
        printf("%lf ", u[i][i]);
    }
    printf("\nEl determinant de la matriu és: %lf \n", determinant);
    double **m_inversa = matriu_inversa(u, l, n);
    double norma_inv = calculaNorma(m_inversa, n, n);
    printf("\nLa norma infinit de la matriu és: %lf \n", norma_a);
    printf("\nLa norma infinit de la matriu inversa és: %lf \n", norma_inv);
    double nombre_condicio = norma_a * norma_inv;
    printf("El nombre de condició de norma infinit és: %lf", nombre_condicio);
}
