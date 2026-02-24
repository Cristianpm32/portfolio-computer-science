//Nom: Cristian Prado Méndez
// Arxiu: taula.c

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "trap.c"

/*
Aquesta funció és la que assignarem al punter *af. En particular, retorna el valor de la funció g(x)
en l'abscissa que se li passa per paràmetre.
*/
double funcio_g(double x)
{
    return exp(sin(x));
}

int main(void)
{
    double n;
    double (*af)(double) = funcio_g;
    double b_1;
    double integral = 0;
    FILE *fitxer = fopen("taula.res", "w");
    for (int i = 0; i <= 20; i++)
    {
        b_1 = i * M_PI / 10;
        n = (int) sqrt(pow(b_1, 3)*exp(1) / 12e-8);
        integral = trapezis(0, b_1, n, af);
        fprintf(fitxer, "%.15lf          %.15lf\n", b_1, integral);
    }
}