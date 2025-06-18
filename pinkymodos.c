// MODO CHASE — Pinky mira 4 blocos à frente do Pac-Man
t_pos pinky_chase(t_game g) {
t_pos target = g.pacman.pos;

cpp
Copiar
Editar
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

// Clipping de limites do labirinto
if (target.y < 0) target.y = 0;
if (target.x < 0) target.x = 0;
if (target.y >= LAB_HEIGHT) target.y = LAB_HEIGHT - 1;
if (target.x >= LAB_WIDTH) target.x = LAB_WIDTH - 1;

return target;
}

// MODO FRIGHTENED — Pinky foge para uma posição aleatória
t_pos pinky_frightened(t_game g) {
t_pos target;
do {
target.y = rand() % LAB_HEIGHT;
target.x = rand() % LAB_WIDTH;
} while (g.lab[target.y][target.x] == '#');
return target;
}

// MODO AFRAID — Pinky vai para o canto inferior direito
t_pos pinky_afraid(t_game g) {
t_pos target;
target.y = LAB_HEIGHT - 2;
target.x = LAB_WIDTH - 2;
return target;
}

// MODO DEAD — Pinky volta para o centro da casa dos fantasmas (10, 10)
t_pos pinky_dead(t_game g) {
t_pos target;
target.y = 10;
target.x = 10;
return target;
}
