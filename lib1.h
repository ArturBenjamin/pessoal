// libnormalize.h

#ifndef LIBNORMALIZE_H
#define LIBNORMALIZE_H

// --- Função antiga ---
double normalize(double x, double min, double max);

// --- Nova função ---
/**
 * @brief Calcula o fatorial de um número inteiro não negativo.
 *
 * @param n O número para o qual o fatorial será calculado.
 * @return O valor do fatorial como um long long int. Retorna -1 se
 * o número for negativo, pois o fatorial não é definido para negativos.
 */
long long int fatorial(int n);

#endif // LIBNORMALIZE_H
