//Nom: Cristian Prado Méndez

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "triL.c"
#include "triU.c"

double gausspivot(double **a, int *p, int n, double tol, double *det)
{
    int nombre_permutacions = 0;
    double determinant = 1; // Per conveniència, ja que el producte s'anul·laria si determinant = 0;
    for (int i = 0; i < n; i++)
    {
        double pivot = a[i][i];
        int fila = i;
        for (int k = i; k < n; k++)
        {
            if (fabs(a[k][i]) > tol && fabs(a[k][i]) > fabs(pivot))
            {
                pivot = a[k][i];
                fila = k;
            }
            else if (fabs(a[k][i]) < tol)
            {
                a[k][i] = 0;
            }
        }
        if (fila != i)
        {
            int auxperm = p[fila];
            p[fila] = p[i];
            p[i] = auxperm;
            nombre_permutacions++;
            double *aux1 = a[fila];
            a[fila] = a[i];
            a[i] = aux1;
        }
        for (int j = i + 1; j < n; j++)
        {
            a[j][i] = a[j][i] / a[i][i];
            for (int m = i + 1; m < n; m++)
            {
                a[j][m] = a[j][m] - a[i][m] * a[j][i];
                if (fabs(a[j][m]) < tol)
                {
                    a[j][m] = 0;
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (fabs(a[i][i]) > tol)
        {
            det[i] = a[i][i];
        }
        else
        {
            det[i] = 0;
        }
    }
    /* det(AB) = det(A)det(B); PA = LU => Det(PA) = det(LU) => +-det(A) = det(L)det(U), en funció de
    si el nombre de permutacions és parell (+) o senar (-).
    det(L)= 1 per ser triangular inferior amb la diagonal plena de 1's =>  +-det(A) = det(U) */
    for (int j = 0; j < n; j++)
    {
        determinant *= det[j];
    }
    if (nombre_permutacions % 2 != 0 && fabs(determinant) > 0)
    {
        determinant = -determinant;
    }
    return determinant;
}
double gauss_sensepivot(double **a, int n, double tol, double *det)
{
    double determinant = 1; // Per conveniència, ja que el producte s'anul·laria si determinant = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (fabs(a[j][i]) > tol)
            {
                a[j][i] = a[j][i] / a[i][i];
            }
            else
            {
                a[j][i] = 0;
            }
            for (int k = i + 1; k < n; k++)
            {
                a[j][k] = a[j][k] - a[i][k] * a[j][i];
                if (fabs(a[j][k]) < tol)
                {
                    a[j][k] = 0;
                }
            }
        }
    }
    for (int i = 0; i < n; i++)
    {
        if (fabs(a[i][i]) > tol)
        {
            det[i] = a[i][i];
        }
        else
        {
            det[i] = 0;
        }
    }
    /* det(AB) = det(A)det(B); A = LU => Det(A) = det(LU).
    det(L)= 1 per ser triangular inferior amb la diagonal plena de 1's =>  det(A) = det(U) */
    for (int j = 0; j < n; j++)
    {
        determinant *= det[j];
    }
    return determinant;
}
int flud(double **a, int *p, int n, double tol, double *det)
{
    if (p == NULL)
    {
        if (gauss_sensepivot(a, n, tol, det) == 0)
        {
            return 0;
        }
    }
    else
    {
        if (gausspivot(a, p, n, tol, det) == 0)
        {
            return 0;
        }
    }
    return 1;
}
double **permutaMatriu(double **b, int *p, int n, int m)
{
    for (int i = 0; i < n - 1; i++)
    {
        double *aux1 = b[p[i]];
        b[p[i]] = b[i];
        b[i] = aux1;
    }
    return b;
}
double **matriu_inversa(double **u, double **l, int n)
{
    double sumatori = 0;
    double **matriu_inversa = (double **)calloc(n, sizeof(double **));
    for (int i = 0; i < n; i++)
    {
        double *identitat = (double *)calloc(n, sizeof(double *));
        identitat[i] = 1;
        double *aux = triL(l, identitat, n);
        matriu_inversa[i] = triU(u, aux, n);
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            double aux = matriu_inversa[i][j];
            matriu_inversa[i][j] = matriu_inversa[j][i];
            matriu_inversa[j][i] = aux;
        }
    }
    return matriu_inversa;
}
double **resolsistema(double **a, double **b, int n, int m)
{
    double **x = (double **)calloc(n, sizeof(double *));
    double sumatori = 0;
    for (int i = 0; i < n; i++)
    {
        x[i] = (double *)calloc(m, sizeof(double));
        for (int j = 0; j < m; j++)
        {
            sumatori = 0;
            for (int k = 0; k < n; k++)
            {
                sumatori += a[i][k] * b[k][j];
            }
            x[i][j] = sumatori;
        }
    }
    return x;
}
double calculaNorma(double **matriu, int n, int m)
{
    double sumatori_actual = 0;
    double sumatori_max = 0;
    for (int i = 0; i < n; i++)
    {
        sumatori_actual = 0;
        for (int j = 0; j < m; j++)
        {
            sumatori_actual += fabs(matriu[i][j]);
        }
        if (sumatori_actual > sumatori_max)
        {
            sumatori_max = sumatori_actual;
        }
    }
    return sumatori_max;
}
