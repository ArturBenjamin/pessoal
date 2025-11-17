#include <stdio.h>

int main() {

    // 1. INICIALIZAÇÃO (Onde começar a contar)
    int i = 1;

    // 2. CONDIÇÃO (Enquanto for verdade, o loop continua)
    while (i <= 5) {

        // O código que será repetido
        printf("Numero: %d\n", i);

        // 3. ATUALIZAÇÃO (O "passo" para a próxima volta)
        i = i + 1; // Fundamental para não criar um loop infinito!
    }

    printf("Loop terminado!\n");
    return 0;
}
