#ifndef LOGICA_H
#define LOGICA_H

#define WORD_COUNT 10
#define MAX_WORD_LEN 1  
#define TOTAL_TIME 90   
#define SPAWN_INTERVAL 2.0
typedef struct {
    char letter;
    int x, y;
    int active;
} FallingWord;
extern FallingWord words[];

typedef struct {
    int score;
    int lives;
    int current_phase;
    float time_elapsed;
    int letters_active; 
} GameState;
extern GameState game_state;


void init_game();
void restore_terminal();
void handle_sigint(int sig);
void update_game();
void draw_game();
void handle_input(int ch);



#endif