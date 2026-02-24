// Autor: Cristian Prado Méndez
// Fitxer: newtraph.c
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "txebixev.c"

int newtraph(int n, double x0, int iter, double tol, double *arrel)
{
    double f;
    double df;
    double x_1;
    double x_0 = x0;
    for (int i = 0; i < iter; i++)
    {
        txebixev(n, x_0, &f, &df);
        x_1 = x_0 - (f) / (df);
        if (fabs(x_1 - x_0) < tol || fabs(f) < tol)
        {
            *arrel = x_0;
            return 0;
        }
        x_0 = x_1;
    }
    return -1;
}