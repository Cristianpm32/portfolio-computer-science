// Nom: Cristian Prado Méndez
// iterf.c
#include <stdio.h>
int main(void)
{
    float n = 0.1f;
    float error_n = 1.19e-8;
    printf("x_0: %f Error: %e \n", n, error_n);
    for (int i = 1; i < 51; i++)
    {
        error_n = 3.9f * (1 - 2 * n) * error_n;
        n = 3.9 * n * (1 - n);
        printf("x_%d: %f Error: %e \n", i, n, error_n);
    }
}