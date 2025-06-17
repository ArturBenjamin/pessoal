// Versão integrada com Pinky
// Todas as funções da Pinky + chamada no game_loop
// (Insira este bloco no final do seu upecman.c original ou compile como está)

#include <stdlib.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include "upecman.h"

// --- Funções da Pinky ---
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

    if (abs(targetY - g.ghost[1].pos.y) > abs(targetX - g.ghost[1].pos.x)) {
        g.ghost[1].dir = (targetY < g.ghost[1].pos.y) ? up : down;
    } else {
        g.ghost[1].dir = (targetX < g.ghost[1].pos.x) ? left : right;
    }
    return g;
}

t_game pinky_frightened(t_game g) {
    t_direction dirs[4] = {up, down, left, right};
    g.ghost[1].dir = dirs[rand() % 4];
    return g;
}

t_game pinky_dead(t_game g) {
    int center_y = 10;
    int center_x = 10;

    if (g.ghost[1].pos.y < center_y)
        g.ghost[1].dir = down;
    else if (g.ghost[1].pos.y > center_y)
        g.ghost[1].dir = up;
    else if (g.ghost[1].pos.x < center_x)
        g.ghost[1].dir = right;
    else if (g.ghost[1].pos.x > center_x)
        g.ghost[1].dir = left;
    else
        g.ghost[1].mode = chase;

    return g;
}

t_game pinky_home(t_game g) {
    t_pos home = {9, 10};
    if (g.ghost[1].pos.y < home.y)
        g.ghost[1].dir = down;
    else if (g.ghost[1].pos.y > home.y)
        g.ghost[1].dir = up;
    else if (g.ghost[1].pos.x < home.x)
        g.ghost[1].dir = right;
    else if (g.ghost[1].pos.x > home.x)
        g.ghost[1].dir = left;

    return g;
}

t_game update_pinky(t_game g) {
    switch (g.ghost[1].mode) {
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

// --- Atualização no game_loop ---
void game_loop(t_game *g) {
    bool game_running = true;
    int player_input_key;
    long frame_delay = 150000;

    timeout(0);
    nodelay(stdscr, TRUE);

    while(game_running) {
        g->timer.current_time = time(NULL);
        g->timer.elapsed_seconds = difftime(g->timer.current_time, g->timer.start_time);

        player_input_key = getch();

        update_upecman_state(g, player_input_key, &game_running);

        // Pinky entra após 10 segundos
        if (g->timer.elapsed_seconds >= g->ghost[1].start_time)
            *g = update_pinky(*g);

        clear();
        printlab(*g);
        display_score_lives(g);
        refresh();
        usleep(frame_delay);
    }
}
