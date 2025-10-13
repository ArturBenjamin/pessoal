/*****************************************************************************
 * polo.h                                   Version 20180714.101818        *
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

#ifndef _POLO_H
#define _POLO_H

/* ------------------------------------------------------------------------- */
/* includes */

#include <errno.h> /* Error number codes errno */

/* ------------------------------------------------------------------------- */
/* definitions */

#ifndef VERSION /* gcc -DVERSION="0.1.160612.142628" */
#define VERSION "20160908.182854" /**< Version Number (string) */
#endif

/* Debug */
#ifndef DEBUG /* gcc -DDEBUG=1 */
#define DEBUG 0 /**< Activate/deactivate debug mode */
#endif

#if DEBUG==0
#define NDEBUG
#endif
/* #include <assert.h> */ /* Verify assumptions with assert. Turn off with #define NDEBUG */ 

/** @brief Debug message if DEBUG on */
#define IFDEBUG(M) if(DEBUG) fprintf(stderr, "[DEBUG file:%s line:%d]: " M "\n", __FILE__, __LINE__); else {;}

/* limits */
#define SBUFF 256 /**< String buffer */
#define NUM 0 /* valor na pilha eh operando */
#define OPE 1 /* valor na pilha eh operador */

/* ------------------------------------------------------------------------- */
/* globals and types */

static int verb = 0; /**< verbose level, global within the file */

/* informacao de cada nodo da pilha */
typedef struct info_pilha
{
    int val; /* valor no nodo da pilha */
    int tipo; /* Se tipo=NUM, val = numero; Se tipo=OPE, val = '+', '-', '*' ou '/' */
} info_t;

/* ponteiro para nodo da pilha contendo informacoes */
typedef struct nodo_pilha
{
    info_t *info; /* estrutura contendo os dados do nodo */
    struct nodo_pilha *prox; /* ponteiro para o proximo nodo */
} pilha_t;

/* ------------------------------------------------------------------------- */
/* prototypes */

void help(void); /**< Prints help information and exit */
void copyr(void); /**< Prints copyright information and exit */
void polo_init(void);  /**< Initializes some operations before start */

/* funcoes de pilha */
int empty(pilha_t *p); /* retorna verdadeiro se pilha vazia */
void push(pilha_t **p, info_t i); /* insere elemento val no topo */
info_t *pop(pilha_t **p); /* remove elemento do topo */
info_t *top(pilha_t *p); /* consulta elemento no topo, sem remove-lo */
int size(pilha_t *p); /* retorna o total de elementos na pilha */
void clean(pilha_t **p); /* limpa toda a memoria utilizada pela pilha */

/* funcoes auxiliares */
int valida(char *s); /* valida a equacao retornando verdadeiro/falso */

#endif /* NOT def _POLO_H */
