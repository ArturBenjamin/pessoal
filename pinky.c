/***************************************************************************
 *   pinky.c - Comportamento do fantasma Pinky                            *
 ***************************************************************************/

#include "upecman.h"
#include <stdlib.h>
#include <ncurses.h>
#include <math.h>

// Chase Mode: Pinky mira 4 blocos à frente da direção do Pacman
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
