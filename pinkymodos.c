#include "upecman.h"
#include <stdlib.h>

// MODO CHASE — Pinky mira 4 blocos à frente do Pac-Man

t_pos pinky_chase(t_game g) {
    t_pos target = g.pacman.pos;
    switch (g.pacman.dir) {
        case up:
            target.y -= 4;
            target.x -= 4; // Comportamento clássico do jogo original
            break;
        case down:
            target.y += 4;
            break;
        case left:
            target.x -= 4;
            break;
        case right:
            target.x += 4;
            break;
        default:
            break;
    }
    return target;
}

// MODO SCATTER — Pinky foge para o canto superior esquerdo

t_pos pinky_scatter(t_game g) {
    t_pos target;
    target.y = 0;
    target.x = 0;
    return target;
}

// MODO FRIGHTENED — Pinky foge para um ponto aleatório

t_pos pinky_frightened(t_game g) {
    t_pos target;
    target.y = rand() % 23;
    target.x = rand() % 20;
    return target;
}

// MODO AFRAUD — Pinky foge para o canto inferior direito

t_pos pinky_afraud(t_game g) {
    t_pos target;
    target.y = 22;
    target.x = 18;
    return target;
}

// MODO DEAD — Pinky retorna para o centro da casa dos fantasmas

t_pos pinky_dead(t_game g) {
    t_pos target;
    target.y = 10;
    target.x = 10;
    return target;
}
