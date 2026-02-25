#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Definició de constants
#define N 5000         // Nombre de punts a calcular
#define IMAX 15        // Iteracions màximes Newton
#define H 0.01         // Pas (distància entre punts)
#define PREC 1e-8      // Precisió desitjada
#define TOL 1e-10      // Tolerància per evitar divisió per zero

// --- FUNCIONS MATEMÀTIQUES ---

// Funció f(x,y) = 0 que defineix la corba
double f(double x, double y) {
    return 2*pow(x,4) + 3*pow(x,2) - 4*x + pow(y,2) - 7*y + pow(x,3)*y + exp(x+y) - x*sin(y) - 8;
}

// Derivada parcial respecte a x
double df_dx(double x, double y) {
    return 8*pow(x,3) + 6*x - 4 + 3*pow(x,2)*y + exp(x+y) - sin(y);
}

// Derivada parcial respecte a y
double df_dy(double x, double y) {
    return 2*y - 7 + pow(x,3) + exp(x+y) - x*cos(y);
}

// --- CERCA DEL PUNT INICIAL (TALL AMB EIXOS) ---

// Cerca un punt inicial a l'eix Y (x=0) usant Newton a dimensió n=1.
// Retorna 1 si convergeix, 0 si no. El resultat es guarda a *y_sortida.
int trobar_tall_eix_Y(double *y_sortida) {
    double x = 0.0;   // Es fixa x = 0
    double y = 0.0;   // Valor inicial per a y
    int i;
    
    for (i = 0; i < IMAX; i++) {
        double valor_f = f(x, y);
        double deriv = df_dy(x, y); 

        // Es comprova que la derivada no sigui nul·la
        if (fabs(deriv) < TOL) return 0; 
        // Actualització de y
        y = y - valor_f / deriv;

        // Criteri d'aturada
        if (fabs(valor_f) < PREC) {
            *y_sortida = y;
            return 1; 
        }
    }
    return 0; 
}

// --- CÀLCUL DEL VECTOR TANGENT ---

// Calcula el vector tangent unitari (v, w) en el punt (x, y).
// Utilitza el vector anterior (v_ant, w_ant) per mantenir el sentit de recorregut.
void calcular_tangent(double x, double y, double v_ant, double w_ant, double *v_sortida, double *w_sortida) {
    double fx = df_dx(x, y);
    double fy = df_dy(x, y);

    // El vector tangent és ortogonal al gradient: (-fy, fx)
    double tx = -fy;
    double ty = fx;

    // Normalització del vector
    double modul = sqrt(tx*tx + ty*ty);
    if (modul < TOL) { 
        tx = 0; ty = 0; 
    } else { 
        tx /= modul; ty /= modul; 
    }

    // Control del sentit: producte escalar ha de ser positiu
    // Si és la primera iteració (v_ant=0), s'accepta el sentit per defecte
    if ((v_ant != 0.0 || w_ant != 0.0) && (tx * v_ant + ty * w_ant < 0)) {
        tx = -tx;
        ty = -ty;
    }

    *v_sortida = tx;
    *w_sortida = ty;
}

// --- CORRECCIÓ AMB MÈTODE DE NEWTON---

// Resol el sistema per trobar el punt sobre la corba a distància H del punt anterior
// Retorna 1 si convergeix, 0 si no.
int correccio_newton(double x_pred, double y_pred, double x_ant, double y_ant, double *x_corr, double *y_corr) {
    double x = x_pred;
    double y = y_pred;
    int i;

    for(i = 0; i < IMAX; i++) {
        double F1 = f(x, y);
        // Equació de distància: (x - x_ant)^2 + (y - y_ant)^2 - H^2 = 0
        double F2 = pow(x - x_ant, 2) + pow(y - y_ant, 2) - pow(H, 2);

        // Comprovació de la convergència (norma del vector de funcions)
        if (sqrt(F1*F1 + F2*F2) < PREC) {
            *x_corr = x;
            *y_corr = y;
            return 1;
        }

        // Càlcul de la matriu Jacobiana del sistema
        double J11 = df_dx(x, y);
        double J12 = df_dy(x, y);
        double J21 = 2 * (x - x_ant);
        double J22 = 2 * (y - y_ant);

        double det = J11 * J22 - J12 * J21;
        
        // Es verifica que el determinant no sigui nul
        if (fabs(det) < TOL) return 0;

        // Resolució per la regla de Cramer per obtenir el desplaçament (dx, dy)
        double dx = (J22 * (-F1) - J12 * (-F2)) / det;
        double dy = (-J21 * (-F1) + J11 * (-F2)) / det;

        // Actualització dels valors
        x += dx;
        y += dy;
    }
    return 0; // No s'ha assolit la convergència
}

// --- MAIN ---

int main() {
    // Vectors per emmagatzemar la trajectòria
    double x_sol[N];
    double y_sol[N];
    
    // Variables per als vectors tangents
    double v = 0.0, w = 0.0;
    double v_ant = 0.0, w_ant = 0.0;

    // Pas 1: Es busca el punt inicial a l'eix Y
    double y_inicial;
    x_sol[0] = 0.0; 
    
    if (!trobar_tall_eix_Y(&y_inicial)) {
        return 1; // Es finalitza si no es troba punt inicial
    }
    y_sol[0] = y_inicial;

    // Obertura del fitxer per escriptura
    FILE *fitxer = fopen("dades_corba.txt", "w");
    if (fitxer == NULL) return 1;
    
    // S'escriu el primer punt al fitxer
    fprintf(fitxer, "%f %f\n", x_sol[0], y_sol[0]);

    // Pas 2: Bucle de continuació
    for (int i = 0; i < N - 1; i++) {
        
        // a) Càlcul del vector tangent
        calcular_tangent(x_sol[i], y_sol[i], v_ant, w_ant, &v, &w);
        v_ant = v;
        w_ant = w;

        // b) Predicció (Punt aproximat a distància H sobre la tangent)
        double x_pred = x_sol[i] + H * v;
        double y_pred = y_sol[i] + H * w;

        // c) Correcció (Tornar a la corba mantenint la distància H)
        if (!correccio_newton(x_pred, y_pred, x_sol[i], y_sol[i], &x_sol[i+1], &y_sol[i+1])) {
            break; // S'atura si el mètode divergeix
        }

        // S'escriu el nou punt al fitxer
        fprintf(fitxer, "%f %f\n", x_sol[i+1], y_sol[i+1]);
    }

    fclose(fitxer);
    return 0;
}