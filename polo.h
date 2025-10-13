/*****************************************************************************
 * exN.h                                    Version 20180714.101818        *
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
 *****************************************************************************
 * To contact the author, please write to:                                 *
 * Ruben Carlo Benante                                                     *
 * Email: rcb@beco.cc                                                      *
 * Webpage: www.beco.cc                                                    *
 * Phone: +55 (81) 3184-7555                                               *
 *****************************************************************************/

/* ------------------------------------------------------------------------- */
/**
 * \file exN.h
 * \ingroup GroupUnique
 * \brief Brief description
 * \details This program really do a nice job as a template, and template only!
 * \version 20160908.182854
 * \date 2016-09-08
 * \author Ruben Carlo Benante <<rcb@beco.cc>>
 * \par Webpage
 * <<a href="www.beco.cc">www.beco.cc</a>>
 * \copyright (c) 2016 GNU GPL v2
 * \note This program is free software: you can redistribute it
 * and/or modify it under the terms of the
 * GNU General Public License as published by
 * the Free Software Foundation version 2 of the License.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.
 * If not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA. 02111-1307, USA.
 * Or read it online at <<http://www.gnu.org/licenses/>>.
 *
 *
 * \todo Now that you have the template, hands on! Programme!
 * \warning Be carefull not to lose your mind in small things.
 * \bug This file right now does nothing usefull
 *
 */

#ifndef _EXN_H
#define _EXN_H

/* ------------------------------------------------------------------------- */
/* includes */

/* #include <stdio.h> */ /* Standard I/O functions */
/* #include <stdlib.h> */ /* Miscellaneous functions (rand, malloc, srand)*/
/* #include <getopt.h> */ /* get options from system argc/argv */
#include <errno.h> /* Error number codes errno */

/* #include <time.h> */ /* Time and date functions */
/* #include <math.h> */ /* Mathematics functions */
/* #include <string.h> */ /* Strings functions definitions */
/* #include <dlfcn.h> */ /* Dynamic library */
/* #include <malloc.h> */ /* Dynamic memory allocation */
/* #include <unistd.h> */ /* UNIX standard function */
/* #include <limits.h> */ /* Various C limits */
/* #include <ctype.h> */ /* Character functions */
/* #include <signal.h> */ /* Signal processing */
/* #include <stdarg.h> */ /* Functions with variable arguments */
/* #include <pthread.h> */ /* Parallel programming with threads */
/* #include <fcntl.h> */ /* File control definitions */
/* #include <termios.h> */ /* Terminal I/O definitions POSIX */
/* #include <sys/stat.h> */ /* File status and information */
/* #include <float.h> */ /* Float constants to help portability */
/* #include <setjmp.h> */ /* Bypass standard function calls and return */
/* #include <stddef.h> */ /* Various types and MACROS */
/* #include <SWI-Prolog.h> */ /* Prolog integration with C */
/* #include <ncurses.h> */ /* Screen handling and optimisation functions */
/* #include <allegro.h> */ /* A game library for graphics, sounds, etc. */
/* #include <libintl.h> */ /* Internationalization / translation */
/* #include <locale.h> */ /* MACROS LC_ for location specific settings */
/* #include "libeco.h" */ /* I/O, Math, Sound, Color, Portable Linux/Windows */
/* #include "exN.h" */ /* To be created for this template if needed */

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


/* Organizacao:
 *
 * info_t:
 * +-----------+
 * | int val;  |
 * +---> +-----------+             +---> info_t
 * |     | int tipo; |             |
 * |     +-----------+             |
 * |                               |
 * pilha_t:        |               pilha_t:        |
 * +----------------+   |          +----------------+   |
 * | info_t *info;  |---+          | info_t *info;  |---+
 * base---> +----------------+        +---> +----------------+
 * | pilha_t *prox; |--------+     | pilha_t *prox; |---> pilha_t ---> ...
 * +----------------+              +----------------+
 * |
 * V
 * topo
 */


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
void exN_init(void);  /**< Initializes some operations before start */

/* funcoes de pilha */
int empty(pilha_t *p); /* retorna verdadeiro se pilha vazia */
void push(pilha_t **p, info_t i); /* insere elemento val no topo */
info_t *pop(pilha_t **p); /* remove elemento do topo */
info_t *top(pilha_t *p); /* consulta elemento no topo, sem remove-lo */
int size(pilha_t *p); /* retorna o total de elementos na pilha */
void clean(pilha_t **p); /* limpa toda a memoria utilizada pela pilha */

/* funcoes auxiliares */
int valida(char *s); /* valida a equacao retornando verdadeiro/falso */

#endif /* NOT def _EXN_H */

/* ------------------------------------------------------------------------- */
/* vi: set ai et ts=4 sw=4 tw=0 wm=0 fo=croql : C config for Vim modeline    */
/* Template by Dr. Beco <rcb at beco dot cc>       Version 20180716.101436   */
