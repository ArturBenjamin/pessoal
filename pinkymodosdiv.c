t_pos pinky_chase_target(t_game g) {
    t_pos target;

    switch (g.pacman.dir) {
        case up:
            target.y = g.pacman.pos.y - 4;
            target.x = g.pacman.pos.x - 4; // comportamento clássico
            break;
        case down:
            target.y = g.pacman.pos.y + 4;
            target.x = g.pacman.pos.x;
            break;
        case left:
            target.y = g.pacman.pos.y;
            target.x = g.pacman.pos.x - 4;
            break;
        case right:
            target.y = g.pacman.pos.y;
            target.x = g.pacman.pos.x + 4;
            break;
        default:
            target = g.pacman.pos;
    }

    // Garantir que não vá para fora do mapa
    if (target.x < 0) target.x = 0;
    if (target.x >= LAB_WIDTH) target.x = LAB_WIDTH - 1;
    if (target.y < 0) target.y = 0;
    if (target.y >= LAB_HEIGHT) target.y = LAB_HEIGHT - 1;

    return target;
}

t_pos pinky_frightened_target(t_game g) {
    t_pos random;
    random.x = rand() % LAB_WIDTH;
    random.y = rand() % LAB_HEIGHT;
    return random;
}

t_pos pinky_dead_target() {
    t_pos house = { .x = 10, .y = 9 }; // centro da casa
    return house;
}

t_pos pinky_home_target() {
    t_pos home = { .x = 11, .y = 9 }; // ponto de saída da casa
    return home;
}

Colocar esse no mov:

t_pos target;

switch (g.ghost[i].mode) {
    case chase:
        target = pinky_chase_target(g);
        break;
    case frightened:
        target = pinky_frightened_target(g);
        break;
    case dead:
        target = pinky_dead_target();
        break;
    case home:
        target = pinky_home_target();
        break;
    default:
        target = g.pacman.pos;
        break;
}
