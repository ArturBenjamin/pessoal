#include "upecman.h"
#include <stdlib.h>

// Define o alvo da Pinky com base no modo

t_game pinky_set_target(t_game g) {
    int i = 1;
    switch (g.ghost[i].mode) {
        case chase:
            switch (g.pacman.dir) {
                case up:
                    g.ghost[i].starget.y = g.pacman.pos.y - 4;
                    g.ghost[i].starget.x = g.pacman.pos.x - 4; // peculiaridade clássica
                    break;
                case down:
                    g.ghost[i].starget.y = g.pacman.pos.y + 4;
                    g.ghost[i].starget.x = g.pacman.pos.x;
                    break;
                case left:
                    g.ghost[i].starget.y = g.pacman.pos.y;
                    g.ghost[i].starget.x = g.pacman.pos.x - 4;
                    break;
                case right:
                    g.ghost[i].starget.y = g.pacman.pos.y;
                    g.ghost[i].starget.x = g.pacman.pos.x + 4;
                    break;
                default:
                    g.ghost[i].starget = g.pacman.pos;
            }
            break;

        case scatter:
            g.ghost[i].starget.y = 0;
            g.ghost[i].starget.x = 0;
            break;

        case frightened:
            g.ghost[i].starget.y = rand() % 23;
            g.ghost[i].starget.x = rand() % 20;
            break;

        case dead:
            g.ghost[i].starget.y = 10;
            g.ghost[i].starget.x = 10;
            if (g.ghost[i].pos.y == 10 && g.ghost[i].pos.x == 10) {
                g.ghost[i].mode = chase;
            }
            break;
    }
    return g;
}

