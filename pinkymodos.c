// Pinky - MODO CHASE: Alvo a 4 blocos à frente da direção do Pac-Man
t_game chasepinky(t_game g) {
    int ypac = g.pacman.pos.y, xpac = g.pacman.pos.x;
    int yghost = g.ghost[1].pos.y, xghost = g.ghost[1].pos.x;

    int target_y = ypac;
    int target_x = xpac;

    switch (g.pacman.dir) {
        case up:    target_y -= 4; break;
        case down:  target_y += 4; break;
        case left:  target_x -= 4; break;
        case right: target_x += 4; break;
        default: break;
    }

    if (abs(target_y - yghost) > abs(target_x - xghost)) {
        if (target_y < yghost && g.lab[yghost - 1][xghost] != '#') g.ghost[1].dir = up;
        else if (g.lab[yghost + 1][xghost] != '#') g.ghost[1].dir = down;
    } else {
        if (target_x < xghost && g.lab[yghost][xghost - 1] != '#') g.ghost[1].dir = left;
        else if (g.lab[yghost][xghost + 1] != '#') g.ghost[1].dir = right;
    }
    return g;
}

// Pinky - MODO FRIGHTENED: Movimento aleatório (igual ao scatterblinky)
t_game scatterpinky(t_game g) {
    return scatterblinky(g);
}

// Pinky - MODO DEAD: Volta ao centro da casa e revive ao chegar
t_game deadpinky(t_game g) {
    int yghost = g.ghost[1].pos.y;
    int xghost = g.ghost[1].pos.x;
    int center_y = 10, center_x = 10;

    if (yghost == center_y && xghost == center_x) {
        g.ghost[1].mode = chase;
        return g;
    }

    if (abs(center_y - yghost) > abs(center_x - xghost)) {
        if (center_y < yghost && g.lab[yghost - 1][xghost] != '#') g.ghost[1].dir = up;
        else if (g.lab[yghost + 1][xghost] != '#') g.ghost[1].dir = down;
    } else {
        if (center_x < xghost && g.lab[yghost][xghost - 1] != '#') g.ghost[1].dir = left;
        else if (g.lab[yghost][xghost + 1] != '#') g.ghost[1].dir = right;
    }
    return g;
}

// Pinky - MODO HOME: Espera no canto (modo scatter, posição 0,0)
t_game homepinky(t_game g) {
    int yghost = g.ghost[1].pos.y;
    int xghost = g.ghost[1].pos.x;
    int home_y = 9, home_x = 10;

    if (abs(home_y - yghost) > abs(home_x - xghost)) {
        if (home_y < yghost && g.lab[yghost - 1][xghost] != '#') g.ghost[1].dir = up;
        else if (g.lab[yghost + 1][xghost] != '#') g.ghost[1].dir = down;
    } else {
        if (home_x < xghost && g.lab[yghost][xghost - 1] != '#') g.ghost[1].dir = left;
        else if (g.lab[yghost][xghost + 1] != '#') g.ghost[1].dir = right;
    }
    return g;
}

// Pinky - FUNÇÃO PRINCIPAL DE MOVIMENTO
t_game movepinky(t_game g, int elapsed_seconds) {
    if (elapsed_seconds < g.ghost[1].start_time) return g;

    if (g.ghost[1].mode == chase) g = chasepinky(g);
    else if (g.ghost[1].mode == frightened) g = scatterpinky(g);
    else if (g.ghost[1].mode == dead) g = deadpinky(g);
    else if (g.ghost[1].mode == home) g = homepinky(g);

    int i = 1; // Índice da Pinky
    int prev_y = g.ghost[i].pos.y, prev_x = g.ghost[i].pos.x;
    int next_y = prev_y, next_x = prev_x;

    if (g.ghost[i].dir == up && g.lab[next_y - 1][next_x] != '#') next_y--;
    else if (g.ghost[i].dir == down && g.lab[next_y + 1][next_x] != '#') next_y++;
    else if (g.ghost[i].dir == left && g.lab[next_y][next_x - 1] != '#') next_x--;
    else if (g.ghost[i].dir == right && g.lab[next_y][next_x + 1] != '#') next_x++;
    else {
        if(g.ghost[i].dir == up || g.ghost[i].dir == down)
            g.ghost[i].dir = (rand() % 2) ? left : right;
        else
            g.ghost[i].dir = (rand() % 2) ? up : down;
    }

    g.ghost[i].pos.y = next_y;
    g.ghost[i].pos.x = next_x;

    if (prev_y != next_y || prev_x != next_x) {
        mvaddch(prev_y, prev_x, g.lab[prev_y][prev_x]);
        attron(COLOR_PAIR(2));
        mvaddch(g.ghost[i].pos.y, g.ghost[i].pos.x, 'P');
        attroff(COLOR_PAIR(2));
    }
    return g;
}
