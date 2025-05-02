/* ************************************************************************ *
 *    ovo.c                                                                 *
 *    Jogo do ovo: escolher entre O ou V em uma linha de 15 espaços         *
 *    quem escrever a palavra ovo ganha, caso não seja escrita e nao tiver  *
 *    mais nenhuma casa: empate                                             *
 *                                                                          *
 *    Copyright (C) 2022 by Joao Marcelo Uchoa Vasconcelos Dourado Leite    *
 *                                                                          *
 *    This program is free software; you can redistribute it and/or modify  *
 *    it under the terms of the GNU General Public License as published by  *
 *    the Free Software Foundation; either version 2 of the License, or     *
 *    (at your option) any later version.                                   *
 *                                                                          *
 *    This program is distributed in the hope that it will be useful,       *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *    GNU General Public License for more details.                          *
 *                                                                          *
 *    You should have received a copy of the GNU General Public License     *
 *    along with this program; if not, write to the                         *
 *    Free Software Foundation, Inc.,                                       *
 *    59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 *                                                                          *
 *  To contact the author, please write to:                                 *
 *  Name: Joao Marcelo Uchoa Vasconcelos Dourado Leite <jmuvdl@poli.br>     *
 *        Artur Benjamin Monteiro Nascimento <abmn@poli.br>                 *
 *        Joao Vitor dos Santos Martins Soares <jvsms@poli.br>              *
 *                                                                          *
 *  Webpage: http://beco.poli.br/~username                                  *
 *  Phone: 81999172565                                                      *
 * ************************************************************************ *
 *
 */
/* ------------------------------------------------------------------------------------------------------- */
/* includes e defines */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAPESIZE 15

/* ------------------------------------------------------------------------------------------------------- */
/* Estrutura */
typedef struct {
    char tape[TAPESIZE];
    int owner[TAPESIZE]; // 0 = vazio, 1 = jogador 1, 2 = jogador 2
    int currentPlayer;
    int lastMove; /* provavelmente vai precisar de alguma pra determinar qm ganhou */
} GameState;

/* ------------------------------------------------------------------------------------------------------- */
/* Base */
void displayTape(const GameState g);
void getInput(GameState g, int *p, char *l);
int makeMove(GameState *g, int p, char l);
int checkGameStatus(const GameState *g);
void startGame(GameState *g);

/* ------------------------------------------------------------------------------------------------------- */
/* prime function */
int main(void)
{

return EXIT_SUCCESS;
}

/* ------------------------------------------------------------------------------------------------------- */
/* começar jogo */
void startGame(GameState g)
{

}

/* ------------------------------------------------------------------------------------------------------- */
/* imprimir a linha sem nenhuma alteração */
void printTape(GameState *g, int p, char l)
{

}

/* ------------------------------------------------------------------------------------------------------- */
/* pegar imput do jogador */
void getInput(GameState g, int *p, char *l)
{
    int validInput = 0;

    while (!validInput)
    {
        printf("\nJogador %d, escolha a posição (1-%d): ", g.currentPlayer, TAPESIZE);
        scanf("%d", p);

        if (*p < 1 || *p > TAPESIZE)
        {
            printf("Posição inválida! Escolha entre 1 e %d.\n", TAPESIZE);
            continue;
        }

        printf("Digite 'O' ou 'V': ");
        scanf(" %c", l);

        *l = (*l == 'o' || *l == 'O') ? 'O' : (*l == 'v' || *l == 'V') ? 'V' : ' ';

        if (*l != 'O' && *l != 'V')
        {
            printf("Entrada inválida! Digite apenas 'O' ou 'V'.\n");
            continue;
        }

        validInput = 1;
    }
}

/* ------------------------------------------------------------------------------------------------------- */
/* mostrar linha agora alterada */
void displayTape(const GameState g)
{

}

/* ------------------------------------------------------------------------------------------------------- */
/* checar se a jogada foi valida */
int makeMove(GameState *g, int p, char l)
{
    if (p < 0 || p >= TAPESIZE) return 0;  // Posição inválida
    if (g->tape[p] != ' ') return 0;  // Posição ocupada
    if (l != 'O' && l != 'V') return 0;  // Letra inválida

    g->tape[p] = l;
    g->owner[p] = g->currentPlayer;
    return 1;
}

/* ------------------------------------------------------------------------------------------------------- */
/* checar se alguem ganhou */
int checkWin(const GameState *g)
{

}







