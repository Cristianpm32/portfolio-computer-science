// Nom: Cristian Prado Méndez
// harm.c
#include <stdio.h>
int main(void)
{
    float n = 0; // x_n
    float i = 1;
    float n_1 = 2;   // x_n+1
    while (n != n_1) // Continuarà la sèrie fins que x_n = x_n+1
    {
        n_1 = n;
        n = n + 1 / i;
        i++;
    }
    printf("%f \n", n);
    printf("%f \n", n_1);
    printf("%f \n", i);
    n = 0;         // Reiniciem el valor de la sèrie per fer la inversa
    while (i != 0) // Des del valor de l'última iteració fins i = 1
    {
        n += 1 / i;
        i--;
    }
    printf("%f \n", n);
    printf("%f", i);
}
