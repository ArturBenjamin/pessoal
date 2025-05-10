/* ************************************************************************ *
 *    jv.c                                                                  *
 *    Jogo da velha                                                         *
 *                                                                          *
 *    Copyright (C) 2022 by Joao Marcelo Uchoa Vasconcelos Dourado Leite    *
 *                                                                          *
 *    Este programa é software livre; você pode redistribuí-lo e/ou         *
 *    modificá-lo sob os termos da Licença Pública Geral GNU conforme       *
 *    publicada pela Free Software Foundation; na versão 2 da Licença,      *
 *    ou (a seu critério) qualquer versão posterior.                        *
 *                                                                          *
 *    Este programa é distribuído na expectativa de que seja útil,          *
 *    mas SEM NENHUMA GARANTIA; sem mesmo a garantia implícita de           *
 *    COMERCIALIZAÇÃO ou ADEQUAÇÃO A QUALQUER PROPÓSITO EM PARTICULAR.      *
 *    Veja a Licença Pública Geral GNU para mais detalhes.                  *
 *                                                                          *
 *    Você deve ter recebido uma cópia da Licença Pública Geral GNU         *
 *    junto com este programa; se não, escreva para                         *
 *    Free Software Foundation, Inc.,                                       *
 *    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                          *
 *  Contato com os autores:                                                 *
 *  Nome: Joao Marcelo Uchoa Vasconcelos Dourado Leite <jmuvdl@poli.br>     *
 *        Artur Benjamin Monteiro Nascimento <abmn@poli.br>                 *
 *        Joao Vitor dos Santos Martins Soares <jvsms@poli.br>              *
 *                                                                          *
 *  Página: http://beco.poli.br/~username                                   *
 *  Telefone: 81999172565                                                   *
 * ************************************************************************ */

/* ------------------------------------------------------------------------------------------------------- */
/* Inclusão de bibliotecas e definição de constantes */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define SIZE 3
/* ------------------------------------------------------------------------------------------------------- */
/* Funções auxiliares */
void displayTabuleiro(char tab[SIZE][SIZE]);
int checkInput(char tab[SIZE][SIZE], int lin, int col); /* checar se o input do player ta certo */
void getInput(char tab[SIZE][SIZE]); /* input do jogador (X) */
void iaImput(char tab[SIZE][SIZE], int jogada_num); /* jogada da ia (O) */
int resultCheck(char tab[SIZE][SIZE]); /*checa vitoria ou impate*/
/* ------------------------------------------------------------------------------------------------------- */
/* Função prime */
int main(void)
{

}
/* ------------------------------------------------------------------------------------------------------- */
/* cria o tabuleiro */
void displayTabuleiro (char tab[SIZE][SIZE])
{
    printf("\nJogo da velha:\n\n");

    for (int i = 0; i < SIZE; i++)
    {
        printf("\n");
        if (i < SIZE - 1)
            printf("---+---+---\n");

        for (int j = 0; j < SIZE; j++)
        {
            tab[i][j] = ' ';
            printf(" %c ", tab[i][j]);
            if (j < SIZE - 1) printf("|");
        }
    }
}
/* ------------------------------------------------------------------------------------------------------- */
/* ler input do jogador */
void getInput(char tab[SIZE][SIZE])
{
    int lin, col;
    do
    {
        printf("Sua vez! Escolha a linha (1-3): ");
        scanf("%d", &lin);
        lin--;

        printf("Escolha a coluna (1-3): ");
        scanf("%d", &col);
        col--;

    }
    while (!checkInput(tab, lin, col));
    tab[lin][col] = 'X';
}
/* ------------------------------------------------------------------------------------------------------- */
/* checar input do jogador */
int checkInput(char tab[SIZE][SIZE], int lin, int col)
{

}
/* ------------------------------------------------------------------------------------------------------- */
/* jogada da ia */
void iaImput(char tab[SIZE][SIZE], int jogada_num)
{

}
/* ------------------------------------------------------------------------------------------------------- */
/* checagem de vitoria/empate */
int resultCheck(char tab[SIZE][SIZE])
{

}
