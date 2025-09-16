#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ============================ FUNÇÕES DE MANIPULAÇÃO DE STRING ============================ */
/* Como não estamos usando a libpessoal, definimos as funções diretamente aqui. */

/**
 * @brief Concatena duas strings, alocando memória para a nova string resultante.
 * @param string1 A primeira string.
 * @param string2 A segunda string.
 * @return Um ponteiro para a nova string concatenada. Esta memória deve ser liberada com free().
 */
char *concatenar(const char *string1, const char *string2) {
    size_t total_comprimento = strlen(string1) + strlen(string2) + 1;
    char *resultado = (char *)malloc(total_comprimento * sizeof(char));
    if (resultado == NULL) {
        fprintf(stderr, "Erro: Falha ao alocar memória.\n");
        exit(EXIT_FAILURE);
    }
    strcpy(resultado, string1);
    strcat(resultado, string2);
    return resultado;
}

/**
 * @brief Verifica se uma string começa com um determinado prefixo.
 * @return 1 (verdadeiro) se for prefixo, 0 (falso) caso contrário.
 */
int ePrefixo(const char *str, const char *prefixo) {
    return strncmp(str, prefixo, strlen(prefixo)) == 0;
}

/**
 * @brief Verifica se uma string termina com um determinado sufixo.
 * @return 1 (verdadeiro) se for sufixo, 0 (falso) caso contrário.
 */
int eSufixo(const char *str, const char *sufixo) {
    int str_comprimento = strlen(str);
    int sufixo_comprimento = strlen(sufixo);
    if (str_comprimento >= sufixo_comprimento) {
        return strcmp(str + (str_comprimento - sufixo_comprimento), sufixo) == 0;
    }
    return 0;
}

/**
 * @brief Verifica se uma string contém uma sub-palavra.
 * @return 1 (verdadeiro) se contém, 0 (falso) caso contrário.
 */
int temSubPalavra(const char *str, const char *sub_palavra) {
    return strstr(str, sub_palavra) != NULL;
}

/* ============================ FUNÇÃO PRINCIPAL (TESTE) ============================ */

int main(void) {
    const char *palavra_principal = "programacao";
    const char *pre = "pro";
    const char *suf = "cao";
    const char *sub = "grama";
    const char *nao_pre = "proa";

    printf("--- Teste das Funcoes de String (Programa Independente) ---\n");
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

    // Liberando a memória alocada pela função 'concatenar'
    free(resultado_concatenado);

    return 0;
}
