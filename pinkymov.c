t_game pinkymove(t_game g, int elapsed_seconds)
{
    t_pos target; // Onde o Pinky quer chegar

    // =================================================================================
    // PASSO 1: CALCULAR O ALVO
    // =================================================================================
    switch (g.pacman.dir)
    {
        case up:
            target.y = g.pacman.pos.y - 4;
            target.x = g.pacman.pos.x - 4; // Peculiaridade do jogo original
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
        // Caso o Pac-Man esteja parado, o Pinky pode mirar diretamente nele
        default:
            target.y = g.pacman.pos.y;
            target.x = g.pacman.pos.x;
            break;
    }

    // =================================================================================
    // PASSO 2: ESCOLHER A MELHOR ROTA
    // =================================================================================
    long int dist_up = 99999, dist_down = 99999, dist_left = 99999, dist_right = 99999;

    // Calcula a distância para o alvo se for para CIMA
    if (g.ghost[pinky].dir != down && g.lab[g.ghost[pinky].pos.y - 1][g.ghost[pinky].pos.x] != '#')
    {
        dist_up = pow(g.ghost[pinky].pos.y - 1 - target.y, 2) + pow(g.ghost[pinky].pos.x - target.x, 2);
    }

    // Calcula a distância para o alvo se for para BAIXO
    if (g.ghost[pinky].dir != up && g.lab[g.ghost[pinky].pos.y + 1][g.ghost[pinky].pos.x] != '#')
    {
        dist_down = pow(g.ghost[pinky].pos.y + 1 - target.y, 2) + pow(g.ghost[pinky].pos.x - target.x, 2);
    }

    // Calcula a distância para o alvo se for para ESQUERDA
    if (g.ghost[pinky].dir != right && g.lab[g.ghost[pinky].pos.y][g.ghost[pinky].pos.x - 1] != '#')
    {
        dist_left = pow(g.ghost[pinky].pos.y - target.y, 2) + pow(g.ghost[pinky].pos.x - 1 - target.x, 2);
    }

    // Calcula a distância para o alvo se for para DIREITA
    if (g.ghost[pinky].dir != left && g.lab[g.ghost[pinky].pos.y][g.ghost[pinky].pos.x + 1] != '#')
    {
        dist_right = pow(g.ghost[pinky].pos.y - target.y, 2) + pow(g.ghost[pinky].pos.x + 1 - target.x, 2);
    }

    // Compara as distâncias e escolhe o menor caminho
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
    if(g.ghost[pinky].dir == up) g.ghost[pinky].pos.y--;
    else if(g.ghost[pinky].dir == down) g.ghost[pinky].pos.y++;
    else if(g.ghost[pinky].dir == left) g.ghost[pinky].pos.x--;
    else if(g.ghost[pinky].dir == right) g.ghost[pinky].pos.x++;

    // Lógica do túnel
    if (g.ghost[pinky].pos.y == 10) {
        if (g.ghost[pinky].pos.x <= 0) {
            g.ghost[pinky].pos.x = 17;
        } else if (g.ghost[pinky].pos.x >= 18) {
            g.ghost[pinky].pos.x = 1;
        }
    }

    return g;
}
