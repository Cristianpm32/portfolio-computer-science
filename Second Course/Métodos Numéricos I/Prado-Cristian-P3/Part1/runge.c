//Nom: Cristian Prado Méndez
// Arxiu: runge.c

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "interpola.c"
#include "avalua.c"

/*
Com que l'exercici 3 i l'exercici 4 eren el mateix però utilitzant les abscisses de Txebitxev  
en comptes d'abscisses equiespaiades, he optat per comentar les línies que no feia servir en cada
exercici. Per tant, si comprovo l'exercici 3, comento les línies que faig servir pel 4, i viceversa.
*/

int main(void)
{
    int n = 50; // Com n és 50, llavors el polinomi serà de grau 49.
    double *x = (double *)calloc(n, sizeof(double *));
    double *f = (double *)calloc(n, sizeof(double *));
    double *c = (double *)calloc(n, sizeof(double *));

    double increment = 10.0 / n; // Serveix pel 3, però no cal comentar-la quan es faci el 4.
    double valor = -5.0; // Serveix pel 3, però no cal comentar-la quan es faci el 4, no afecta.
    for (int i = 0; i < n; i++)
    {
        x[i] = 5 * cos(((2 * i + 1) * M_PI) / (2 * (n + 1))); // Exercici 4
        // x[i] = valor; // Exercici 3
        f[i] = 1 / (1 + pow(x[i], 2));
        // valor += increment; // Exercici 3
    }
    // FILE *fitxer = fopen("abscissesequi.txt", "w"); // Creació fitxer exercici 3
    FILE *fitxer = fopen("abscissestxebi.txt", "w"); // Creació fitxer exercici 4
    interpola(x, f, n, c);
    double valor_polinomi = 0;
    for (double j = -5.0; j <= 5.0; j += 0.1)
    {
        valor_polinomi = avalua(j, x, c, n);
        fprintf(fitxer, "%.15lf          %.15lf\n", j, valor_polinomi);
    }
    fclose(fitxer);
}