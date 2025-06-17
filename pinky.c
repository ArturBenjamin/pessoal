// Pinky Mov
t_game pinkymove(t_game g, int elapsed_seconds)
{
    // Pinky só se move após 10 segundos de jogo
    if(elapsed_seconds < g.ghost[1].start_time)
        return g;
    // Lógica para sair da casa
    if (g.ghost[1].pos.y > 7 && g.ghost[1].pos.y <= 9 && g.ghost[1].pos.x == 10)
    {
        g.ghost[1].pos.y--; // Sobe para a linha 7
        return g;
    }
    if (g.ghost[1].pos.y == 7 && g.ghost[1].pos.x >= 10 && g.ghost[1].pos.x < 12)
    {
        g.ghost[1].pos.x++; // Sai para a direita
        return g;
    }

    // Movimento no labirinto
    int prev_y = g.ghost[1].pos.y;
    int prev_x = g.ghost[1].pos.x;
    int movev[2] = {up, down};
    int moveh[2] = {left, right};
    int next_y = prev_y;
    int next_x = prev_x;

    if (g.lab[next_y - 1][next_x] == '-')
        g.ghost[1].dir = up;

    if (g.ghost[1].dir == up)
    {
        if (g.lab[next_y - 1][next_x] != '#')
            next_y--;
        else {
            g.ghost[1].dir = moveh[rand() % 2];
            next_x += (g.ghost[1].dir == left) ? -1 : 1;
        }
    }
    else if (g.ghost[1].dir == down)
    {
        if (g.lab[next_y + 1][next_x] != '#')
            next_y++;
        else {
            g.ghost[1].dir = moveh[rand() % 2];
            next_x += (g.ghost[1].dir == left) ? -1 : 1;
        }
    }
    else if (g.ghost[1].dir == left)
    {
        if (g.lab[next_y][next_x - 1] != '#')
            next_x--;
        else {
            g.ghost[1].dir = movev[rand() % 2];
            next_y += (g.ghost[1].dir == up) ? -1 : 1;
        }
    }
    else if (g.ghost[1].dir == right)
    {
        if (g.lab[next_y][next_x + 1] != '#')
            next_x++;
        else {
            g.ghost[1].dir = movev[rand() % 2];
            next_y += (g.ghost[1].dir == up) ? -1 : 1;
        }
    }

    // Atualiza posição se possível
    if (g.lab[next_y][next_x] != '#') {
        g.lab[g.ghost[1].pos.y][g.ghost[1].pos.x] = ' '; // limpa anterior
        g.ghost[1].pos.y = next_y;
        g.ghost[1].pos.x = next_x;
        g.lab[next_y][next_x] = 'P'; // marca com P de Pinky
    } else {
        g.ghost[1].pos.y = prev_y;
        g.ghost[1].pos.x = prev_x;
    }

    // Teletransporte nas bordas
    if (g.ghost[1].pos.x == 0 && g.ghost[1].pos.y == 10)
        g.ghost[1].pos.x = 17;
    else if (g.ghost[1].pos.x == 18 && g.ghost[1].pos.y == 10)
        g.ghost[1].pos.x = 1;

    return g;
}
