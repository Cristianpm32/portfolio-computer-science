// Autor: Cristian Prado Méndez
// Fitxer: txebixev.c
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void txebixev(int n, double x, double *f, double *df)
{
    double k_1 = 1;
    double k_2 = x;
    double kf_1 = 0;
    double kf_2 = 1;
    double valor_f = 0;
    double valor_df = 0;

    for (int i = 1; i < n; i++)
    {
        valor_f = 2 * x * k_2 - k_1;
        valor_df = 2 * k_2 + 2 * x * kf_2 - kf_1;
        k_1 = k_2;
        k_2 = valor_f;
        kf_1 = kf_2;
        kf_2 = valor_df;
    }
    *f = valor_f;
    *df = valor_df;
}