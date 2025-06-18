t_game modosfantasmas(t_game g)
{
    for (int i = 0; i < 4; i++)
    {
        switch (g.ghost[i].mode)
        {
            case chase:
            if (i == 1)
            {
                // Pinky
                g.ghost[i].starget = g.pacman.pos;
                switch (g.pacman.dir)
                {
                    case up:
                    g.ghost[i].starget.y -= 4;
                    g.ghost[i].starget.x -= 4;
                    break;
                    case down:
                    g.ghost[i].starget.y += 4;
                    break;
                    case left:
                    g.ghost[i].starget.x -= 4;
                    break;
                    case right:
                    g.ghost[i].starget.x += 4;
                    break;
                    default:
                    break;
                }
            }
            break;

            case scatter:
            if (i == 1)
            {
                // Pinky
                g.ghost[i].starget.y = 0;
                g.ghost[i].starget.x = 0;
            }
            break;

            case frightened:
            if (i == 1)
            {
                // Pinky
                g.ghost[i].starget.y = rand() % 23;
                g.ghost[i].starget.x = rand() % 20;
            }
            break;

            case afraud:
            if (i == 1)
            {
                // Pinky
                g.ghost[i].starget.y = 22;
                g.ghost[i].starget.x = 18;
            }
            break;

            case dead:
            if (i == 1)
            {
                // Pinky
                g.ghost[i].starget.y = 10;
                g.ghost[i].starget.x = 10;
            }
            break;

            default:
            break;
        }
    }

return g;
}
