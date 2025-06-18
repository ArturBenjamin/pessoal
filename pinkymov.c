// PINKY - Movimento com lógica anti-180°

// Verifica se a direção nova é oposta à atual
int is_opposite_direction(int current_dir, int new_dir) {
    return (current_dir == up && new_dir == down) ||
           (current_dir == down && new_dir == up) ||
           (current_dir == left && new_dir == right) ||
           (current_dir == right && new_dir == left);
}

t_game pinkymove(t_game g, int elapsed_seconds)
{
    int i = 1; // Índice da Pinky

    if (elapsed_seconds < g.ghost[i].start_time) return g;

    // Saída da casa (ajustada)
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

    // Movimento com lógica anti-180°
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
        int valid_dirs[4];
        int valid_count = 0;
        int directions[] = {up, down, left, right};

        for (int j = 0; j < 4; j++) {
            int test_dir = directions[j];
            if (is_opposite_direction(g.ghost[i].dir, test_dir)) continue;

            if ((test_dir == up && g.lab[prev_y - 1][prev_x] != '#') ||
                (test_dir == down && g.lab[prev_y + 1][prev_x] != '#') ||
                (test_dir == left && g.lab[prev_y][prev_x - 1] != '#') ||
                (test_dir == right && g.lab[prev_y][prev_x + 1] != '#')) {
                valid_dirs[valid_count++] = test_dir;
            }
        }

        if (valid_count > 0) {
            g.ghost[i].dir = valid_dirs[rand() % valid_count];
        } else {
            // beco sem saída, permite 180°
            g.ghost[i].dir = (g.ghost[i].dir == up) ? down :
                            (g.ghost[i].dir == down) ? up :
                            (g.ghost[i].dir == left) ? right : left;
        }
    }

    // Move na direção escolhida
    if (g.ghost[i].dir == up) g.ghost[i].pos.y--;
    else if (g.ghost[i].dir == down) g.ghost[i].pos.y++;
    else if (g.ghost[i].dir == left) g.ghost[i].pos.x--;
    else if (g.ghost[i].dir == right) g.ghost[i].pos.x++;

    // Atualiza labirinto
    g.lab[prev_y][prev_x] = ' ';
    g.lab[g.ghost[i].pos.y][g.ghost[i].pos.x] = 'P';

    return g;
}
