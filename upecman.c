
#include "upecman.h"
#include <ncurses.h>
#include <unistd.h> // usleep

// Função principal do jogo
int main() {
    t_game g = upecman_init(); // Função fictícia para iniciar o jogo
    int elapsed_seconds = 0;

    initscr(); noecho(); cbreak(); keypad(stdscr, TRUE); curs_set(0);
    timeout(100); // 100ms de espera por entrada = 10 FPS (~10 ciclos por segundo)

    while (1) {
        int ch = getch();
        g = handle_input(g, ch); // Processa teclas para controlar o Pacman
        g = update_game(g, elapsed_seconds); // Atualiza movimentação, lógica e pontuação
        draw_game(g); // Atualiza a tela com base no estado do jogo

        elapsed_seconds++;
        usleep(100000); // Espera 100ms (1/10 segundo)
    }

    endwin();
    return 0;
}
