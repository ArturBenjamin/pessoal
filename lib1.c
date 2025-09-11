// libnormalize.c

#include "libnormalize.h"

// --- Implementação da função antiga ---
double normalize(double x, double min, double max) {
    if (max - min == 0) {
        return 0.0;
    }
    return (x - min) / (max - min);
}

// --- Implementação da nova função ---
long long int fatorial(int n) {
    // Fatorial não é definido para números negativos.
    if (n < 0) {
        return -1; // Usamos -1 para indicar um erro.
    }
    
    long long int resultado = 1;
    for (int i = 1; i <= n; ++i) {
        resultado *= i;
    }
    return resultado;
}
