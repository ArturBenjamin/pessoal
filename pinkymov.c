t_game pinkymove(t_game g, int elapsed_seconds)
{
    if (elapsed_seconds < g.ghost[pinky].start_time) return g;

    t_pos target; // Onde o Pinky quer chegar
    int y = g.ghost[pinky].pos.y;
    int x = g.ghost[pinky].pos.x;

    // =================================================================================
    // PASSO 1: CALCULAR O ALVO
    // =================================================================================
    switch (g.pacman.dir)
    {
        case up:
            target.y = g.pacman.pos.y - 4;
            target.x = g.pacman.pos.x - 4; // Peculiaridade do Pinky original
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
            break;
    }

    // =================================================================================
    // PASSO 2: ESCOLHER A MELHOR ROTA
    // =================================================================================
    long int dist_up = 99999, dist_down = 99999, dist_left = 99999, dist_right = 99999;

    if (y > 0 && g.ghost[pinky].dir != down && g.lab[y - 1][x] != '#')
        dist_up = pow(y - 1 - target.y, 2) + pow(x - target.x, 2);

    if (y < 22 && g.ghost[pinky].dir != up && g.lab[y + 1][x] != '#')
        dist_down = pow(y + 1 - target.y, 2) + pow(x - target.x, 2);

    if (x > 0 && g.ghost[pinky].dir != right && g.lab[y][x - 1] != '#')
        dist_left = pow(y - target.y, 2) + pow(x - 1 - target.x, 2);

    if (x < 19 && g.ghost[pinky].dir != left && g.lab[y][x + 1] != '#')
        dist_right = pow(y - target.y, 2) + pow(x + 1 - target.x, 2);

    if (dist_up <= dist_down && dist_up <= dist_left && dist_up <= dist_right)
        g.ghost[pinky].dir = up;
    else if (dist_down <= dist_up && dist_down <= dist_left && dist_down <= dist_right)
        g.ghost[pinky].dir = down;
    else if (dist_left <= dist_up && dist_left <= dist_down && dist_left <= dist_right)
        g.ghost[pinky].dir = left;
    else
        g.ghost[pinky].dir = right;

    // =================================================================================
    // PASSO 3: ATUALIZAR A POSIÇÃO
    // =================================================================================
    int prev_y = y, prev_x = x;

    if(g.ghost[pinky].dir == up) y--;
    else if(g.ghost[pinky].dir == down) y++;
    else if(g.ghost[pinky].dir == left) x--;
    else if(g.ghost[pinky].dir == right) x++;

    // Lógica do túnel
    if (y == 10 && x <= 0) x = 17;
    else if (y == 10 && x >= 18) x = 1;

    g.lab[prev_y][prev_x] = ' ';
    g.ghost[pinky].pos.y = y;
    g.ghost[pinky].pos.x = x;
    g.lab[y][x] = 'P';

    return g;
}
