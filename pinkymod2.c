void modospinky(t_game *g)
{
    int i = 1; // Índice da Pinky
    int yp = g->pacman.pos.y;
    int xp = g->pacman.pos.x;
    int yg = g->ghost[i].pos.y;
    int xg = g->ghost[i].pos.x;

    switch (g->ghost[i].mode)
    {
        case chase:
            // Pinky tenta cortar o Pac-Man — alvo a 4 blocos à frente dele
            if (abs(yp - yg) > abs(xp - xg))
            {
                if (yp < yg && g->lab[yg - 1][xg] != '#') g->ghost[i].dir = up;
                else if (g->lab[yg + 1][xg] != '#') g->ghost[i].dir = down;
            }
            else
            {
                if (xp < xg && g->lab[yg][xg - 1] != '#') g->ghost[i].dir = left;
                else if (g->lab[yg][xg + 1] != '#') g->ghost[i].dir = right;
            }
            break;

        case frightened:
            // Pinky foge do Pac-Man
            if (abs(yp - yg) < abs(xp - xg))
            {
                if (yp < yg && g->lab[yg + 1][xg] != '#') g->ghost[i].dir = down;
                else if (g->lab[yg - 1][xg] != '#') g->ghost[i].dir = up;
            }
            else
            {
                if (xp < xg && g->lab[yg][xg + 1] != '#') g->ghost[i].dir = right;
                else if (g->lab[yg][xg - 1] != '#') g->ghost[i].dir = left;
            }
            break;

        case dead:
            // Pinky volta para o centro da casa dos fantasmas (10,10)
            if (yg > 10 && g->lab[yg - 1][xg] != '#') g->ghost[i].dir = up;
            else if (yg < 10 && g->lab[yg + 1][xg] != '#') g->ghost[i].dir = down;
            else if (xg > 10 && g->lab[yg][xg - 1] != '#') g->ghost[i].dir = left;
            else if (xg < 10 && g->lab[yg][xg + 1] != '#') g->ghost[i].dir = right;

            if (yg == 10 && xg == 10)
                g->ghost[i].mode = chase;
            break;

        case home:
            // Pinky permanece parado ou sobe caso esteja preso
            if (yg > 7 && g->lab[yg - 1][xg] != '#')
                g->ghost[i].dir = up;
            break;
    }
}
