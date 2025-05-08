#ifndef LOGICA_H
#define LOGICA_H

#define WORD_COUNT 5
#define MAX_WORD_LEN 20
#define FALL_DELAY 500

typedef struct {
    char word[MAX_WORD_LEN];
    int x, y;
    int active;
} FallingWord;

typedef struct {
    int score;
    int lives;
    int current_word;
} GameState;

// Declarações de funções
void init_game();
void restore_terminal();
void handle_sigint(int sig);
void update_game();
void draw_game();
void handle_input(int ch);

#endif