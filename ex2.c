// ex2.c

#include <stdio.h>
#include "libnormalize.h"

int main() {
    printf("--- Testes da Funcao de Normalizacao ---\n");
    // ... (testes da função normalize que já estavam aqui) ...
    double resultado1 = normalize(15.0, 10.0, 20.0);
    printf("Resultado normalize: %f\n", resultado1);

    printf("\n--- Testes da Funcao Fatorial ---\n");
    
    // Teste Fatorial 1: Fatorial de 5
    int num1 = 5;
    long long int fat1 = fatorial(num1);
    printf("O fatorial de %d eh: %lld\n", num1, fat1); // %lld para long long

    // Teste Fatorial 2: Fatorial de 0
    int num2 = 0;
    long long int fat2 = fatorial(num2);
    printf("O fatorial de %d eh: %lld\n", num2, fat2);

    // Teste Fatorial 3: Fatorial de número grande
    int num3 = 15;
    long long int fat3 = fatorial(num3);
    printf("O fatorial de %d eh: %lld\n", num3, fat3);

    // Teste Fatorial 4: Teste de erro (número negativo)
    int num4 = -4;
    long long int fat4 = fatorial(num4);
    printf("O fatorial de %d eh: %lld (retorno -1 indica erro)\n", num4, fat4);

    return 0;
}
