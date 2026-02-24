// Nom: Cristian Prado Méndez
// iterd.c
#include <stdio.h>
int main(void)
{
    double n = 0.1;
    double error_n = 2.22e-17;
    printf("x_0: %lf Error: %le \n", n, error_n);
    for (int i = 0; i < 50; i++)
    {
        error_n = 3.9 * (1 - 2 * n) * error_n;
        n = 3.9 * n * (1 - n);
        printf("x_%d: %lf Error: %le \n", i + 1, n, error_n);
    }
}