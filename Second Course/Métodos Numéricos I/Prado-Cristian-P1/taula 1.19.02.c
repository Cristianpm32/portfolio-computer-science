// Nom: Cristian Prado Méndez
// taula.c
#include <stdio.h>
#include <math.h>
int main(void)
{
    double valorx = -0.001;
    double valory = 0;
    FILE *fitxer;                           // Creació variable per tractar fitxers
    fitxer = fopen("taulavalors.txt", "w"); // Creació fitxer
    while (0.001001 >= valorx)
    { // Introduïm els valors al fitxer
        valory = (-280 + 28 * pow(valorx, 2) - pow(valorx, 4)) / 840;
        fprintf(fitxer, "%.15lf          %.15lf\n", valorx, valory);
        valorx = valorx + 0.000001; // Augmentem el valor de x
    }
    fclose(fitxer); // Tanquem el fitxer
}