#include <stdio.h>
#include <stdlib.h>      // Necessário para free()
#include "libpessoal.h"  // Inclui sua biblioteca com as novas funções!

int main(void) {
    const char *palavra_principal = "programacao";
    const char *pre = "pro";
    const char *suf = "cao";
    const char *sub = "grama";
    const char *nao_pre = "proa";

    printf("--- Teste das Funcoes de String da Biblioteca ---\n");
    printf("Palavra principal para os testes: \"%s\"\n\n", palavra_principal);

    // --- Teste da função ePrefixo() ---
    printf("1. Testando ePrefixo():\n");
    printf("A palavra \"%s\" comeca com \"%s\"? Resposta: %s\n", palavra_principal, pre, ePrefixo(palavra_principal, pre) ? "Sim" : "Nao");
    printf("A palavra \"%s\" comeca com \"%s\"? Resposta: %s\n", palavra_principal, nao_pre, ePrefixo(palavra_principal, nao_pre) ? "Sim" : "Nao");
    printf("\n");

    // --- Teste da função eSufixo() ---
    printf("2. Testando eSufixo():\n");
    printf("A palavra \"%s\" termina com \"%s\"? Resposta: %s\n", palavra_principal, suf, eSufixo(palavra_principal, suf) ? "Sim" : "Nao");
    printf("A palavra \"%s\" termina com \"%s\"? Resposta: %s\n", palavra_principal, pre, eSufixo(palavra_principal, pre) ? "Sim" : "Nao");
    printf("\n");

    // --- Teste da função temSubPalavra() ---
    printf("3. Testando temSubPalavra():\n");
    printf("A palavra \"%s\" contem \"%s\"? Resposta: %s\n", palavra_principal, sub, temSubPalavra(palavra_principal, sub) ? "Sim" : "Nao");
    printf("A palavra \"%s\" contem \"%s\"? Resposta: %s\n", palavra_principal, "lua", temSubPalavra(palavra_principal, "lua") ? "Sim" : "Nao");
    printf("\n");

    // --- Teste da função concatenar() ---
    printf("4. Testando concatenar():\n");
    const char *parte1 = "biblioteca ";
    const char *parte2 = "pessoal";
    char *resultado_concatenado = concatenar(parte1, parte2);

    printf("Concatenando \"%s\" com \"%s\"...\n", parte1, parte2);
    printf("Resultado: \"%s\"\n", resultado_concatenado);

    // IMPORTANTE: Como 'concatenar' aloca memória, devemos liberá-la
    // quando não precisarmos mais dela para evitar vazamento de memória.
    free(resultado_concatenado);

    return 0;
}
