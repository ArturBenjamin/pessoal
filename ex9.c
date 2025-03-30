#include <stdio.h>
#include <time.h>

#define SEGUNDOS_POR_ANO 31536000

int main() {
    char nome[50];
    int dia, mes, ano;
    time_t t;
    struct tm data_nasc = {0};
    double segundos_de_vida;

    // Obtém a data atual
    time(&t);
    struct tm *data_atual = localtime(&t);

    // Solicita o nome e a data de nascimento
    printf("Digite seu nome: ");
    scanf("%49s", nome);
    printf("Digite sua data de nascimento (DD MM AAAA): ");
    scanf("%d %d %d", &dia, &mes, &ano);

    // Configura a data de nascimento
    data_nasc.tm_mday = dia;
    data_nasc.tm_mon = mes - 1;
    data_nasc.tm_year = ano - 1900;

    // Calcula a diferença em segundos
    segundos_de_vida = difftime(t, mktime(&data_nasc));

    // Exibe a mensagem
    printf("Parabéns %s, você tem %.0f segundos de vida!\n", nome, segundos_de_vida);

    return 0;
}
