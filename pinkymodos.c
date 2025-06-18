// Pinky - MODO CHASE: mira 4 blocos à frente do Pacman
t_game chasepinky(t_game g) {
    int ypac = g.pacman.pos.y, xpac = g.pacman.pos.x;
    int yghost = g.ghost[1].pos.y, xghost = g.ghost[1].pos.x;

    int target_y = ypac, target_x = xpac;
    switch (g.pacman.dir) {
        case up:    target_y -= 4; break;
        case down:  target_y += 4; break;
        case left:  target_x -= 4; break;
        case right: target_x += 4; break;
        case none: break;
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

// Pinky - MODO FRIGHTENED: foge do Pacman
t_game scatterpinky(t_game g) {
    int ypac = g.pacman.pos.y, xpac = g.pacman.pos.x;
    int yghost = g.ghost[1].pos.y, xghost = g.ghost[1].pos.x;

    if (abs(ypac - yghost) < abs(xpac - xghost)) {
        if (ypac < yghost && g.lab[yghost + 1][xghost] != '#') g.ghost[1].dir = down;
        else if (g.lab[yghost - 1][xghost] != '#') g.ghost[1].dir = up;
    } else {
        if (xpac < xghost && g.lab[yghost][xghost + 1] != '#') g.ghost[1].dir = right;
        else if (g.lab[yghost][xghost - 1] != '#') g.ghost[1].dir = left;
    }

    return g;
}

// Pinky - MODO DEAD: volta para a casa central
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

// Pinky - MODO HOME: espera na posição (9,10) até hora de sair
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
