#include <stdio.h>
#include <math.h>

// Função para calcular raiz quadrada pelo método da bissecção
double raiz_bisseccao(double numero) {
    double esquerda = 0, direita = numero, meio;
    double precisao = 0.00001; // Precisão desejada
    
    if (numero < 1) {
        direita = 1; // Para números entre 0 e 1
    }
    
    while ((direita - esquerda) > precisao) {
        meio = (esquerda + direita) / 2;
        if (meio * meio > numero) {
            direita = meio;
        } else {
            esquerda = meio;
        }
    }
    
    return (esquerda + direita) / 2;
}

int main() {
    double numero, raiz, raiz_bis;
    
    // Solicita um número ao usuário
    printf("Digite um número: ");
    scanf("%lf", &numero);
    
    // Verifica se o número é não negativo
    if (numero < 0) {
        printf("Não é possível calcular a raiz quadrada de um número negativo.\n");
    } else {
        // Calcula a raiz quadrada usando sqrt()
        raiz = sqrt(numero);
        
        // Calcula a raiz quadrada pelo método da bissecção
        raiz_bis = raiz_bisseccao(numero);
        
        printf("A raiz quadrada de %.2lf pelo método sqrt() é %.5lf\n", numero, raiz);
        printf("A raiz quadrada de %.2lf pelo método da bissecção é %.5lf\n", numero, raiz_bis);
    }
    
    return 0;
}
