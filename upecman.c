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

#include <curses.h>
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
    bool wants_to_play_again = true;

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
                if(optopt == 0 || opterr == 0)
                    fprintf(stderr, "Unknown option '-%c'.\n", optopt);
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

    while (wants_to_play_again)
    {
        // Inicializa um jogo completamente novo
        g = upecman_init();
        g.timer.start_time = time(NULL);

        // Roda o loop de um jogo até o fim
        game_loop(&g);

        // Mostra a tela de Game Over e captura a escolha do jogador
        int player_choice = show_game_over_ascii(&g);

        if (player_choice == 1) // Jogador quer reiniciar
        {
            wants_to_play_again = true;
        }
        else // Jogador quer sair
        {
            wants_to_play_again = false;
        }
    }

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
    g.pacman.start.y = g.pacman.pos.y;
    g.pacman.start.x = g.pacman.pos.x;
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

    // define a posição e a aparição da cereja
    g.cereja_apareceu = 0;
    g.cereja_apareceu_na_fase = 0;
    g.cereja_foi_coletada = 0;
    g.cereja.x = -1;
    g.cereja.y = -1;

    // Ghosts initial setup
    for(f = blinky; f <= clyde; f++)
    {
        switch(f)
        {
            case blinky: // 'B'
                g.ghost[f].pos.y = 7;
                g.ghost[f].pos.x = 9;
                g.ghost[f].starget.y = 0;
                g.ghost[f].starget.x = 19;
                g.lab[g.ghost[f].pos.y][g.ghost[f].pos.x] = ' '; // Clear 'B' from map
                break;
            case pinky: // 'P'
                g.ghost[f].pos.y = 9;
                g.ghost[f].pos.x = 10;
                g.ghost[f].starget.y = 0;
                g.ghost[f].starget.x = 0;
                g.lab[g.ghost[f].pos.y][g.ghost[f].pos.x] = ' '; // Clear 'P' from map
                break;
            case inky: // 'I'
                g.ghost[f].pos.y = 10;
                g.ghost[f].pos.x = 10;
                g.ghost[f].starget.y = 22;
                g.ghost[f].starget.x = 19;
                g.lab[g.ghost[f].pos.y][g.ghost[f].pos.x] = ' '; // Clear 'I' from map
                break;
            case clyde: // 'C'
                g.ghost[f].pos.y = 11;
                g.ghost[f].pos.x = 10;
                g.ghost[f].starget.y = 22;
                g.ghost[f].starget.x = 0;
                g.lab[g.ghost[f].pos.y][g.ghost[f].pos.x] = ' '; // Clear 'C' from map
                break;
        }
        g.ghost[f].dir = left;
        g.ghost[f].mode = chase;
        g.ghost[f].start.y = g.ghost[f].pos.y;
        g.ghost[f].start.x = g.ghost[f].pos.x;
    }
    // Ncurses init calls (initscr, cbreak, etc.) are MOVED to main()
    return g;
}

/* ---------------------------------------------------------------------- */
void printlab(t_game g)
{
    int y, x, f;

    // 1. Print the static labyrinth (walls, dots, pills, empty spaces)
    //    These are already in g.lab from upecman_init
    for(y = 0; y < LABL; y++)
    {
        for(x = 0; x < LABC - 1; x++)    // LABC-1 because labmodel strings are LABC-1 char long + null
            mvaddch(y, x, g.lab[y][x]);
    }

    // 2. Print Ghosts
    char ghost_char;
    for(f = blinky; f <= clyde; f++)
    {
        switch(f)
        {
            case blinky:
                ghost_char = 'B';
                break;
            case pinky:
                ghost_char = 'P';
                break;
            case inky:
                ghost_char = 'I';
                break;
            case clyde:
                ghost_char = 'C';
                break;
            default:
                ghost_char = '?';
                break; // Should not happen
        }
        attron(COLOR_PAIR(f + 1) | A_BOLD); // Ghost colors are 1-4
        mvaddch(g.ghost[f].pos.y, g.ghost[f].pos.x, ghost_char);
        attroff(COLOR_PAIR(f + 1) | A_BOLD);

        if (g.ghost[f].mode == afraid)
        {
            // Par de cores 5 é o azul para fantasmas assustados
            attron(COLOR_PAIR(5) | A_BOLD);
        }
        else
        {
            // Cores normais dos fantasmas (1 a 4)
            attron(COLOR_PAIR(f + 1) | A_BOLD);
        }

        mvaddch(g.ghost[f].pos.y, g.ghost[f].pos.x, ghost_char);

        // Desliga a cor que foi ligada
        if (g.ghost[f].mode == afraid) {
            attroff(COLOR_PAIR(5) | A_BOLD);
        } else {
            attroff(COLOR_PAIR(f + 1) | A_BOLD);
        }

    }
    /* clear(); */

    // 3. Print Pacman
    attron(COLOR_PAIR(6) | A_BOLD); // Pacman color is 6 (Yellow)
    mvaddch(g.pacman.pos.y, g.pacman.pos.x, '@');
    attroff(COLOR_PAIR(6) | A_BOLD);
}

/* ---------------------------------------------------------------------- */
void display_score_lives(t_game *g)
{
    mvprintw(LABL, 0, "Score: %-7d Lives: %d", g->pacman.score, g->pacman.life);
}

/* ---------------------------------------------------------------------- */
bool is_wall(t_game *g, int y, int x)
{
    if(y < 0 || y >= LABL || x < 0 || x >= (LABC - 1))    // LABC-1 for valid game columns
    {
        return true; // Out of bounds is a wall
    }
    // Check against the base labyrinth stored in g->lab
    return g->lab[y][x] == '#';
}

/* ---------------------------------------------------------------------- */
void update_upecman_state(t_game *g, int player_input_key, bool *game_running)
{
    int next_y, next_x;
    int desired_next_y, desired_next_x;

    // Handle player input to set desired direction
    switch(player_input_key)
    {
        case KEY_UP:
            g->pacman.desired_dir = up;
            break;
        case KEY_DOWN:
            g->pacman.desired_dir = down;
            break;
        case KEY_LEFT:
            g->pacman.desired_dir = left;
            break;
        case KEY_RIGHT:
            g->pacman.desired_dir = right;
            break;
        case 'q':
            *game_running = false;
            return;
        default:
            break;
    }

    // Current Pac-Man position
    int old_y = g->pacman.pos.y;
    int old_x = g->pacman.pos.x;

    // Try to move in the desired direction first
    desired_next_y = old_y;
    desired_next_x = old_x;

    switch(g->pacman.desired_dir)
    {
        case up:
            desired_next_y--;
            break;
        case down:
            desired_next_y++;
            break;
        case left:
            desired_next_x--;
            break;
        case right:
            desired_next_x++;
            break;
        case none:
            break;
    }

    // Check if desired direction is valid
    if(!is_wall(g, desired_next_y, desired_next_x))
    {
        g->pacman.pos.y = desired_next_y;
        g->pacman.pos.x = desired_next_x;
        g->pacman.dir = g->pacman.desired_dir;
    }
    else
    {
        // If desired direction is blocked, try current direction
        next_y = old_y;
        next_x = old_x;

        switch(g->pacman.dir)
        {
            case up:
                next_y--;
                break;
            case down:
                next_y++;
                break;
            case left:
                next_x--;
                break;
            case right:
                next_x++;
                break;
            case none:
                break;
        }

        if(!is_wall(g, next_y, next_x))
        {
            g->pacman.pos.y = next_y;
            g->pacman.pos.x = next_x;
        }
    }

    // Tunnel logic
    if(g->pacman.pos.y == 10)
    {
        if(g->pacman.pos.x == 0 && g->pacman.dir == left)
            g->pacman.pos.x = LABC - 2;
        else
            if(g->pacman.pos.x == LABC - 2 && g->pacman.dir == right)
                g->pacman.pos.x = 0;
    }

    // Check for dots and pills
    char cell = g->lab[g->pacman.pos.y][g->pacman.pos.x];
    if(cell == '.')
    {
        g->pacman.score += 10;
        g->lab[g->pacman.pos.y][g->pacman.pos.x] = ' ';
    }
    else
        if(cell == 'o')
        {
            g->pacman.score += 50;
            g->lab[g->pacman.pos.y][g->pacman.pos.x] = ' ';
            // TODO: Activate afraid mode for ghosts

            activate_power_pill_mode(g);
        }
        else
            if(cell == '%')
            {
                g->pacman.score += 500;
                g->lab[g->pacman.pos.y][g->pacman.pos.x] = ' ';
                g->cereja_foi_coletada = 1;
                cereja_desapareceu(g);
            }
}
/* ---------------------------------------------------------------------- */
void game_loop(t_game *g)
{
    IFDEBUG("game_loop()");
    //bool game_running = true;
    int player_input_key;
    long frame_delay = 250000; // microseconds (250ms)

    // Set non-blocking input
    timeout(0);
    //nodelay(stdscr, TRUE); // Alternative to timeout(0)

    while(g->pacman.life > 0)
    {
        if (g->power_pill_active)
        {
            g->power_pill_timer.current_time = time(NULL);
            g->power_pill_timer.elapsed_seconds = difftime(g->power_pill_timer.current_time, g->power_pill_timer.start_time);

            // Define a duração do poder (ex: 10 segundos)
            if (g->power_pill_timer.elapsed_seconds >= 10)
            {
                deactivate_power_pill_mode(g);
            }
        }



        // calcula o tempo decorrido
        g->timer.current_time = time(NULL);
        g->timer.elapsed_seconds = difftime(g->timer.current_time, g->timer.start_time);

        g->cereja_timer.current_time = time(NULL);
        g->cereja_timer.elapsed_seconds = difftime(g->cereja_timer.current_time, g->cereja_timer.start_time);

        g->cereja_espera.current_time = time(NULL);
        g->cereja_espera.elapsed_seconds = difftime(g->cereja_espera.current_time, g->cereja_espera.start_time);

        //verifica se já se passaram 20 segundos
        if(g->timer.elapsed_seconds >= 20 && g->cereja_apareceu == 0 && g->cereja_apareceu_na_fase == 0)
        {
            cereja_apareceu(g);
            g->cereja_apareceu_na_fase = 1;
        }
        else
            if(g->cereja_timer.elapsed_seconds >= 10 && g->cereja_apareceu == 1 && g->cereja_foi_coletada == 0)
            {
                cereja_desapareceu(g);
                g->cereja_espera.start_time = time(NULL);
            }
                if (verifica_vitoria_nivel(g))
        {
            clear();
            mvprintw(LABL / 2, (COLS - 15) / 2, "FASE COMPLETA!");
            refresh();
            sleep(2);

            prepara_proximo_nivel(g);
            if (frame_delay > 50000) frame_delay -= 10000;
            continue;
        }

        // Get input
        player_input_key = getch();

        // Verifica se a tecla de pausa foi pressionada
        if (player_input_key == 'p' || player_input_key == 'P')
        {
           bool restarted = pause_game_and_show_menu(g, &frame_delay);

            // Se o jogo foi reiniciado, pula para a próxima iteração do loop
            if (restarted)
            {
                continue;
            }
        }
        if (player_input_key == 'q' || player_input_key == 'Q')
        {
             // Se o jogador aperta 'q', saímos do loop imediatamente.
             break;
        }


        // Update game state
        update_upecman_state(g, player_input_key, NULL);

                // --- Chamada dos movimentos dos fantasmas aqui ---
            blinkymove(g, g->timer.elapsed_seconds);
            pinkymove(g, g->timer.elapsed_seconds);
            inkymove(g, g->timer.elapsed_seconds);
            clydemove(g, g->timer.elapsed_seconds);

            check_collisions(g);
        {

            // Check if game should end
        //if(!game_running) break;

        // Draw everything
        clear();
        printlab(*g);
        display_score_lives(g);

        // Debug info (can be removed later)
        //mvprintw(LABL + 2, 0, "Current direction: %d, Desired: %d",
        //         g->pacman.dir, g->pacman.desired_dir);
        //mvprintw(LABL + 3, 0, "Position: Y=%d, X=%d",
        //         g->pacman.pos.y, g->pacman.pos.x);
        mvprintw(LABL + 1, 0, "Time: %d",
                 g->timer.elapsed_seconds);

        mvprintw(LABL + 3, 0, "Pressione [p] para pausar o jogo");

        refresh();

        // Control game speed
        usleep(frame_delay);
        }
        }
}
/*------------------------------------------------------------------------------------*/

void draw_ascii_art(void)
{
    for(int i = 0; i < 5; i++)
    {
        int start_col = (COLS - strlen(menu_title[i])) / 2;

        // "U" → colunas 2 a 6
        attron(COLOR_PAIR(1)); // vermelho
        mvprintw(3 + i, start_col, "%.5s", &menu_title[i][2]);
        attroff(COLOR_PAIR(1));

        // "PE" → colunas 7 a 18
        attron(COLOR_PAIR(5)); // azul
        printw("%.12s", &menu_title[i][7]);
        attroff(COLOR_PAIR(5));

        // "CMAN" → colunas 19 em diante
        attron(COLOR_PAIR(6)); // amarelo
        printw("%s", &menu_title[i][19]);
        attroff(COLOR_PAIR(6));
    }
}

void show_menu(void)
{
    int highlight = 0;
    int choice = 0;
    int c;
    int ymax, xmax;

    while(1)
    {
        getmaxyx(stdscr, ymax, xmax);
        clear();
        draw_ascii_art();

        // Desenha opções do menu
        for(int i = 0; i < 3; i++)
        {
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
        switch(c)
        {
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

    switch(choice)
    {
        case 1: // Jogar
            break;
        case 2: // Ajuda
            clear();

            mvprintw(4, (xmax / 2) - 9, "Tutorial!");
            mvchgat(4, (xmax / 2) - 9, -1, A_BOLD, 6, NULL);
            attron(COLOR_PAIR(6));

            // Seção de Objetivos do Jogo
            mvprintw(7, (xmax / 2) - 53, "Objetivo do jogo: Sua missão é guiar o Pacman (@) para consumir todas as pílulas dispersas pelo labirinto.");

            // Seção de Mecânicas do Jogo
            mvprintw(9, (xmax / 2) - 53, "Instruções Cruciais: Mantenha o Pacman longe dos fantasmas (identificados como I, P, B, C). A coleta de pílulas resultará em pontos para voce.");


            // Seção de Pontuação e Vidas
            mvprintw(11, (xmax / 2) - 53, "Pontuação: Pílulas comuns (10 pontos), Pílulas grandes (50 pontos), Fantasmas (500 pontos).");
            mvprintw(13, (xmax / 2) - 53, "Vidas Disponíveis: Você possui um total de 3 vidas. Eh imperativo que você evite qualquer contato com os fantasmas para não perdê-las!");

            // Controles
            mvprintw(15, (xmax / 2) - 53, "Comandos: Para mover o Pacman, utilize as setas direcionais do seu teclado.");

            // Voltar para o menu
            mvprintw((ymax - 10), (xmax / 2) - 53, "Aperte [b] para voltar a tela inicial.");

            attroff(COLOR_PAIR(6));

            refresh();

            do {
                c = getch();
            } while (c != 'b');

            show_menu();
        break;
        case 3: // Sair
            endwin();
            exit(0);
    }
}

void display_pause_menu(int selected_option)
{
    clear();
    mvprintw(LABL / 2 - 2, (COLS - 12) / 2, "JOGO PAUSADO");

    // Opção Retornar ao Jogo
    if (selected_option == 0)
        attron(A_REVERSE); // Destaca a opção
    mvprintw(LABL / 2, (COLS - 16) / 2, "Retornar ao Jogo");
    if (selected_option == 0)
        attroff(A_REVERSE);

    // Opção Reiniciar Jogo
    if (selected_option == 1)
        attron(A_REVERSE);
    mvprintw(LABL / 2 + 1, (COLS - 15) / 2, "Reiniciar o Jogo");
    if (selected_option == 1)
        attroff(A_REVERSE);

    // Opção Sair do Jogo
    if (selected_option == 2)
        attron(A_REVERSE);
    mvprintw(LABL / 2 + 2, (COLS - 12) / 2, "Sair do Jogo");
    if (selected_option == 2)
        attroff(A_REVERSE);

    refresh();
}

bool pause_game_and_show_menu(t_game *g, long *frame_delay)
{
    bool in_pause_menu = true;
    bool game_restarted = false;
    int selected_option = 0;
    int menu_input;

    // Mede o tempo de início da pausa para ajustar os timers depois
    time_t pause_start_time = time(NULL);
    timeout(-1); // Muda para entrada bloqueante para o menu

    while(in_pause_menu)
    {
        display_pause_menu(selected_option);
        menu_input = getch();

        switch(menu_input)
        {
            case KEY_UP: case 'w':
                selected_option = (selected_option == 0) ? 2 : selected_option - 1;
                break;
            case KEY_DOWN: case 's':
                selected_option = (selected_option == 2) ? 0 : selected_option + 1;
                break;
            case 'p': case 'P': // Permite sair da pausa com 'p' também
                in_pause_menu = false;
                break;
            case '\n': // Tecla Enter
                switch(selected_option)
                {
                    case 0: // Retornar ao Jogo
                        in_pause_menu = false;
                        break;
                    case 1: // Reiniciar o Jogo
                        restart_game(g, frame_delay);
                        game_restarted = true;
                        in_pause_menu = false;
                        break;
                    case 2: // Sair do Jogo
                        g->pacman.life = 0;
                        in_pause_menu = false;
                        break;
                }
                break;
        }
    }

    // Ajusta os timers se o jogo não foi reiniciado ou encerrado
    if (g->pacman.life > 0 && !game_restarted)
    {
        long pause_duration = difftime(time(NULL), pause_start_time);
        g->timer.start_time += pause_duration;
        g->cereja_timer.start_time += pause_duration;
        g->cereja_espera.start_time += pause_duration;
        if (g->power_pill_active) {
            g->power_pill_timer.start_time += pause_duration;
        }
    }

    timeout(0);
    return game_restarted;
}

void restart_game(t_game *g, long *frame_delay)
{
    IFDEBUG("restart_game()");
    // Reinicia a estrutura principal do jogo
    *g = upecman_init();

    // Define o tempo inicial para o novo jogo
    g->timer.start_time = time(NULL);

    // Reseta a velocidade do jogo (dificuldade) para o valor inicial
    *frame_delay = 250000;
}

int show_game_over_ascii(t_game *g)
{
    // Texto de game over
    const char *gameOverArt[] = {
      "  #####      #      #   #   #####        ###    #   #   #####   ####  ",
      " #          # #     ## ##   #           #   #   #   #   #       #   # ",
      " # ###     #####    # # #   ####        #   #   #   #   ####    ####  ",
      " #   #    #     #   #   #   #           #   #    # #    #       #  #  ",
      "  #####  #       #  #   #   #####        ###      #     #####   #   # "
    };
    int art_height = 5;
    int lins, cols;

    clear();
    getmaxyx(stdscr, lins, cols);

    // Calcula a posição para centralizar
    int start_y = (lins - art_height) / 2 - 3;

    attron(COLOR_PAIR(1) | A_BOLD); // Usa a cor vermelha e negrito
    for (int i = 0; i < art_height; i++)
    {
        // Centraliza cada linha individualmente
        int start_x = (cols - strlen(gameOverArt[i])) / 2;
        mvprintw(start_y + i, start_x, "%s", gameOverArt[i]);
    }
    attroff(COLOR_PAIR(1) | A_BOLD);

    // Exibe as informações abaixo
    int info_y = start_y + art_height + 2;
    mvprintw(info_y, (cols - 21) / 2, "OBRIGADO POR JOGAR!");
    mvprintw(info_y + 1, (cols - 28) / 2, "Sua pontuação final foi: %d", g->pacman.score);

    attron(A_BLINK);
    mvprintw(info_y + 4, (cols - 43) / 2, "Pressione 'R' para jogar novamente ou 'Q' para sair");
    attroff(A_BLINK);

    refresh();

    // Aguarda a decisão do jogador
    int choice;
    timeout(-1);
    noecho();
    while (1)
    {
        choice = getch();
        if (choice == 'r' || choice == 'R')
        {
            return 1; // Sinaliza para reiniciar
        }
        else if (choice == 'q' || choice == 'Q')
        {
            return 0; // Sinaliza para sair
        }
    }
}

/*------------------------progressao de fase------------------------*/

/*
 * Verifica se todas as pílulas e pílulas de poder foram comidas.
 * Retorna true se a fase terminou, false caso contrário.*/

bool verifica_vitoria_nivel(t_game *g)
{
    for(int y = 0; y < LABL; y++)
    {
        for(int x = 0; x < LABC - 1; x++)
        {
            if(g->lab[y][x] == '.' || g->lab[y][x] == 'o')
            {
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

void prepara_proximo_nivel(t_game *g)
{

    //Reinicia o tempo
    g->timer.start_time = time(NULL);

    //Faz a cereja poder aparecer de novo
    g->cereja_apareceu_na_fase = 0;

    // 1. Recarrega o mapa original
    for(int y = 0; y < LABL; y++)
        strcpy(g->lab[y], labmodel[y]);

    // 2. Reseta a posição e direção do Pac-Man
    g->pacman.pos.y = 17;
    g->pacman.pos.x = 9;
    g->lab[g->pacman.pos.y][g->pacman.pos.x] = ' ';
    g->pacman.dir = left;
    g->pacman.desired_dir = left;

    // 3. Reseta a posição, modo e direção dos Fantasmas
    for(int f = blinky; f <= clyde; f++)
    {
        switch(f)
        {
            case blinky:
                g->ghost[f].pos.y = 7;
                g->ghost[f].pos.x = 9;
                g->lab[g->ghost[f].pos.y][g->ghost[f].pos.x] = ' ';
                break;
            case pinky:
                g->ghost[f].pos.y = 9;
                g->ghost[f].pos.x = 10;
                g->lab[g->ghost[f].pos.y][g->ghost[f].pos.x] = ' ';
                break;
            case inky:
                g->ghost[f].pos.y = 10;
                g->ghost[f].pos.x = 10;
                g->lab[g->ghost[f].pos.y][g->ghost[f].pos.x] = ' ';
                break;
            case clyde:
                g->ghost[f].pos.y = 11;
                g->ghost[f].pos.x = 10;
                g->lab[g->ghost[f].pos.y][g->ghost[f].pos.x] = ' ';
                break;
        }
        g->ghost[f].dir = left;
        g->ghost[f].mode = chase;
    }
}

void cereja_apareceu(t_game *g)
{
    g->cereja.x = 9;
    g->cereja.y = 13;
    g->lab[g->cereja.y][g->cereja.x] = '%';
    g->cereja_apareceu = 1;
    g->cereja_foi_coletada = 0;
    g->cereja_timer.start_time = time(NULL);
}

void cereja_desapareceu(t_game *g)
{
    g->lab[g->cereja.y][g->cereja.x] = ' ';
    g->cereja.x = -1;
    g->cereja.y = -1;
    g->cereja_apareceu = 0;
}
/*------------------------Fantasmas Movimentação------------------------*/

// Função auxiliar pra verificar se duas direções são opostas.
int is_opposite_direction(int current_dir, int new_dir) {
    if (current_dir == up && new_dir == down) return 1;
    if (current_dir == down && new_dir == up) return 1;
    if (current_dir == left && new_dir == right) return 1;
    if (current_dir == right && new_dir == left) return 1;
    return 0;
}
// Função para calcular a distância
int distance_squared(int y1, int x1, int y2, int x2) {
    int dy = y2 - y1;
    int dx = x2 - x1;
    return (dy * dy) + (dx * dx);
}

// FUNÇÃO Blinky

void blinkymove(t_game *g, int elapsed_seconds)
{
    int i = 0; // Índice do Blinky.

    // 1. VERIFICAÇÃO INICIAL
    if(elapsed_seconds < g->ghost[i].start_time) {
        return;
    }

    int prev_y = g->ghost[i].pos.y;
    int prev_x = g->ghost[i].pos.x;
    int final_dir = g->ghost[i].dir; // Inicia com a direção atual como padrão.

    // 2. LÓGICA DE MOVIMENTO BASEADA NO MODO
    if (g->ghost[i].mode == afraid)
    {
        // MODO AFRAID: Movimento aleatório.
        int valid_dirs[4];
        int valid_count = 0;
        int directions[] = {up, down, left, right};

        // Tenta escolher uma nova direção em cruzamentos ou becos sem saída.
        int possible_moves = 0;
        for (int j = 0; j < 4; j++) {
            int next_y = prev_y, next_x = prev_x;
            if (directions[j] == up) next_y--; else if (directions[j] == down) next_y++;
            else if (directions[j] == left) next_x--; else if (directions[j] == right) next_x++;
            if (next_y < 0 || next_y >= LABL || next_x < 0 || next_x >= LABC - 1) continue;
            if (g->lab[next_y][next_x] != '#') possible_moves++;
        }

        int wall_ahead = (g->lab[prev_y + (g->ghost[i].dir == down) - (g->ghost[i].dir == up)]
                                [prev_x + (g->ghost[i].dir == right) - (g->ghost[i].dir == left)] == '#');

        if (wall_ahead || possible_moves > 2) {
             for (int j = 0; j < 4; j++) {
                if (is_opposite_direction(g->ghost[i].dir, directions[j])) continue;

                int next_y = prev_y, next_x = prev_x;
                if (directions[j] == up) next_y--; else if (directions[j] == down) next_y++;
                else if (directions[j] == left) next_x--; else if (directions[j] == right) next_x++;

                if (next_y < 0 || next_y >= LABL || next_x < 0 || next_x >= LABC - 1) continue;

                if (g->lab[next_y][next_x] != '#') {
                    valid_dirs[valid_count++] = directions[j];
                }
            }
            if (valid_count > 0) final_dir = valid_dirs[rand() % valid_count];
        }
    }
    else // Modos baseados em ALVO: chase, scatter, dead.
    {
        t_pos target;

        // Define o alvo de acordo com o modo.
        switch(g->ghost[i].mode) {
            case chase:
                target = g->pacman.pos;
                break;
            //case scatter:
            //    target = g->ghost[i].starget;
            //    break;
            //case dead:
            //    target.y = 7; target.x = 9; // Alvo: entrada da casa dos fantasmas.
            //    if (g->ghost[i].pos.y == target.y && g->ghost[i].pos.x == target.x) {
            //        g->ghost[i].mode = chase; // Revive ao chegar.
            //    }
            //    break;
            default:
                target = g->pacman.pos; // Padrão para chase.
                break;
        }

        // Algoritmo de busca de caminho para encontrar a melhor direção.
        int min_dist = 999999;
        int best_dir = -1;
        int directions[] = {up, down, left, right};

        for(int j = 0; j < 4; j++) {
            int test_dir = directions[j];
            if (is_opposite_direction(g->ghost[i].dir, test_dir)) continue;

            int next_y = prev_y, next_x = prev_x;
            if (test_dir == up) next_y--; else if (test_dir == down) next_y++;
            else if (test_dir == left) next_x--; else if (test_dir == right) next_x++;

            // Verificação de segurança 1: Limites do mapa.
            if (next_y < 0 || next_y >= LABL || next_x < 0 || next_x >= LABC - 1) continue;

            // Verificação de segurança 2: Paredes (com lógica para o modo 'dead').
            if (g->ghost[i].mode != dead) {
                if (g->lab[next_y][next_x] == '#' || g->lab[next_y][next_x] == '-') continue;
                if (is_ghost_in_house((t_pos){next_y, next_x})) continue;
            } else { // Se morto, só não pode atravessar paredes '#'.
                if (g->lab[next_y][next_x] == '#') continue;
            }

            // Se a direção é válida, calcula qual o deixa mais perto do alvo.
            int dist = distance_squared(next_y, next_x, target.y, target.x);
            if (dist < min_dist) {
                min_dist = dist;
                best_dir = test_dir;
            }
        }

        if (best_dir != -1) {
            final_dir = best_dir;
        } else { // Fallback: se ficou preso, inverte a direção.
            if(g->ghost[i].dir == up) final_dir = down; else if(g->ghost[i].dir == down) final_dir = up;
            else if(g->ghost[i].dir == left) final_dir = right; else if(g->ghost[i].dir == right) final_dir = left;
        }
    }

    g->ghost[i].dir = final_dir;

    // 3. APLICA O MOVIMENTO
    if(g->ghost[i].dir == up) g->ghost[i].pos.y--;
    else if(g->ghost[i].dir == down) g->ghost[i].pos.y++;
    else if(g->ghost[i].dir == left) g->ghost[i].pos.x--;
    else if(g->ghost[i].dir == right) g->ghost[i].pos.x++;

    // 4. APLICA A LÓGICA DO TÚNEL
    if (g->ghost[i].pos.y == 10) {
        if (g->ghost[i].pos.x <= 0 && g->ghost[i].dir == left) g->ghost[i].pos.x = LABC - 2;
        else if (g->ghost[i].pos.x >= LABC - 2 && g->ghost[i].dir == right) g->ghost[i].pos.x = 0;
    }
}
// INKY Movimento
void inkymove(t_game *g, int elapsed_seconds)
{
    int i = 2; // Índice do Inky

    if (elapsed_seconds < g->ghost[i].start_time) {
        return;
    }

    // --- LÓGICA DE SAÍDA DA CASA  ---
    if (is_ghost_in_house(g->ghost[i].pos))
    {
        if (g->ghost[i].pos.y > 7) {
            g->ghost[i].pos.y--;
        } else if (g->ghost[i].pos.x > 9) {
            g->ghost[i].pos.x--;
        }
        return;
    }

    // A IA do Inky é sempre aleatória, não precisa de if/else para o modo
    int prev_y = g->ghost[i].pos.y, prev_x = g->ghost[i].pos.x;
    int wall_ahead = (g->ghost[i].dir == up && g->lab[prev_y - 1][prev_x] == '#') || (g->ghost[i].dir == down && g->lab[prev_y + 1][prev_x] == '#') || (g->ghost[i].dir == left && g->lab[prev_y][prev_x - 1] == '#') || (g->ghost[i].dir == right && g->lab[prev_y][prev_x + 1] == '#');
    int possible_moves = 0;
if (g->lab[prev_y - 1][prev_x] != '#')
    possible_moves++;
if (g->lab[prev_y + 1][prev_x] != '#')
    possible_moves++;
if (g->lab[prev_y][prev_x - 1] != '#')
    possible_moves++;
if (g->lab[prev_y][prev_x + 1] != '#'){
    possible_moves++;
}

    if (wall_ahead || possible_moves > 2) {
        int valid_dirs[4], valid_count = 0, directions[] = {up, down, left, right};
        for(int j = 0; j < 4; j++) {
            int test_dir = directions[j];
            if (is_opposite_direction(g->ghost[i].dir, test_dir)) continue;
            int next_y = prev_y, next_x = prev_x;
            if (test_dir == up) next_y--; else if (test_dir == down) next_y++;
            else if (test_dir == left) next_x--; else if (test_dir == right) next_x++;
            if (g->lab[next_y][next_x] != '#') valid_dirs[valid_count++] = test_dir;
        }
        if (valid_count > 0) g->ghost[i].dir = valid_dirs[rand() % valid_count];
    }

    if(g->ghost[i].dir == up) g->ghost[i].pos.y--;
    else if(g->ghost[i].dir == down) g->ghost[i].pos.y++;
    else if(g->ghost[i].dir == left) g->ghost[i].pos.x--;
    else if(g->ghost[i].dir == right) g->ghost[i].pos.x++;

    if (g->ghost[i].pos.y == 10) {
        if (g->ghost[i].pos.x <= 0) { g->ghost[i].pos.x = LABC - 2; }
        else if (g->ghost[i].pos.x >= LABC - 2) { g->ghost[i].pos.x = 0; }
    }
}
// PINKY Movimento
void pinkymove(t_game *g, int elapsed_seconds)
{
    int i = 1; // Índice do Pinky

    if (elapsed_seconds < g->ghost[i].start_time) {
        return;
    }

    // --- LÓGICA DE SAÍDA DA CASA ---
    // O objetivo é levar o fantasma até a saída em (Y=7, X=9)
    if (is_ghost_in_house(g->ghost[i].pos))
    {
        // Se não está na linha da porta, move para cima.
        if (g->ghost[i].pos.y > 7) {
            g->ghost[i].pos.y--;
        }
        // Se já está na linha da porta (y=7), mas não na coluna de saída (x=9), move para o lado.
        else if (g->ghost[i].pos.x < 9) {
            g->ghost[i].pos.x++;
        }
        else if (g->ghost[i].pos.x > 9) {
            g->ghost[i].pos.x--;
        }
        return; // Pula o resto da IA até o fantasma sair completamente.
    }

    // --- LÓGICA DE MODO AFRAID ---
    if (g->ghost[i].mode == afraid)
    {
        // (lógica de movimento aleatório para fugir)
        int prev_y = g->ghost[i].pos.y, prev_x = g->ghost[i].pos.x;
        int valid_dirs[4], valid_count = 0, directions[] = {up, down, left, right};
        for (int j=0; j<4; j++) {
            int test_dir = directions[j];
            if (is_opposite_direction(g->ghost[i].dir, test_dir)) continue;
            int next_y = prev_y, next_x = prev_x;
            if (test_dir == up) next_y--; else if (test_dir == down) next_y++;
            else if (test_dir == left) next_x--; else if (test_dir == right) next_x++;
            if (g->lab[next_y][next_x] != '#') valid_dirs[valid_count++] = test_dir;
        }
        if (valid_count > 0) g->ghost[i].dir = valid_dirs[rand() % valid_count];
    }
    else // --- LÓGICA DE MODO CHASE ---
    {
        // (Lógica de perseguição original do Pinky)
        t_pos target;
        switch (g->pacman.dir) {
            case up:    target.y = g->pacman.pos.y - 4; target.x = g->pacman.pos.x - 4; break;
            case down:  target.y = g->pacman.pos.y + 4; target.x = g->pacman.pos.x;     break;
            case left:  target.y = g->pacman.pos.y;     target.x = g->pacman.pos.x - 4; break;
            case right: target.y = g->pacman.pos.y;     target.x = g->pacman.pos.x + 4; break;
            default:    target = g->pacman.pos; break;
        }
        int best_dir = -1, min_dist = 999999, directions[] = {up, down, left, right};
        for(int j=0; j<4; ++j){
            if (is_opposite_direction(g->ghost[i].dir, directions[j])) continue;
            int next_y = g->ghost[i].pos.y, next_x = g->ghost[i].pos.x;
            if (directions[j] == up) next_y--; else if (directions[j] == down) next_y++;
            else if (directions[j] == left) next_x--; else if (directions[j] == right) next_x++;
            if (g->lab[next_y][next_x] == '#') continue;
            int dist = distance_squared(next_y, next_x, target.y, target.x);
            if (dist < min_dist) { min_dist = dist; best_dir = directions[j]; }
        }
        if (best_dir != -1) g->ghost[i].dir = best_dir;
    }

    // --- APLICA O MOVIMENTO E TELEPORTE (COMUM A TODOS OS MODOS) ---
    if(g->ghost[i].dir == up) g->ghost[i].pos.y--;
    else if(g->ghost[i].dir == down) g->ghost[i].pos.y++;
    else if(g->ghost[i].dir == left) g->ghost[i].pos.x--;
    else if(g->ghost[i].dir == right) g->ghost[i].pos.x++;

    if (g->ghost[i].pos.y == 10) {
        if (g->ghost[i].pos.x <= 0) { g->ghost[i].pos.x = LABC - 2; }
        else if (g->ghost[i].pos.x >= LABC - 2) { g->ghost[i].pos.x = 0; }
    }
}
// CLYDE
void clydemove(t_game *g, int elapsed_seconds)
{
    int i = 3; // Índice do Clyde

    if (elapsed_seconds < g->ghost[i].start_time) {
        return;
    }

    // --- LÓGICA DE SAÍDA DA CASA ---
    if (is_ghost_in_house(g->ghost[i].pos))
    {
        if (g->ghost[i].pos.y > 7) {
            g->ghost[i].pos.y--;
        } else if (g->ghost[i].pos.x < 9) {
            g->ghost[i].pos.x++;
        }
        return;
    }

    // A IA do Clyde é sempre aleatória, não precisa de if/else para o modo
    int prev_y = g->ghost[i].pos.y, prev_x = g->ghost[i].pos.x;
    int wall_ahead = (g->ghost[i].dir == up && g->lab[prev_y - 1][prev_x] == '#') || (g->ghost[i].dir == down && g->lab[prev_y + 1][prev_x] == '#') || (g->ghost[i].dir == left && g->lab[prev_y][prev_x - 1] == '#') || (g->ghost[i].dir == right && g->lab[prev_y][prev_x + 1] == '#');
    int possible_moves = 0;
    if (g->lab[prev_y - 1][prev_x] != '#')
         possible_moves++;
    if (g->lab[prev_y + 1][prev_x] != '#')
         possible_moves++;
    if (g->lab[prev_y][prev_x - 1] != '#')
         possible_moves++;
    if (g->lab[prev_y][prev_x + 1] != '#')
         possible_moves++;

    if (wall_ahead || possible_moves > 2) {
        int valid_dirs[4], valid_count = 0, directions[] = {up, down, left, right};
        for(int j = 0; j < 4; j++) {
            int test_dir = directions[j];
            if (is_opposite_direction(g->ghost[i].dir, test_dir)) continue;
            int next_y = prev_y, next_x = prev_x;
            if (test_dir == up) next_y--; else if (test_dir == down) next_y++;
            else if (test_dir == left) next_x--; else if (test_dir == right) next_x++;
            if (g->lab[next_y][next_x] != '#') valid_dirs[valid_count++] = test_dir;
        }
        if (valid_count > 0) g->ghost[i].dir = valid_dirs[rand() % valid_count];
    }

    if(g->ghost[i].dir == up) g->ghost[i].pos.y--;
    else if(g->ghost[i].dir == down) g->ghost[i].pos.y++;
    else if(g->ghost[i].dir == left) g->ghost[i].pos.x--;
    else if(g->ghost[i].dir == right) g->ghost[i].pos.x++;

    if (g->ghost[i].pos.y == 10) {
        if (g->ghost[i].pos.x <= 0) { g->ghost[i].pos.x = LABC - 2; }
        else if (g->ghost[i].pos.x >= LABC - 2) { g->ghost[i].pos.x = 0; }
    }
}
/*------------------------------------ colisões ----------------------------------*/

void check_collisions(t_game *g)
{
    // Itera sobre todos os fantasmas para verificar colisões
            for (int i = 0; i < 4 ; i++)
            {
             if (g->pacman.pos.x == g->ghost[i].pos.x && g->pacman.pos.y == g->ghost[i].pos.y)
             {
             if (g->ghost[i].mode == afraid) {
             g->pacman.score += 750;
            // Retorna o fantasma para sua posição inicial na "casa" dos fantasmas

             g->ghost[i].pos.x = g->ghost[i].start.x;
             g->ghost[i].pos.y = g->ghost[i].start.y;

             g->ghost[i].mode = chase;

     }
             else
     {
    // Fantasma não está assustado: Pac-Man morre
         g->pacman.life--;

 if (g->pacman.life > 0)
                {
                    reset_positions_after_death(g);
                }

         break;
      }
    }
  }
}

void reset_positions_after_death(t_game *g)
{
    // Reseta a posição e direção do Pac-Man
    g->pacman.pos.x = g->pacman.start.x;
    g->pacman.pos.y = g->pacman.start.y;
    g->pacman.dir = none;
    g->pacman.desired_dir = none;

    // Reseta a posição e direção de todos os fantasmas
    for (int i = 0; i < 4; i++)
    {
        g->ghost[i].pos.x = g->ghost[i].start.x;
        g->ghost[i].pos.y = g->ghost[i].start.y;
        g->ghost[i].dir = none;
    }

    // Isso dá tempo para o jogador se preparar para o reinício da ação.
    clear();
    printlab(*g); // Desenha o labirinto e os personagens em suas novas posições
    display_score_lives(g);
    mvprintw(g->pacman.start.y, g->pacman.start.x - 4, "PRONTO?");
    refresh();
    sleep(1); // Pausa por 1 segundo
}
/* ----------------------------Modo afraid------------------------------- */


bool is_ghost_in_house(t_pos ghost_pos)
{
    if (ghost_pos.y >= 8 && ghost_pos.y <= 12 &&
        ghost_pos.x >= 7 && ghost_pos.x <= 13)
    {
        return true;
    }
    return false;
}

void deactivate_power_pill_mode(t_game *g)
{
    g->power_pill_active = false;
    for (int i = 0; i < 4; i++)
    {
        // Só afeta fantasmas que ainda estavam no modo 'afraid'
        if (g->ghost[i].mode == afraid)
        {
            g->ghost[i].mode = chase;
        }
    }
}

void activate_power_pill_mode(t_game *g)
{
    g->power_pill_active = true;
    g->power_pill_timer.start_time = time(NULL);

    for (int i = 0; i < 4; i++)
    {
        // A pílula só afeta fantasmas que não estão na casa
        if (!is_ghost_in_house(g->ghost[i].pos))
        {
            g->ghost[i].mode = afraid;

        }
    }
}







/* ---------------------------------------------------------------------- */
 /* vi: set ai et ts=4 sw=4 tw=0 wm=0 fo=croql : C config for Vim modeline */
 /* Template by Dr. Beco <rcb at beco dot cc> Version 20160612.142044      */
