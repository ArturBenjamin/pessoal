
#ifndef UPECMAN_H
#define UPECMAN_H

#define LABL 23
#define LABC 20

typedef enum { up, down, left, right, none } t_direction;
typedef enum { chase, scatter, afraid, dead } t_ghostmode;

typedef struct {
    int y;
    int x;
} t_pos;

typedef struct {
    t_pos pos;
    t_direction dir;
    int life;
    int score;
} t_pacman;

typedef struct {
    t_pos pos;
    t_direction dir;
    t_pos starget;
    t_ghostmode mode;
    int start_time;
} t_ghost;

typedef struct {
    char lab[LABL][LABC];
    t_pacman pacman;
    t_ghost ghost[4];
} t_game;

// Funções principais do jogo
t_game upecman_init();
t_game handle_input(t_game g, int ch);
t_game update_game(t_game g, int elapsed_seconds);
void draw_game(t_game g);

#endif
