/***************************************************************************
 *   upecman.c                                Version 20160529.013231      *
 *                                                                         *
 *   Pacman Ncurses                                                        *
 *   Copyright (C) 2016         by Ruben Carlo Benante                     *
 ***************************************************************************
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License.        *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************
 *   To contact the author, please write to:                               *
 *   Ruben Carlo Benante                                                   *
 *   Email: rcb@beco.cc                                                    *
 *   Webpage: http://www.beco.cc                                           *
 *   Phone: +55 (81) 3184-7555                                             *
 ***************************************************************************/

/* ---------------------------------------------------------------------- */
/**
 * @file upecman.c
 * @ingroup GroupUnique
 * @brief Pacman Ncurses
 * @details This program really do a nice job as a template, and template only!
 * @version 20160529.013231
 * @date 2016-05-29
 * @author Ruben Carlo Benante <<rcb@beco.cc>>
 * @par Webpage
 * <<a href="http://www.beco.cc">www.beco.cc</a>>
 * @copyright (c) 2016 GNU GPL v2
 * @note This program is free software: you can redistribute it
 * and/or modify it under the terms of the
 * GNU General Public License as published by
 * the Free Software Foundation version 2 of the License.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program.
 * If not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA. 02111-1307, USA.
 * Or read it online at <<http://www.gnu.org/licenses/>>.
 *
 *
 * @todo Now that you have the template, hands on! Programme!
 * @warning Be carefull not to lose your mind in small things.
 * @bug This file right now does nothing usefull
 *
 */

/*
 * Instrucoes para compilar:
 *      $make
 * ou
 *      $gcc upecman.c -o upecman.x -Wall -lncurses -g -Og
 *          -Wextra -ansi -pedantic-errors -DDEBUG=1
 */

/* ---------------------------------------------------------------------- */
/* includes */

#include <stdio.h> /* Standard I/O functions */
#include <stdlib.h> /* Miscellaneous functions (rand, malloc, srand)*/
#include <ncurses.h> /* Screen handling and optimisation functions */
#include <getopt.h> /* get options from system argc/argv */
#include <string.h> /* Strings functions definitions */
#include <assert.h> /* Verify assumptions with assert */
#include <unistd.h> /* UNIX standard function */
#include "upecman.h" /* To be created for this template if needed */

#include <time.h>  /* Time and date functions */
#include <ctype.h> /* For tolower() */


/* ---------------------------------------------------------------------- */
int main(int argc, char *argv[])
{
    IFDEBUG("main()\n");
    int opt; /* return from getopt() */
    t_game g; /* the game */
    const char *sready = "Are you ready? (y/n)"; /* ready string */
    int kin; /* keyboard input */

    IFDEBUG("Starting optarg loop...\n");

    opterr = 0;
    while((opt = getopt(argc, argv, "hvc")) != EOF)
        switch(opt)
        {
            case 'h':
                // Ncurses might not be initialized here. If help prints to stdout, it's fine.
                // If help uses ncurses, it needs to be handled differently or ncurses initialized earlier.
                // For simplicity, assuming help prints to stdout and exits.
                help();
                return EXIT_SUCCESS; // help() should ideally exit itself
            case 'v':
                verb++;
                break;
            case 'c':
                // Similar to help(), assuming copyr prints to stdout and exits.
                copyr();
                return EXIT_SUCCESS; // copyr() should ideally exit itself
            case '?':
            default:
                // getopt already prints an error message if opterr is not 0
                // and if opterr is 0, then we print our own.
                if (optopt == 0 || opterr == 0) { // optopt contains the unrecognized option
                     fprintf(stderr, "Unknown option '-%c'.\n", optopt);
                }
                fprintf(stderr, "Type %s -h for help.\n", argv[0]);
                return EXIT_FAILURE;
        }

    if(verb)
        printf("Verbose level set at: %d\n", verb); // This prints to stdout before ncurses


    // Initialize ncurses first
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0); // Hide cursor
    start_color();

    // Initialize color pairs (moved from upecman_init)
    init_pair(1, COLOR_RED, COLOR_BLACK);     /* Blinky */
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK); /* Pinky */
    init_pair(3, COLOR_CYAN, COLOR_BLACK);    /* Inky */
    init_pair(4, COLOR_GREEN, COLOR_BLACK);   /* Clyde */
    init_pair(5, COLOR_BLUE, COLOR_BLACK);    /* Afraid mode ghost*/
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);  /* Pacman */

    // Display "Are you ready?" prompt on a clear screen or specific line
    clear(); // Clear the screen before showing the prompt
    mvprintw(10, (COLS - strlen(sready)) / 2 , "%s", sready); // Centered on line 10
    refresh();

    timeout(-1); // Make getch blocking for this prompt
    while(1)
    {
        kin = getch();
        if(tolower(kin) == 'y')
            break;
        if(tolower(kin) == 'n')
        {
            clear();
            mvprintw(LINES / 2, (COLS - strlen("Exiting...")) / 2, "Exiting...");
            refresh();
            sleep(1);
            endwin();
            return EXIT_SUCCESS;
        }
    }

    // User is ready, now initialize game data
    IFDEBUG("Initializing game data...\n");
    g = upecman_init(); // This now ONLY initializes game struct

    timeout(0); // Restore non-blocking getch for the game loop

    IFDEBUG("Starting the game loop now...\n");
    // Initial draw of the lab before game loop starts
    clear(); // Clear the "Are you ready?" prompt
    printlab(g);
    display_score_lives(&g); // Display initial score/lives
    refresh();

    game_loop(&g);

    /* write your code here */

        // 1. Desenha o labirinto e os elementos (Pacman, fantasmas, pontos)

        // 2. Exibe informações do jogo (score, vidas)

        // 3. Captura a entrada do teclado (non-blocking)

        // 4. Move o Pacman com base na entrada do teclado

        // 5. Lógica dos fantasmas (você ou outro membro do grupo vai implementar aqui)
        // Exemplo:
        // move_ghosts(&g);
        // check_pacman_ghost_collision(&g); // Verificar se Pacman colidiu com fantasma

        // 6. Verificação de condição de vitória (todos os pontos comidos)
        // Você precisará de uma função para contar os pontos restantes no labirinto
        // if (all_dots_eaten(g)) {
        //     clear();
        //     mvprintw(LINES / 2, COLS / 2 - 5, "VOCÊ VENCEU!");
        //     refresh();
        //     getch();
        //     break; // Sai do loop do jogo
        // }

        // 7. Pequeno atraso para controlar a velocidade do jogo (aproximadamente 60 FPS)
    endwin();
    printf("Game Over! Final Score: %d\n", g.pacman.score);
    return EXIT_SUCCESS;
}



/* ---------------------------------------------------------------------- */
void help(void)
{
    IFDEBUG("help()");
    // This function should print to stdout and then exit.
    // If ncurses is active, it should call endwin() first.
    // For simplicity, we assume it's called before ncurses or handles it.
    printf("%s - %s\n", "upecman", "Pacman Ncurses");
    printf("\nUsage: ./%s [-h|-v|-c]\n", "upecman");
    printf("\nOptions:\n");
    printf("\t-h,  --help\n\t\tShow this help.\n");
    printf("\t-c,  --copyright, --version\n\t\tShow version and copyright information.\n");
    printf("\t-v,  --verbose\n\t\tSet verbose level (cumulative).\n");
    printf("\nGame Controls:\n");
    printf("\tArrow Keys: Move Pac-Man\n");
    printf("\tq: Quit Game\n");
    printf("\nExit status:\n\t0 if ok.\n\t1 some error occurred.\n");
    printf("\nTodo:\n\tLong options not implemented yet.\n");
    printf("\nAuthor:\n\tWritten by %s <%s>\n\n", "Ruben Carlo Benante", "rcb@beco.cc");
    // No exit here, main will handle it if help/copyr don't.
}

/* ---------------------------------------------------------------------- */
void copyr(void)
{
    IFDEBUG("copyr()");
    // Similar to help(), should print to stdout and exit.
    printf("%s - Version %s\n", "upecman", VERSION);
    printf("\nCopyright (C) %d %s <%s>, GNU GPL version 2 <http://gnu.org/licenses/gpl.html>. This  is  free  software:  you are free to change and redistribute it. There is NO WARRANTY, to the extent permitted by law. USE IT AS IT IS. The author takes no responsability to any damage this software may inflige in your data.\n\n", 2016, "Ruben Carlo Benante", "rcb@beco.cc");
    if(verb > 3) printf("copyr(): Verbose: %d\n", verb);
    // No exit here.
}

/* ---------------------------------------------------------------------- */
t_game upecman_init(void)
{
    IFDEBUG("upecman_init() - Initializing game data structure ONLY");
    t_game g;
    int f, y;

    srand(time(NULL)); // Seed random number generator

    for(y = 0; y < LABL; y++)
        strcpy(g.lab[y], labmodel[y]); // copy the labyrinth

    // Pacman initial setup
    g.pacman.pos.y = 17; // Original position of '@' in labmodel
    g.pacman.pos.x = 9;  // Original position of '@' in labmodel
    g.lab[g.pacman.pos.y][g.pacman.pos.x] = ' '; // Clear '@' from the map model, Pacman will be drawn over it
    g.pacman.dir = left;
    g.pacman.desired_dir = left; // Initialize desired_dir
    g.pacman.life = 3;
    g.pacman.score = 0;
    /* {
        strcpy(g.lab[y], labmodel[y]);
        g.lab[y][LABC - 1] = '\0'; // Garante que cada linha é uma string nula-terminada no limite correto
    } */

    // Ghosts initial setup
    for(f = blinky; f <= clyde; f++)
    {
        switch(f)
        {
            case blinky: // 'B'
                g.ghost[f].pos.y = 7; g.ghost[f].pos.x = 9;
                g.ghost[f].starget.y = 0; g.ghost[f].starget.x = 19;
                g.lab[g.ghost[f].pos.y][g.ghost[f].pos.x] = ' '; // Clear 'B' from map
                break;
            case pinky: // 'P'
                g.ghost[f].pos.y = 9; g.ghost[f].pos.x = 10;
                g.ghost[f].starget.y = 0; g.ghost[f].starget.x = 0;
                g.lab[g.ghost[f].pos.y][g.ghost[f].pos.x] = ' '; // Clear 'P' from map
                break;
            case inky: // 'I'
                g.ghost[f].pos.y = 10; g.ghost[f].pos.x = 10;
                g.ghost[f].starget.y = 22; g.ghost[f].starget.x = 19;
                g.lab[g.ghost[f].pos.y][g.ghost[f].pos.x] = ' '; // Clear 'I' from map
                break;
            case clyde: // 'C'
                g.ghost[f].pos.y = 11; g.ghost[f].pos.x = 10;
                g.ghost[f].starget.y = 22; g.ghost[f].starget.x = 0;
                g.lab[g.ghost[f].pos.y][g.ghost[f].pos.x] = ' '; // Clear 'C' from map
                break;
        }
        g.ghost[f].dir = left;
        g.ghost[f].mode = chase;
    }
    // Ncurses init calls (initscr, cbreak, etc.) are MOVED to main()
    return g;
}

/* ---------------------------------------------------------------------- */
void printlab(t_game g) {
    int y, x, f;

    // 1. Print the static labyrinth (walls, dots, pills, empty spaces)
    //    These are already in g.lab from upecman_init
    for (y = 0; y < LABL; y++) {
        for (x = 0; x < LABC - 1; x++) { // LABC-1 because labmodel strings are LABC-1 char long + null
            mvaddch(y, x, g.lab[y][x]);
        }
    }

    // 2. Print Ghosts
    char ghost_char;
    for (f = blinky; f <= clyde; f++) {
        switch (f) {
            case blinky: ghost_char = 'B'; break;
            case pinky:  ghost_char = 'P'; break;
            case inky:   ghost_char = 'I'; break;
            case clyde:  ghost_char = 'C'; break;
            default:     ghost_char = '?'; break; // Should not happen
        }
        attron(COLOR_PAIR(f + 1) | A_BOLD); // Ghost colors are 1-4
        mvaddch(g.ghost[f].pos.y, g.ghost[f].pos.x, ghost_char);
        attroff(COLOR_PAIR(f + 1) | A_BOLD);
    }
    /* clear(); */

    // 3. Print Pacman
    attron(COLOR_PAIR(6) | A_BOLD); // Pacman color is 6 (Yellow)
    mvaddch(g.pacman.pos.y, g.pacman.pos.x, '@');
    attroff(COLOR_PAIR(6) | A_BOLD);
}

/* ---------------------------------------------------------------------- */
void display_score_lives(t_game *g) {
    mvprintw(LABL, 0, "Score: %-7d Lives: %d", g->pacman.score, g->pacman.life);
}

/* ---------------------------------------------------------------------- */
bool is_wall(t_game *g, int y, int x) {
    if (y < 0 || y >= LABL || x < 0 || x >= (LABC -1) ) { // LABC-1 for valid game columns
        return true; // Out of bounds is a wall
    }
    // Check against the base labyrinth stored in g->lab
    return g->lab[y][x] == '#';
}

/* ---------------------------------------------------------------------- */
void update_upecman_state(t_game *g, int player_input_key, bool *game_running) {
    int next_y, next_x;
    int desired_next_y, desired_next_x;

    // Handle player input to set desired direction
    switch (player_input_key) {
        case KEY_UP:    g->pacman.desired_dir = up;    break;
        case KEY_DOWN:  g->pacman.desired_dir = down;  break;
        case KEY_LEFT:  g->pacman.desired_dir = left;  break;
        case KEY_RIGHT: g->pacman.desired_dir = right; break;
        case 'q':       *game_running = false; return; // Exit game
    }

    // Current Pac-Man position
    int old_y = g->pacman.pos.y;
    int old_x = g->pacman.pos.x;

    // Try to move in the desired direction first
    desired_next_y = old_y;
    desired_next_x = old_x;

    switch (g->pacman.desired_dir) {
        case up:    desired_next_y--; break;
        case down:  desired_next_y++; break;
        case left:  desired_next_x--; break;
        case right: desired_next_x++; break;
        case none: break; // Should not happen if initialized
    }

    if (!is_wall(g, desired_next_y, desired_next_x)) {
        g->pacman.pos.y = desired_next_y;
        g->pacman.pos.x = desired_next_x;
        g->pacman.dir = g->pacman.desired_dir; // Commit to desired direction
    } else {
        // If desired direction is blocked, try to continue in the current direction
        next_y = old_y;
        next_x = old_x;
        switch (g->pacman.dir) {
            case up:    next_y--; break;
            case down:  next_y++; break;
            case left:  next_x--; break;
            case right: next_x++; break;
            case none: break; // Should not happen
        }
        if (!is_wall(g, next_y, next_x)) {
            g->pacman.pos.y = next_y;
            g->pacman.pos.x = next_x;
            // Keep current g->pacman.dir, desired_dir remains for next chance
        } else {
            // Pacman is blocked in current direction too, so it stops.
            // No change in position.
        }
    }

    // Tunnel logic (Row 10, exits at X=0 and X=19 (LABC-2))
    if (g->pacman.pos.y == 10) { // Tunnel row defined in labmodel
        if (g->pacman.pos.x == 0 && g->pacman.dir == left) {
            g->pacman.pos.x = LABC - 2; // Wrap to right side (column 19 for LABC=21)
        } else if (g->pacman.pos.x == LABC - 2 && g->pacman.dir == right) {
            g->pacman.pos.x = 0; // Wrap to left side (column 0)
        }
    }

    // Check for collision with dots/pills at the new position
    // This check must be done on g->lab because that's where dots/pills are stored.
    char cell_content = g->lab[g->pacman.pos.y][g->pacman.pos.x];
    if (cell_content == '.') {
        g->pacman.score += 10;
        g->lab[g->pacman.pos.y][g->pacman.pos.x] = ' '; // Eat the dot by replacing it with space
    } else if (cell_content == 'o') {
        g->pacman.score += 50;
        g->lab[g->pacman.pos.y][g->pacman.pos.x] = ' '; // Eat the pill
        // TODO: Activate afraid mode for ghosts
    }
}

/* ---------------------------------------------------------------------- */
void game_loop(t_game *g) {
    IFDEBUG("game_loop()");
    bool game_running = true;
    int player_input_key;
    long frame_delay = 150000; // microseconds (150ms, approx 6.6 FPS, adjust for speed)

    while(game_running) {
        player_input_key = getch(); // Non-blocking due to timeout(0) set in main

        update_upecman_state(g, player_input_key, &game_running);

        if (!game_running) break; // Exit if 'q' was pressed in update_upecman_state

        // Ghost logic would go here (not implemented in this version)

        // Drawing
        erase(); // Clear the whole screen
        printlab(*g); // Redraw the entire game state
        display_score_lives(g); // Redraw score and lives
        refresh(); // Update the physical screen

        usleep(frame_delay); // Control game speed
    }
    /* refresh(); */
}

void move_pacman(t_game *g, int key_input)
{
    IFDEBUG("move_pacman()\n");

    int old_y = g->pacman.pos.y;
    int old_x = g->pacman.pos.x;

    t_direction desired_dir = g->pacman.dir;
    t_direction actual_dir = g->pacman.dir;

    int temp_y = old_y;
    int temp_x = old_x;

    const int TUNNEL_Y_MIN = 17;
    const int TUNNEL_Y_MAX = 17;

    switch (key_input)
    {
        case KEY_UP:    desired_dir = up;    break;
        case KEY_DOWN:  desired_dir = down;  break;
        case KEY_LEFT:  desired_dir = left;  break;
        case KEY_RIGHT: desired_dir = right; break;
        default: break;
    }

    // Prioridade A: Verificar Túnel
    if (old_y >= TUNNEL_Y_MIN && old_y <= TUNNEL_Y_MAX)
    {
        // Se está na coluna 0 (borda esquerda) e quer ir para a esquerda
        if (desired_dir == left && old_x == 0)
        {
            temp_x = LABC - 2; // TELEPORTA para a PENÚLTIMA coluna (índice 19, que é a última visível)
            temp_y = old_y;
            actual_dir = desired_dir;
            /* nao use goto apply_movement; */
        }
        // Se está na coluna 19 (borda direita visível) e quer ir para a direita
        else if (desired_dir == right && old_x == (LABC - 2)) // LABC-2 é a coluna 19
        {
            temp_x = 0; // Teleporta para a coluna 0
            temp_y = old_y;
            actual_dir = desired_dir;
            /* nao use goto apply_movement; */
        }
    }

    // Prioridade B: Tentar movimento na direção DESEJADA (se não foi túnel)
    int next_y_desired = old_y;
    int next_x_desired = old_x;
    switch (desired_dir)
    {
        case up:    next_y_desired--; break;
        case down:  next_y_desired++; break;
        case left:  next_x_desired--; break;
        case right: next_x_desired++; break;
        default:
                    printf("veja linha 380 ajustar esse erro");
    }

    if (g->lab[next_y_desired][next_x_desired] != '#')
    {
        temp_y = next_y_desired;
        temp_x = next_x_desired;
        actual_dir = desired_dir;
    }
    // Prioridade C: Se a direção DESEJADA é PAREDE, tentar movimento na direção ATUAL
    else
    {
        int next_y_current = old_y;
        int next_x_current = old_x;
        switch (g->pacman.dir)
        {
            case up:    next_y_current--; break;
            case down:  next_y_current++; break;
            case left:  next_x_current--; break;
            case right: next_x_current++; break;
            default:
                    printf("veja linha 380 ajustar esse erro");
        }

        if (g->lab[next_y_current][next_x_current] != '#')
        {
            temp_y = next_y_current;
            temp_x = next_x_current;
            actual_dir = g->pacman.dir;
        }
        // Se todas as tentativas falharem, temp_y e temp_x permanecem como old_y e old_x, e o Pacman não se move.
    }


/* nao use goto apply_movement:; */

    if (temp_y != old_y || temp_x != old_x)
    {
        g->lab[old_y][old_x] = ' ';

        if (g->lab[temp_y][temp_x] == '.')
        {
            g->pacman.score += 10;
        }
        else if (g->lab[temp_y][temp_x] == 'o')
        {
            g->pacman.score += 50;
        }

        g->lab[temp_y][temp_x] = '@';

        g->pacman.pos.y = temp_y;
        g->pacman.pos.x = temp_x;
        g->pacman.dir = actual_dir;
    }
}
    // O '@' permanece na posição old_y, old_x.
/* ---------------------------------------------------------------------- */
/* vi: set ai et ts=4 sw=4 tw=0 wm=0 fo=croql : C config for Vim modeline */
/* Template by Dr. Beco <rcb at beco dot cc> Version 20160612.142044      */
