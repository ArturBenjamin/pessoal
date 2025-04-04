#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Miscellaneous functions (rand, malloc, srand)*/
#include <getopt.h> /* get options from system argc/argv */
#include <math.h>  /* Mathematics functions */

double bisseccao_raiz_quadrada(double x)
{
    double li = 0; /* limite inferior */
    double ls = x; /* limite superior */
    double c = (ls + li) / 2; /* ponto medio do intervalo */
    double delta = 0.001;

    while (fabs(c * c - x) > delta) 
    {
        if (c * c > x) 
        {
            ls = c;
        } else {
            li = c;
        }

        c = (ls + li) / 2.0;
    }

    return c;
}

void ex10_init(void)
{
    IFDEBUG("ex10_init()");
    double numero;

    printf("Digite um número para calcular a raiz quadrada: ");
    scanf("%lf", &numero);

    if (numero < 0) {
        printf("Não é possível calcular a raiz quadrada de um número negativo.\n");
    } else {
        double resultado = bisseccao_raiz_quadrada(numero);
        printf("A raiz quadrada de %.2lf é aproximadamente %.4lf\n", numero, resultado);
    }

    return;
}
