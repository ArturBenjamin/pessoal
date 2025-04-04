#include <stdio.h>  /* Standard I/O functions */
#include <stdlib.h> /* Miscellaneous functions (rand, malloc, srand) */
#include <getopt.h> /* get options from system argc/argv */
#include <math.h>   /* Mathematics functions */

/* Definições necessárias */
#define VERSION "1.0"  /* Definição da versão */
int verb = 0;         /* Controle de verbosidade */

/* Protótipos das funções */
void help(void);
void copyr(void);
double bisseccao_raiz_quadrada(double x);
void ex10_init(void);

int main(int argc, char *argv[])
{
    int opt; /* retorno de getopt() */

    /* getopt() opções configuradas:
     *        -h  help
     *        -V  version
     *        -v  verbose
     */
    opterr = 0;
    while ((opt = getopt(argc, argv, "vhV")) != -1)
    {
        switch (opt)
        {
        case 'h':
            help();
            break;
        case 'V':
            copyr();
            break;
        case 'v':
            verb++;
            break;
        case '?':
        default:
            printf("Digite\n\t$man %s\nou\n\t$%s -h\npara ajuda.\n\n", argv[0], argv[0]);
            return EXIT_FAILURE;
        }
    }

    if (verb)
        printf("Nível de verbosidade: %d\n", verb);

    /* Chamada da função de inicialização */
    ex10_init();

    return EXIT_SUCCESS;
}

void help(void)
{
    printf("%s - %s\n", "exN", "Descrição breve");
    printf("\nUso: %s [-h|-v]\n", "exN");
    printf("\nOpções:\n");
    printf("\t-h,  --help\n\t\tExibir esta ajuda.\n");
    printf("\t-V,  --version\n\t\tExibir versão e informações de copyright.\n");
    printf("\t-v,  --verbose\n\t\tAjustar nível de verbosidade (cumulativo).\n");
    printf("\nStatus de saída:\n\t0 se ok.\n\t1 se ocorrer algum erro.\n");
    printf("\nAutor:\n\tEscrito por %s <%s>\n\n", "Ruben Carlo Benante", "rcb@beco.cc");
    exit(EXIT_FAILURE);
}

double bisseccao_raiz_quadrada(double x)
{
    double li = 0; /* limite inferior */
    double ls = x; /* limite superior */
    double c = (ls + li) / 2; /* ponto médio do intervalo */
    double delta = 0.001;

    while (fabs(c * c - x) > delta)
    {
        if (c * c > x)
        {
            ls = c;
        }
        else
        {
            li = c;
        }

        c = (ls + li) / 2.0;
    }

    return c;
}

void copyr(void)
{
    printf("%s - Versão %s\n", "exN", VERSION);
    printf("\nCopyright (C) %d %s <%s>, GNU GPL versão 2 <http://gnu.org/licenses/gpl.html>.\n", 2016, "Ruben Carlo Benante", "rcb@beco.cc");
    printf("Este é um software livre: você pode modificar e redistribuir.\n");
    printf("NÃO HÁ GARANTIA, na extensão permitida por lei.\n\n");
    if (verb > 3)
        printf("Verbose: %d\n", verb); /* -vvvv */
    exit(EXIT_FAILURE);
}

void ex10_init(void)
{
    double numero;

    printf("Digite um número para calcular a raiz quadrada: ");
    scanf("%lf", &numero);

    if (numero < 0)
    {
        printf("Não é possível calcular a raiz quadrada de um número negativo.\n");
    }
    else
    {
        double resultado = bisseccao_raiz_quadrada(numero);
        printf("A raiz quadrada de %.2lf é aproximadamente %.4lf\n", numero, resultado);
    }
}
