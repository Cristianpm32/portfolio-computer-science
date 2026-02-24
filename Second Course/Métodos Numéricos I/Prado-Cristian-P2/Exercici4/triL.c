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
double *llegirVector(char nom_fitxer[])
{
    FILE *fitxer = fopen(nom_fitxer, "r");
    if (fitxer == NULL)
    {
        printf("L'arxiu no s'ha pogut obrir.");
        exit(1);
    }
    int n;
    fscanf(fitxer, "%d", &n);
    double *V = (double *)calloc(n, sizeof(double *));
    for (int i = 0; i < n; i++)
    {
        double coef;
        fscanf(fitxer, "%le", &coef);
        V[i] = coef;
    }
    fclose(fitxer);
    return V;
}
double *triL(double **U, double *b, int n)
{
    double sumatori = 0;
    for (int i = 0; i < n; i++)
    {
        sumatori = 0;
        b[i] = b[i] / U[i][i];
        if (i != n - 1)
        {
            for (int j = 0; j <= i; j++)
            {
                sumatori += b[j] * U[i + 1][j];
            }
            b[i + 1] -= sumatori;
        }
    }
    /*printf("Les solucions del sistema d'equacions són: \n");
    for (int k = 0; k < 10; k++)
    {
        printf("x_%d = %lf ", k + 1, b[k]);
    }*/
    return b;
}
/*
int main(void)
{
    char nom_U[10];
    int n, m, l;
    printf("Introdueix el nom del fitxer de la matriu: ");
    scanf("%9s", nom_U);
    FILE *matriu = fopen(nom_U, "r");
    if (matriu == NULL)
    {
        printf("L'arxiu no s'ha pogut obrir.");
        exit(1);
    }
    fscanf(matriu, "%d %d", &n, &m);
    fclose(matriu);
    double **u = llegirMatriu(nom_U);
    printf("Introdueix el nom del fitxer de la matriu de termes independents : ");
    char nom_B[10];
    scanf("%9s", nom_B);
    FILE *vector = fopen(nom_B, "r");
    if (vector == NULL)
    {
        printf("L'arxiu no s'ha pogut obrir.");
        exit(1);
    }
    fscanf(vector, "%d", &l);
    fclose(vector);
    double *b = llegirVector(nom_B);
    printf("La matriu U és la següent: \n");
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%lf ", u[i][j]);
        }
        printf("\n");
    }
    printf("\nLa matriu de termes independents és: \n");
    for (int i = 0; i < l; i++)
    {
        printf("%lf ", b[i]);
    }
    printf("\n");
    triL(u, b, m);
}
*/