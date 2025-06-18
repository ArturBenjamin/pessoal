// ====================================================================
// PINKY - Corrigido para NÃO COMER PASTILHAS
// ====================================================================
t_game pinkymove(t_game g, int elapsed_seconds)
{
    int i = 1; // Índice do Pinky
    if (elapsed_seconds < g.ghost[i].start_time)
        return g;

    // LÓGICA DE SAÍDA DA CASA (CORRIGIDA)
    if ((g.ghost[i].pos.y > 7 && g.ghost[i].pos.y <= 9 && g.ghost[i].pos.x == 10) ||
        (g.ghost[i].pos.y == 7 && g.ghost[i].pos.x >= 10 && g.ghost[i].pos.x < 12)) {

        // A lógica de saída agora só atualiza a posição e direção do fantasma.
        if (g.ghost[i].pos.y > 7) {
            g.ghost[i].pos.y--;
            g.ghost[i].dir = up;
        } else if (g.ghost[i].pos.y == 7) {
            g.ghost[i].pos.x++;
            g.ghost[i].dir = right;
        }

        // --- CORREÇÃO APLICADA ---
        // As linhas que modificavam g.lab foram removidas daqui.
        // g.lab[prev_y][prev_x] = ' ';
        // g.lab[g.ghost[i].pos.y][g.ghost[i].pos.x] = 'P';
        
        return g;
    }

    // A sua lógica de IA a partir daqui está ótima e será mantida.
    t_pos target;
    int y = g.ghost[i].pos.y;
    int x = g.ghost[i].pos.x;

    // =================================================================================
    // PASSO 1: CALCULAR O ALVO (Sem alterações)
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
    // PASSO 2: ESCOLHER A MELHOR ROTA (Sem alterações)
    // =================================================================================
    long int dist_up = 99999, dist_down = 99999, dist_left = 99999, dist_right = 99999;

    if (y > 0 && g.ghost[i].dir != down && g.lab[y - 1][x] != '#')
        dist_up = (y - 1 - target.y)(y - 1 - target.y) + (x - target.x)(x - target.x);

    if (y < 22 && g.ghost[i].dir != up && g.lab[y + 1][x] != '#')
        dist_down = (y + 1 - target.y)(y + 1 - target.y) + (x - target.x)(x - target.x);

    if (x > 0 && g.ghost[i].dir != right && g.lab[y][x - 1] != '#')
        dist_left = (y - target.y)(y - target.y) + (x - 1 - target.x)(x - 1 - target.x);

    if (x < 19 && g.ghost[i].dir != left && g.lab[y][x + 1] != '#')
        dist_right = (y - target.y)(y - target.y) + (x + 1 - target.x)(x + 1 - target.x);

    if (dist_up <= dist_down && dist_up <= dist_left && dist_up <= dist_right)
        g.ghost[i].dir = up;
    else if (dist_down <= dist_up && dist_down <= dist_left && dist_down <= dist_right)
        g.ghost[i].dir = down;
    else if (dist_left <= dist_up && dist_left <= dist_down && dist_left <= dist_right)
        g.ghost[i].dir = left;
    else
        g.ghost[i].dir = right;

    // =================================================================================
    // PASSO 3: ATUALIZAR A POSIÇÃO (Com a correção)
    // =================================================================================
    // A variável 'y' e 'x' são locais, precisamos atualizar a estrutura principal 'g'
    if(g.ghost[i].dir == up) g.ghost[i].pos.y--;
    else if(g.ghost[i].dir == down) g.ghost[i].pos.y++;
    else if(g.ghost[i].dir == left) g.ghost[i].pos.x--;
    else if(g.ghost[i].dir == right) g.ghost[i].pos.x++;

    // Lógica do túnel
    if (g.ghost[i].pos.y == 10 && g.ghost[i].pos.x <= 0) g.ghost[i].pos.x = 17;
    else if (g.ghost[i].pos.y == 10 && g.ghost[i].pos.x >= 18) g.ghost[i].pos.x = 1;

    // --- CORREÇÃO APLICADA ---
    // As linhas que modificavam g.lab foram removidas daqui também.
    // g.lab[prev_y][prev_x] = ' ';
    // g.lab[y][x] = 'P';

    return g;
}
