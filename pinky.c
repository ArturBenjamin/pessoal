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

    // Pinky modos: chase, scatter, dead, afraid
case(pinky):
    {
    // Sair da casa
    if (g.ghost[i].pos.y > 7 && g.ghost[i].pos.y <= 9 && g.ghost[i].pos.x == 10)
    {
        g.ghost[i].pos.y--;
        continue;
    }
    // Chase Mode — Pinky mira 4 blocos à frente do Pac-Man
    if (g.ghost[i].mode == chase)
    {
        int offsetY = 0, offsetX = 0;
        switch (g.pacman.dir)
        {
            case up:    offsetY = -4; break;
            case down:  offsetY = 4; break;
            case left:  offsetX = -4; break;
            case right: offsetX = 4; break;
            default: break;
        }

        g.ghost[i].starget.y = g.pacman.pos.y + offsetY;
        g.ghost[i].starget.x = g.pacman.pos.x + offsetX;
    }

    // Scatter Mode — vai para o canto superior esquerdo
    else if (g.ghost[i].mode == scatter)
    {
        g.ghost[i].starget.y = 0;
        g.ghost[i].starget.x = 0;
    }

    // Dead Mode — volta ao centro da "casa" e revive
    else if (g.ghost[i].mode == dead)
    {
        g.ghost[i].starget.y = 10;
        g.ghost[i].starget.x = 10;
        if (g.ghost[i].pos.y == 10 && g.ghost[i].pos.x == 10)
            g.ghost[i].mode = chase;
    }

    // Afraid Mode — movimentação aleatória
    else if (g.ghost[i].mode == afraid)
    {
        int next_y = g.ghost[i].pos.y;
        int next_x = g.ghost[i].pos.x;
        int valid = 0;
        int tentativas = 0;

        while (!valid && tentativas < 10)
        {
            int dir = rand() % 4;

            next_y = g.ghost[i].pos.y;
            next_x = g.ghost[i].pos.x;

            switch (dir)
            {
                case 0: if (g.lab[next_y - 1][next_x] != '#') next_y--; break;
                case 1: if (g.lab[next_y + 1][next_x] != '#') next_y++; break;
                case 2: if (g.lab[next_y][next_x - 1] != '#') next_x--; break;
                case 3: if (g.lab[next_y][next_x + 1] != '#') next_x++; break;
            }

            if (g.lab[next_y][next_x] != '#')
                valid = 1;

            tentativas++;
        }

        g.ghost[i].starget.y = valid ? next_y : g.ghost[i].pos.y;
        g.ghost[i].starget.x = valid ? next_x : g.ghost[i].pos.x;
    }

    break;
    return g;
}
