// Nom: Cristian Prado Méndez
// compar.c
#include <stdio.h>
#include <math.h>
int main(void)
{
    double f_xn = 0.1;
    double g_xn = 0.1;
    double error_f_xn = 2.22e-17;
    double error_g_xn = 2.22e-17;
    printf("f(x_n) => x_0: %lf Error: %lf | g(x_n) => x_0: %lf Error: %lf \n", f_xn, error_f_xn, g_xn, error_g_xn);
    for (int i = 0; i < 50; i++)
    {
        error_f_xn = 3.9 * (1 - 2 * f_xn) * error_f_xn;
        error_g_xn = 3.9 * (1 - 2 * g_xn) * error_g_xn;
        f_xn = 3.9 * f_xn * (1 - f_xn);
        g_xn = 3.9 * g_xn - 3.9 * (g_xn * g_xn);
        printf("f(x_n) => x_%d: %lf Error: %le | g(x_n) => x_%d: %lf Error: %le \n", i + 1, f_xn, error_f_xn, i + 1, g_xn, error_g_xn);
    }
}