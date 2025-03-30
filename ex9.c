#include <stdio.h>
#include <time.h>

#define SEGUNDOS_POR_ANO 31536000 // Aproximação considerando anos não bissextos

int main() {
    char nome[50];
    int dia, mes, ano;
    time_t t;
    struct tm nascimento = {0};
    double segundos_de_vida;

    // Solicita os dados ao usuário
    printf("Digite seu nome: ");
    fgets(nome, sizeof(nome), stdin);
    
    printf("Digite sua data de nascimento (DD MM AAAA): ");
    scanf("%d %d %d", &dia, &mes, &ano);
    
    // Obtém o tempo atual
    time(&t);
    struct tm *tempo_atual = localtime(&t);
    
    // Configura a estrutura de data de nascimento
    nascimento.tm_mday = dia;
    nascimento.tm_mon = mes - 1; // Meses em struct tm começam do zero
    nascimento.tm_year = ano - 1900; // Anos em struct tm começam de 1900
    
    // Calcula o tempo de vida em segundos
    segundos_de_vida = difftime(t, mktime(&nascimento));
    
    // Remove o caractere de nova linha do nome
    if (nome[strlen(nome) - 1] == '\n') {
        nome[strlen(nome) - 1] = '\0';
    }
    
    // Exibe a mensagem
    printf("Parabéns %s, você tem %.0f segundos de vida!\n", nome, segundos_de_vida);
    
    return 0;
}
