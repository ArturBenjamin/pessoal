// PINKY - Movimento com lógica de cruzamento e anti-180° Modos

// Verifica se direções são opostas
int is_opposite_direction(int current_dir, int new_dir);

// Função que define alvo conforme o modo de Pinky
t_game pinky_set_target(t_game g) {
    int i = 1;
    switch (g.ghost[i].mode) {
        case chase: {
            int offset_y = 0, offset_x = 0;
            switch (g.pacman.dir) {
                case up: offset_y = -4; break;
                case down: offset_y = 4; break;
                case left: offset_x = -4; break;
                case right: offset_x = 4; break;
                case none: default: break;
            }
            g.ghost[i].starget.y = g.pacman.pos.y + offset_y;
            g.ghost[i].starget.x = g.pacman.pos.x + offset_x;
            break;
        }
        case scatter:
            g.ghost[i].starget.y = 0;
            g.ghost[i].starget.x = 0;
            break;
        case dead:
            g.ghost[i].starget.y = 10;
            g.ghost[i].starget.x = 10;
            break;
        case frightened:
            g.ghost[i].starget.y = rand() % 23;
            g.ghost[i].starget.x = rand() % 20;
            break;
    }
    return g;
}

t_game pinkymove(t_game g, int elapsed_seconds)
{
    int i = 1; // Índice da Pinky

    if(elapsed_seconds < g.ghost[i].start_time) return g;

    // Saída da casa
    if ((g.ghost[i].pos.y > 7 && g.ghost[i].pos.y <= 9 && g.ghost[i].pos.x == 10) ||
        (g.ghost[i].pos.y == 7 && g.ghost[i].pos.x >= 10 && g.ghost[i].pos.x < 12)) {

        int prev_y = g.ghost[i].pos.y;
        int prev_x = g.ghost[i].pos.x;

        if (g.ghost[i].pos.y > 7) { g.ghost[i].pos.y--; g.ghost[i].dir = up; }
        else if (g.ghost[i].pos.y == 7) { g.ghost[i].pos.x++; g.ghost[i].dir = right; }

        g.lab[prev_y][prev_x] = ' ';
        g.lab[g.ghost[i].pos.y][g.ghost[i].pos.x] = 'P';
        return g;
    }

    // Atualiza alvo conforme o modo
    g = pinky_set_target(g);

    // Lógica de movimento
    int prev_y = g.ghost[i].pos.y;
    int prev_x = g.ghost[i].pos.x;

    int wall_ahead = (g.ghost[i].dir == up && g.lab[prev_y - 1][prev_x] == '#') ||
                     (g.ghost[i].dir == down && g.lab[prev_y + 1][prev_x] == '#') ||
                     (g.ghost[i].dir == left && g.lab[prev_y][prev_x - 1] == '#') ||
                     (g.ghost[i].dir == right && g.lab[prev_y][prev_x + 1] == '#');

    int possible_moves = 0;
    if (g.lab[prev_y - 1][prev_x] != '#') possible_moves++;
    if (g.lab[prev_y + 1][prev_x] != '#') possible_moves++;
    if (g.lab[prev_y][prev_x - 1] != '#') possible_moves++;
    if (g.lab[prev_y][prev_x + 1] != '#') possible_moves++;

    if (wall_ahead || possible_moves > 2) {
        int best_dir = -1;
        int best_dist = 9999;
        int directions[] = {up, down, left, right};

        for (int j = 0; j < 4; j++) {
            int dir = directions[j];
            if (is_opposite_direction(g.ghost[i].dir, dir)) continue;

            int ny = prev_y, nx = prev_x;
            if (dir == up && g.lab[ny - 1][nx] != '#') ny--;
            else if (dir == down && g.lab[ny + 1][nx] != '#') ny++;
            else if (dir == left && g.lab[ny][nx - 1] != '#') nx--;
            else if (dir == right && g.lab[ny][nx + 1] != '#') nx++;
            else continue;

            int dy = abs(g.ghost[i].starget.y - ny);
            int dx = abs(g.ghost[i].starget.x - nx);
            int dist = dy + dx;

            if (dist < best_dist) {
                best_dist = dist;
                best_dir = dir;
            }
        }

        if (best_dir != -1) g.ghost[i].dir = best_dir;
    }

    // Movimento
    if(g.ghost[i].dir == up) g.ghost[i].pos.y--;
    else if(g.ghost[i].dir == down) g.ghost[i].pos.y++;
    else if(g.ghost[i].dir == left) g.ghost[i].pos.x--;
    else if(g.ghost[i].dir == right) g.ghost[i].pos.x++;

    g.lab[prev_y][prev_x] = ' ';
    g.lab[g.ghost[i].pos.y][g.ghost[i].pos.x] = 'P';

    return g;
}
