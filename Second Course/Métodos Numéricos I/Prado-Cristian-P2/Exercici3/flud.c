//Nom: Cristian Prado Méndez

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

double **llegirMatriu(char nom_fitxer[])
{
    FILE *fitxer = fopen(nom_fitxer, "r");
    if (fitxer == NULL)
    {
        printf("L'arxiu no s'ha pogut obrir.");
        exit(1);
    }
    int n, m;
    fscanf(fitxer, "%d %d", &n, &m);
    double **A = (double **)calloc(n, sizeof(double **));
    for (int i = 0; i < n; i++)
    {
        A[i] = (double *)calloc(m, sizeof(double *));
        for (int j = 0; j < m; j++)
        {
            double coef;
            fscanf(fitxer, "%le", &coef);
            A[i][j] = coef;
        }
    }
    fclose(fitxer);
    return A;
}
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
            }
        }
        printf("\n");
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
    if (nombre_permutacions % 2 != 0 && fabs(determinant) >0)
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
    printf("\n\nDet(A) = ");
    for (int j = 0; j < n; j++)
    {
        determinant *= det[j];
        printf("%lf ", det[j]);
        if (j < n - 1)
        {
            printf("* ");
        }
    }
    printf("= %lf \n\n", determinant);
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
        return 1;
    }
    else
    {
        if (gausspivot(a, p, n, tol, det) == 0)
        {
            return 0;
        }
        return 1;
    }
}
int main(void)
{
    char nom_U[10];
    int n = 0, m, pivotatge = 0;
    printf("Introdueix el nom del fitxer de la matriu: ");
    scanf("%9s", nom_U);
    FILE *matriu = fopen(nom_U, "r");
    fscanf(matriu, "%d %d", &n, &m);
    if (matriu == NULL)
    {
        printf("L'arxiu no s'ha pogut obrir.");
        exit(1);
    }
    fclose(matriu);
    double tol = 0;
    int *p = NULL;
    printf("Introdueix el valor de la tolerància: ");
    scanf("%lf", &tol);
    double **u = llegirMatriu(nom_U);
    double *det = (double *)calloc(n, sizeof(double *));
    printf("Per eliminació gaussiana amb pivotatge prem 1, sense pivotatge 0: ");
    scanf("%d", &pivotatge);
    if (pivotatge == 1)
    {
        p = (int *)calloc(n, sizeof(int *));
    }
    if (flud(u, p, n, tol, det) == 1)
    {
        printf("La factorització LU s'ha pogut realitzar correctament.");
    }
    else
    {
        printf("No s'ha pogut realitzar la factorització LU.");
    }
}