#ifndef LOGICA_H
#define LOGICA_H

#define WORD_COUNT 10
#define MAX_WORD_LEN 1  
#define TOTAL_TIME 90   
#define SPAWN_INTERVAL 2.0
typedef struct {
    char letra;
    int x, y;
    int ativo;
} palavrasCaindo;
extern palavrasCaindo words[];

typedef struct {
    int score;
    int vidas;
    int faseAtual;
    float tempoContrario;
    int letrasAtivas; 
} gameConfig;
extern gameConfig game_config;


void init_game();
void restore_terminal();
void handle_sigint(int sig);
void update_game();
void draw_game();
void handle_input(int ch);



#endif