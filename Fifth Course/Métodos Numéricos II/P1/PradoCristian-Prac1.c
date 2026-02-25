#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

// Definició de constants

#define ITER_MAX 100000
#define TOL 1e-8
#define N 50
#define H (1.0/(N+1))

// Definició de funcions. Aquestes funcions poden ser modificades segons el problema específic. En
// aquest cas, es defineixen funcions constants per a p(x), q(x), r(x) i f(x), pròpies de
// l'oscil·lador harmònic simple.

// Funcions p(x), q(x), r(x) i f(x)
double p(double x) {
    return 1.0;
}

double q(double x) {
    return 0.1;
}

double r(double x) {
    return 1.0;
}

double f(double x) {
    return 0.0;
}

// Funcions per construir les diagonals de la matriu tridiagonal i el vector del sistema

// Funcions per obtenir les diagonals principal, inferior i superior
double* diagonal_principal(int n){
    double *diag_prin = (double*)malloc(n * sizeof(double));
    for(int i = 0; i < n; i++){
        diag_prin[i] = (-2*p((i+1)*H) + r((i+1)*H)*H*H) / (H*H); // Inicialitzem amb zeros
    }
    return diag_prin;
}
double* diagonal_inferior(int n){
    double *diag_infer = (double*)malloc((n-1) * sizeof(double));
    for(int i = 0; i < n-1; i++){
        diag_infer[i] = (2*p((i+2)*H) - q((i+2)*H)*H) / (2*H*H); // Inicialitzem amb zeros
    }
    return diag_infer;
}
double* diagonal_superior(int n){
    double *diag_super = (double*)malloc((n-1) * sizeof(double));
    for(int i = 0; i < n-1; i++){
        diag_super[i] = (2*p((i+1)*H) + q((i+1)*H)*H) / (2*H*H); // Inicialitzem amb zeros
    }
    return diag_super;
}

// Vector del sistema, termes independents. Aprofitem que y_0 = a i y_(n+1) = b per expressar f_1 i f_n
double* system_vector_f(int n, double a, double b){
    double *syst_vector = (double*)malloc(n * sizeof(double));
    syst_vector[0] = f(H)-((2*p(H) - q(H)*H) / (2*H*H))*a; 
    for(int i = 1; i < n; i++){
        syst_vector[i] = f((i+1)*H);
    }
    syst_vector[n-1] = f(n*H)-((2*p(n*H) + q(n*H)*H) / (2*H*H))*b;
    return syst_vector;
}

// Solució exacta de l'oscil·lador harmònic simple per calcular l'error
double solucio_exacta(double x) {
    // Oscil·lador harmònic simple: y(x) = sin(x)/sin(1)
    return sin(x)/sin(1.0);
}

// Càlcul de l'error màxim entre la solució numèrica i l'exacta
double error(double *x_sol){
    double max_error = 0.0;
    for(int i = 0; i < N; i++){
        double x_i = (i+1)*H;
        double exacta = solucio_exacta(x_i);
        double err = fabs(x_sol[i] - exacta);
        if(err > max_error){
            max_error = err;
        }
    }
    return max_error;
}

// Les normes són equivalents en K^n, així que podem utilitzar qualsevol. En el nostre cas utilitzarem la norma 2
bool convergencia(double *x_old, double *x_new){
    // Comprovem si s'ha assolit la convergència
    double norm = 0.0;
    for(int i = 0; i < N; i++){
        norm += (x_new[i] - x_old[i]) * (x_new[i] - x_old[i]);
    }
    norm = sqrt(norm);

    return norm < TOL;
}

// Implementació dels mètodes iteratius
int jacobi( double a, double b, double *D, double *L, double *U, double *b_vector, double *x_sol){
    // Implementació del mètode de Jacobi. A causa de la estructura de la matriu (tridiagonal), només calen les diagonals
    // Per tal d'obtenir els valors de x_k+1 en cada iteració, només caldran 2 termes del sumatori
    double *x_old = (double*)malloc(N * sizeof(double));
    double *x_new = (double*)malloc(N * sizeof(double));
    int num_iter = 0;
    bool converge = false;
    for(int i = 0; i < N; i++){
        x_old[i] = 0.0; // Inicialitzem amb uns per evitar problemes amb la convergència
        x_new[i] = 1.0; // Inicialitzem amb uns per evitar problemes amb la convergència
    }
    while((!converge) && (num_iter < ITER_MAX)){
        for(int i = 0; i < N; i++){
            double sum_1 = 0.0;
            double sum_2 = 0.0;
            if(i > 0){
                sum_1= L[i-1] * x_old[i-1];
            }
            if(i < N-1){
                sum_2 += U[i] * x_old[i+1];
            }
            x_new[i] = (b_vector[i] - sum_1 - sum_2) / D[i];
        }

        converge = convergencia(x_old, x_new);
        // Actualitzem x_old per a la següent iteració
        for(int i = 0; i < N; i++){
            x_old[i] = x_new[i];
        }
        num_iter++;
    }
    for (int i = 0; i < N; i++) {
        x_sol[i] = x_new[i];
    }
    free(x_old);
    free(x_new);
    return num_iter;
}

int gauss_seidel( double a, double b, double *D, double *L, double *U, double *b_vector, double *x_sol){
    // Implementació del mètode de Gauss-Seidel. A causa de la estructura de la matriu (tridiagonal), només calen les diagonals
    // Per tal d'obtenir els valors de x_k+1 en cada iteració, només caldrà un terme de cada sumatori
    double *x_old = (double*)malloc(N * sizeof(double));
    double *x_new = (double*)malloc(N * sizeof(double));
    int num_iter = 0;
    bool converge = false;
    for(int i = 0; i < N; i++){
        x_old[i] = 0.0; // Inicialitzem amb zeros
        x_new[i] = 1.0; // Inicialitzem amb uns per evitar problemes amb la convergència
    }
    while((!converge )&& (num_iter < ITER_MAX)){
        for(int i = 0; i < N; i++){
            double sum_1 = 0.0;
            double sum_2 = 0.0;
            if(i > 0){
                sum_1 = L[i-1] * x_new[i-1]; // Utilitzem el valor més recent
            }
            if(i < N-1){
                sum_2 = U[i] * x_old[i+1]; // Utilitzem el valor de l'iteració anterior
            }
            x_new[i] = (b_vector[i] - sum_1 - sum_2) / D[i];
        }
        converge = convergencia(x_old, x_new);
        // Actualitzem x_old per a la següent iteració
        for(int i = 0; i < N; i++){
            x_old[i] = x_new[i];
        }
        num_iter++;
    }
    for (int i = 0; i < N; i++) {
        x_sol[i] = x_new[i];
    }
    free(x_old);
    free(x_new);
    return num_iter;

}

int sor(double a, double omega, double b, double *D, double *L, double *U, double *b_vector, double *x_sol){
    // Implementació del mètode SOR. A causa de la estructura de la matriu (tridiagonal), només calen les diagonals
    double *x_old = (double*)malloc(N * sizeof(double));
    double *x_new = (double*)malloc(N * sizeof(double));
    int num_iter = 0;
    bool converge = false;
    for(int i = 0; i < N; i++){
        x_old[i] = 0.0; // Inicialitzem amb zeros
        x_new[i] = 1.0; // Inicialitzem amb uns per evitar problemes amb la convergència
    }
    while((!converge) && (num_iter < ITER_MAX)){
        for(int i = 0; i < N; i++){
            double sum_r_1 = 0.0;
            double sum_r_2 = 0.0;
            double r = 0.0; 
            if(i > 0){
                sum_r_1 = L[i-1] * x_new[i-1]; // Utilitzem el valor més recent
            }
            if(i < N-1){

                sum_r_2 = U[i] * x_old[i+1];

            }
            r = (b_vector[i] - sum_r_1 - sum_r_2 - D[i] * x_old[i]) / D[i];
            x_new[i] = x_old[i] + omega * r;
        }
        converge = convergencia(x_old, x_new);
        // Actualitzem x_old per a la següent iteració
        for(int i = 0; i < N; i++){
            x_old[i] = x_new[i];
        }
        num_iter++;
    }
    for (int i = 0; i < N; i++) {
        x_sol[i] = x_new[i];
    }
    free(x_old);
    free(x_new);
    return num_iter;
}

// Funció per trobar l'omega òptim. Prova valors d'omega entre 0.01 i 2.0 amb un pas de 0.01
int optim_omega(double a, double b, double *D, double *L, double *U, double *b_vector, double *x_sol){
    int min_iter = ITER_MAX;
    double best_omega = 1.0;
    for (double omega = 0.01; omega < 2.0; omega += 0.01) {
        int iters = sor(a, omega, b, D, L, U, b_vector, x_sol);
        if (iters < min_iter) {
            min_iter = iters;
            best_omega = omega;
        }
    }
    printf("Óptim omega: %f amb %d iteracions\n", best_omega, min_iter);
    return min_iter;
}
int main() {
    double a = 0.0; // Condició de contorn a x=0
    double b = 1.0; // Condició de contorn a x=1
    double *D = diagonal_principal(N);
    double *L = diagonal_inferior(N);
    double *U = diagonal_superior(N);
    double *b_vector = system_vector_f(N, a, b);
    double *x_sol = (double*)malloc(N * sizeof(double));
    int num_iterats;
    int metode;
    // Demanem a l'usuari quin mètode vol utilitzar
    printf("Selecciona el mètode iteratiu:\n1. Jacobi\n2. Gauss-Seidel\n3. SOR\n");
    scanf("%d", &metode);
    switch(metode) {
        case 1:
            printf("Mètode seleccionat: Jacobi\n");
            num_iterats = jacobi(a, b, D, L, U, b_vector, x_sol);
            printf("Nombre d'iteracions Jacobi: %d\n", num_iterats);
            break;
        case 2:
            printf("Mètode seleccionat: Gauss-Seidel\n");
            num_iterats = gauss_seidel(a, b, D, L, U, b_vector, x_sol);
            printf("Nombre d'iteracions Gauss-Seidel: %d\n", num_iterats);
            break;
        case 3:
            printf("Mètode seleccionat: SOR\n");
            num_iterats = optim_omega(a, b, D, L, U, b_vector, x_sol);
            break;
        default:
            printf("Mètode no vàlid. Si us plau, selecciona 1, 2 o 3.\n");
            return 1;
    }

    // Una vegada tenim el vector solució, si en sabem la solució exacta podem calcular l'error que hem comès
    // Si no la sabem, evidentment aquesta part no es pot fer. Comentem aquesta part per defecte.
    // Serveix per l'oscil·lador harmònic simple

    /*
        double max_err = error(x_sol);
        printf("Error màxim: %e\n", max_err);
    */


    // Alliberem la memòria
    free(D);
    free(L);
    free(U);
    free(b_vector);
    free(x_sol);
    return 0;
}
