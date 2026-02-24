//Nom: Cristian Prado Méndez
// Arxiu: trap.c

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double trapezis(double a, double b, int n, double (*af)(double)){
    double x;
    double y = a;
    double aprox = 0;
    for (int i = 1; i<= n; i++){
        x = a + i*(b-a)/n;
        aprox += (x-y)*((af(x)+af(y))/2);
        y = x;
    }
    return aprox;
}