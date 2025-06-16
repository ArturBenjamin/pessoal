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

    IFDEBUG("Starting optarg loop...\n");

    opterr = 0;
    while((opt = getopt(argc, argv, "hvc")) != EOF)
        switch(opt)
        {
            case 'h':
                help();
                return EXIT_SUCCESS;
            case 'v':
                verb++;
                break;
            case 'c':
                copyr();
                return EXIT_SUCCESS;
            case '?':
            default:
                if (optopt == 0 || opterr == 0) {
                     fprintf(stderr, "Unknown option '-%c'.\n", optopt);
                }
                fprintf(stderr, "Type %s -h for help.\n", argv[0]);
                return EXIT_FAILURE;
        }

    if(verb)
        printf("Verbose level set at: %d\n", verb);

    // Initialize ncurses
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);
    start_color();

    // Initialize color pairs
    init_pair(1, COLOR_RED, COLOR_BLACK);     /* Blinky */
    init_pair(2, COLOR_MAGENTA, COLOR_BLACK); /* Pinky */
    init_pair(3, COLOR_CYAN, COLOR_BLACK);    /* Inky */
    init_pair(4, COLOR_GREEN, COLOR_BLACK);   /* Clyde */
    init_pair(5, COLOR_BLUE, COLOR_BLACK);    /* Afraid mode ghost*/
    init_pair(6, COLOR_YELLOW, COLOR_BLACK);  /* Pacman */

    // Show menu first
    show_menu();

    // Initialize game
    g = upecman_init();
    //define o tmpo inicial para zero
    g.timer.start_time = time(NULL);

    // Start game loop
    game_loop(&g);

    endwin();
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
    // Ghosts Tempo de Movimento
    g.ghost[0].start_time = 0;  // Blinky sempre se movendo
    g.ghost[1].start_time = 10; // Pinky inicio apos 10 segundos de jogo
    g.ghost[2].start_time = 20; // Inky inicio apos 20 segundos de jogo
    g.ghost[3].start_time = 30; // Clyde inicio apos 30 segundos de jogo

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
        case 'q':       *game_running = false; return;
        default: break;
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
        case none: break;
    }

    // Check if desired direction is valid
    if (!is_wall(g, desired_next_y, desired_next_x)) {
        g->pacman.pos.y = desired_next_y;
        g->pacman.pos.x = desired_next_x;
        g->pacman.dir = g->pacman.desired_dir;
    }
    else {
        // If desired direction is blocked, try current direction
        next_y = old_y;
        next_x = old_x;

        switch (g->pacman.dir) {
            case up:    next_y--; break;
            case down:  next_y++; break;
            case left:  next_x--; break;
            case right: next_x++; break;
            case none: break;
        }

        if (!is_wall(g, next_y, next_x)) {
            g->pacman.pos.y = next_y;
            g->pacman.pos.x = next_x;
        }
    }

    // Tunnel logic
    if (g->pacman.pos.y == 10) {
        if (g->pacman.pos.x == 0 && g->pacman.dir == left) {
            g->pacman.pos.x = LABC - 2;
        }
        else if (g->pacman.pos.x == LABC - 2 && g->pacman.dir == right) {
            g->pacman.pos.x = 0;
        }
    }

    // Check for dots and pills
    char cell = g->lab[g->pacman.pos.y][g->pacman.pos.x];
    if (cell == '.') {
        g->pacman.score += 10;
        g->lab[g->pacman.pos.y][g->pacman.pos.x] = ' ';
    }
    else if (cell == 'o') {
        g->pacman.score += 50;
        g->lab[g->pacman.pos.y][g->pacman.pos.x] = ' ';
        // TODO: Activate afraid mode for ghosts
    }
}
/* ---------------------------------------------------------------------- */
void game_loop(t_game *g) {
    IFDEBUG("game_loop()");
    bool game_running = true;
    int player_input_key;
    long frame_delay = 150000; // microseconds (150ms)

    // Set non-blocking input
    timeout(0);
    nodelay(stdscr, TRUE); // Alternative to timeout(0)

    while(game_running) {

        // calcula o tempo decorrido
        g->timer.current_time = time(NULL);
        g->timer.elapsed_seconds = difftime(g->timer.current_time, g->timer.start_time);

        // Get input
        player_input_key = getch();

        // Update game state
        update_upecman_state(g, player_input_key, &game_running);

        // Logica de progressao de fase
        if (verifica_vitoria_nivel(g)) {
            // Mostra uma mensagem de vitória
            clear();
            mvprintw(LABL / 2, (COLS - 15) / 2, "FASE COMPLETA!");
            refresh();
            sleep(3); // Pausa por 3 segundos

            // Prepara o próximo nível
            prepara_proximo_nivel(g);
            // Aumenta a dificuldade a cada fase
            if (frame_delay > 50000) frame_delay -= 10000;
        }

        // Check if game should end
        if (!game_running) break;

        // Draw everything
        clear();
        printlab(*g);
        display_score_lives(g);

        // Debug info (can be removed later)
        mvprintw(LABL + 2, 0, "Current direction: %d, Desired: %d",
                g->pacman.dir, g->pacman.desired_dir);
        mvprintw(LABL + 3, 0, "Position: Y=%d, X=%d",
                g->pacman.pos.y, g->pacman.pos.x);
        mvprintw(LABL + 4, 0, "Tempo: %d",
                g->timer.elapsed_seconds);

        refresh();

        // Control game speed
        usleep(frame_delay);
    }
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

/*------------------------------------------------------------------------------------*/

void draw_ascii_art(void) {
    int i;
    for(i = 0; i < 5; i++) {
        mvprintw(3 + i, (COLS - strlen(menu_title[i])) / 2, "%s", menu_title[i]);
    }
}

void show_menu(void) {
    int highlight = 0;
    int choice = 0;
    int c;

    while(1) {
        clear();
        draw_ascii_art();

        // Desenha opções do menu
        for(int i = 0; i < 3; i++) {
            if(i == highlight)
                attron(A_REVERSE);
            mvprintw(10 + i, (COLS - strlen(menu_options[i])) / 2, "%s", menu_options[i]);
            if(i == highlight)
                attroff(A_REVERSE);
        }

        // Instruções
        mvprintw(15, (COLS - 40) / 2, "Use as setas para navegar e ENTER para selecionar");

        refresh();

        c = getch();
        switch(c) {
            case KEY_UP:
                highlight--;
                if(highlight < 0) highlight = 2;
                break;
            case KEY_DOWN:
                highlight++;
                if(highlight > 2) highlight = 0;
                break;
            case 10: // ENTER
                choice = highlight + 1;
                break;
            default:
                break;
        }

        if(choice != 0) break;
    }

    switch(choice) {
        case 1: // Jogar
            break;
        case 2: // Ajuda
            show_menu();
            break;
        case 3: // Sair
            endwin();
            exit(0);
    }
}

/*------------------------progressao de fase------------------------*/

/*
 * Verifica se todas as pílulas e pílulas de poder foram comidas.
 * Retorna true se a fase terminou, false caso contrário.*/

bool verifica_vitoria_nivel(t_game *g) {
    for (int y = 0; y < LABL; y++) {
        for (int x = 0; x < LABC - 1; x++) {
            if (g->lab[y][x] == '.' || g->lab[y][x] == 'o') {
                return false; // Ainda existem pílulas no mapa
            }
        }
    }
    return true; // Nenhuma pílula encontrada, fase concluída!
}

/*
 * Reseta o estado do mapa e dos personagens para o início de um novo nível.
 * Não reseta a pontuação nem as vidas do jogador.
 */

void prepara_proximo_nivel(t_game *g) {
    // 1. Recarrega o mapa original
    for (int y = 0; y < LABL; y++) {
        strcpy(g->lab[y], labmodel[y]);
    }

    // 2. Reseta a posição e direção do Pac-Man
    g->pacman.pos.y = 17;
    g->pacman.pos.x = 9;
    g->lab[g->pacman.pos.y][g->pacman.pos.x] = ' ';
    g->pacman.dir = left;
    g->pacman.desired_dir = left;

    // 3. Reseta a posição, modo e direção dos Fantasmas
    for (int f = blinky; f <= clyde; f++) {
        switch (f) {
            case blinky:
                g->ghost[f].pos.y = 7; g->ghost[f].pos.x = 9;
                g->lab[g->ghost[f].pos.y][g->ghost[f].pos.x] = ' ';
                break;
            case pinky:
                g->ghost[f].pos.y = 9; g->ghost[f].pos.x = 10;
                g->lab[g->ghost[f].pos.y][g->ghost[f].pos.x] = ' ';
                break;
            case inky:
                g->ghost[f].pos.y = 10; g->ghost[f].pos.x = 10;
                g->lab[g->ghost[f].pos.y][g->ghost[f].pos.x] = ' ';
                break;
            case clyde:
                g->ghost[f].pos.y = 11; g->ghost[f].pos.x = 10;
                g->lab[g->ghost[f].pos.y][g->ghost[f].pos.x] = ' ';
                break;
        }
        g->ghost[f].dir = left;
        g->ghost[f].mode = chase;
    }
}
t_game pinky_chase(t_game g) {
    int targetY = g.pacman.pos.y;
    int targetX = g.pacman.pos.x;

    switch(g.pacman.dir) {
        case up:    targetY -= 4; break;
        case down:  targetY += 4; break;
        case left:  targetX -= 4; break;
        case right: targetX += 4; break;
        default: break;
    }

    if (abs(targetY - g.ghost[pinky].pos.y) > abs(targetX - g.ghost[pinky].pos.x)) {
        g.ghost[pinky].dir = (targetY < g.ghost[pinky].pos.y) ? up : down;
    } else {
        g.ghost[pinky].dir = (targetX < g.ghost[pinky].pos.x) ? left : right;
    }
    return g;
}

// Frightened Mode: Pinky se move aleatoriamente
t_game pinky_frightened(t_game g) {
    t_direction dirs[4] = {up, down, left, right};
    g.ghost[pinky].dir = dirs[rand() % 4];
    return g;
}

// Dead Mode: Pinky volta para o centro e revive
t_game pinky_dead(t_game g) {
    int center_y = 10;
    int center_x = 10;

    if (g.ghost[pinky].pos.y < center_y)
        g.ghost[pinky].dir = down;
    else if (g.ghost[pinky].pos.y > center_y)
        g.ghost[pinky].dir = up;
    else if (g.ghost[pinky].pos.x < center_x)
        g.ghost[pinky].dir = right;
    else if (g.ghost[pinky].pos.x > center_x)
        g.ghost[pinky].dir = left;
    else
        g.ghost[pinky].mode = chase;

    return g;
}

// Home Mode: Pinky espera dentro da casa
t_game pinky_home(t_game g) {
    t_pos home = {9, 10};
    if (g.ghost[pinky].pos.y < home.y)
        g.ghost[pinky].dir = down;
    else if (g.ghost[pinky].pos.y > home.y)
        g.ghost[pinky].dir = up;
    else if (g.ghost[pinky].pos.x < home.x)
        g.ghost[pinky].dir = right;
    else if (g.ghost[pinky].pos.x > home.x)
        g.ghost[pinky].dir = left;

    return g;
}

// Atualiza Pinky conforme seu modo atual
t_game update_pinky(t_game g) {
    switch (g.ghost[pinky].mode) {
        case chase:
            return pinky_chase(g);
        case scatter:
            return pinky_home(g);
        case afraid:
            return pinky_frightened(g);
        case dead:
            return pinky_dead(g);
        default:
            return g;
    }
}


   // O '@' permanece na posição old_y, old_x.
/* ---------------------------------------------------------------------- */
/* vi: set ai et ts=4 sw=4 tw=0 wm=0 fo=croql : C config for Vim modeline */
/* Template by Dr. Beco <rcb at beco dot cc> Version 20160612.142044      */
