/*****************************************************************************
 * polo.c                                   Version 20180714.101818        *
 * *
 * Calculadora Polonesa usando Pilhas                                      *
 * Copyright (C) 2016-2018    by Ruben Carlo Benante                       *
 *****************************************************************************
 * This program is free software; you can redistribute it and/or modify    *
 * it under the terms of the GNU General Public License as published by    *
 * the Free Software Foundation; either version 2 of the License.          *
 * *
 * This program is distributed in the hope that it will be useful,         *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 * *
 * You should have received a copy of the GNU General Public License       *
 * along with this program; if not, write to the                           *
 * Free Software Foundation, Inc.,                                         *
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <ctype.h>
#include <limits.h> /* Para INT_MAX e INT_MIN */
#include "polo.h"

int main(int argc, char *argv[])
{
    int opt;
    pilha_t *p = NULL; /* Inicia a pilha como vazia */

    IFDEBUG("Starting optarg loop...");

    opterr = 0;
    while((opt = getopt(argc, argv, "hV")) != EOF) /* Removido 'v' */
    {
        switch(opt)
        {
            case 'h':
                help();
                break;
            case 'V':
                copyr();
                break;
            /* Removido case 'v' */
            case '?':
            default:
                fprintf(stderr, "Opção inválida. Use -h para ajuda.\n");
                return EXIT_FAILURE;
        }
    }

    if (argc == optind)
    {
        fprintf(stderr, "Erro: Nenhuma expressão fornecida.\nUse -h para ajuda.\n");
        return EXIT_FAILURE;
    }

    /* Processa cada argumento da linha de comando */
    for (int i = optind; i < argc; i++)
    {
        char *token = argv[i];

        /* Se for um operador */
        if (strlen(token) == 1 && strchr("+-*/", token[0]))
        {
            if (size(p) < 2)
            {
                fprintf(stderr, "Erro: Operandos insuficientes para o operador '%s'.\n", token);
                clean(&p);
                return EXIT_FAILURE;
            }

            info_t *op2_info = pop(&p);
            info_t *op1_info = pop(&p);

            int op1 = op1_info->val;
            int op2 = op2_info->val;
            int resultado = 0;

            switch (token[0])
            {
                case '+':
                    resultado = op1 + op2;
                    break;
                case '-':
                    resultado = op1 - op2;
                    break;
                case '*':
                    resultado = op1 * op2;
                    break;
                case '/':
                    if (op2 == 0)
                    {
                        fprintf(stderr, "Erro: Divisão por zero.\n");
                        free(op1_info);
                        free(op2_info);
                        clean(&p);
                        return EXIT_FAILURE;
                    }
                    resultado = op1 / op2;
                    break;
            }
            
            free(op1_info); /* Libera a memória da informação que não será mais usada */
            free(op2_info);

            info_t info_res;
            info_res.val = resultado;
            push(&p, info_res);
        }
        /* Senão, tenta converter para número */
        else
        {
            char *endptr;
            long val;
            errno = 0; /* Reseta errno antes da chamada */

            val = strtol(token, &endptr, 10);

            /* Verifica erros de conversão */
            if (errno == ERANGE || val > INT_MAX || val < INT_MIN)
            {
                fprintf(stderr, "Erro: Overflow no número '%s'.\n", token);
                clean(&p);
                return EXIT_FAILURE;
            }
            if (endptr == token)
            {
                fprintf(stderr, "Erro: Token inválido '%s' não é um operador nem número.\n", token);
                clean(&p);
                return EXIT_FAILURE;
            }
            if (*endptr != '\0')
            {
                fprintf(stderr, "Erro: Caracteres inválidos no número '%s'.\n", token);
                clean(&p);
                return EXIT_FAILURE;
            }

            /* Sucesso na conversão */
            info_t info_num;
            info_num.val = (int)val;
            push(&p, info_num);
        }
    }

    if (size(p) != 1)
    {
        fprintf(stderr, "Erro: A expressão está mal formada (operandos em excesso ou faltantes).\n");
        clean(&p);
        return EXIT_FAILURE;
    }

    info_t *resultado_final_info = pop(&p);
    printf("Resultado: %d\n", resultado_final_info->val);
    free(resultado_final_info);

    /* clean(&p); // Opcional, pois a pilha já deve estar vazia. pop() liberou o nodo. */
    return EXIT_SUCCESS;
}

void help(void)
{
    IFDEBUG("help()");
    printf("%s - Calculadora Polonesa Reversa (RPN)\n", "polo");
    printf("\nUso: %s [opções] <expressão>\n", "polo");
    printf("\nExemplo: %s 5 1 2 + 4 \\* + 3 -\n", "polo");
    printf("\nOpções:\n");
    printf("\t-h,  --help\n\t\tMostra esta ajuda.\n");
    printf("\t-V,  --version\n\t\tMostra a versão e informações de copyright.\n");
    printf("\nStatus de Saída:\n\t0 se ok.\n\t1 se ocorreu algum erro.\n");
    printf("\nAutor:\n\tEscrito por %s <%s>\n\n", "Ruben Carlo Benante", "rcb@beco.cc");
    exit(EXIT_SUCCESS); /* Corrigido para SUCESSO */
}

void copyr(void)
{
    IFDEBUG("copyr()");
    printf("%s - Versão %s\n", "polo", VERSION);
    printf("\nCopyright (C) %d %s <%s>, GNU GPL version 2 <http://gnu.org/licenses/gpl.html>.\n", 2018, "Ruben Carlo Benante", "rcb@beco.cc");
    exit(EXIT_SUCCESS); /* Corrigido para SUCESSO */
}

info_t *pop(pilha_t **p)
{
    if (empty(*p))
    {
        errno = EFAULT; /* Endereço ruim, pilha vazia */
        return NULL;
    }

    pilha_t *temp = *p;
    info_t *info_retorno = temp->info;
    
    *p = temp->prox; /* Atualiza o topo da pilha */
    free(temp);      /* Libera o nodo da pilha */
    
    return info_retorno; /* Retorna a estrutura de informação, quem chama deve liberar a memória */
}

void push(pilha_t **p, info_t i)
{
    /* Aloca memória para o novo nodo da pilha */
    pilha_t *novo_nodo = (pilha_t *) malloc(sizeof(pilha_t));
    if (!novo_nodo)
    {
        perror("Falha ao alocar memória para o nodo da pilha");
        exit(EXIT_FAILURE);
    }

    /* Aloca memória para a informação */
    novo_nodo->info = (info_t *) malloc(sizeof(info_t));
    if (!novo_nodo->info)
    {
        perror("Falha ao alocar memória para a informação do nodo");
        free(novo_nodo);
        exit(EXIT_FAILURE);
    }
    
    *(novo_nodo->info) = i;
    novo_nodo->prox = *p;
    *p = novo_nodo;
}

int empty(pilha_t *p)
{
    return p == NULL;
}

void clean(pilha_t **p)
{
    while (!empty(*p))
    {
        info_t *info = pop(p);
        free(info); /* Libera a estrutura de info retornada por pop */
    }
}

int size(pilha_t *p)
{
    int count = 0;
    pilha_t *atual = p;
    while (atual != NULL)
    {
        count++;
        atual = atual->prox;
    }
    return count;
}
