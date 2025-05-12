#include "logica.h"
#include "keyboard.h"
#include "screen.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Definições das variáveis globais
GameState game_state;
FallingWord words[WORD_COUNT];
char input_buffer[MAX_WORD_LEN] = {0};
int buffer_index = 0;
int last_y_position[WORD_COUNT];

// Variáveis globais (declaradas no main.c)
extern GameState game_state;
extern FallingWord words[];
extern char input_buffer[];
extern int buffer_index;
extern int last_y_position[];

// Implementações
void generate_word(int index) {
    const char *dict[] = {"hello", "world", "cesar", "school", "keyboard"};
    strcpy(words[index].word, dict[rand() % 5]);
    words[index].x = 10 + (rand() % 60);
    words[index].y = 1;
    words[index].active = (index == 0) ? 1 : 0;
}

void init_game() {
    srand(time(NULL));
    screenInit(1);
    keyboardInit();
    timerInit(300);
    screenDrawBorders();

    for(int i = 0; i < 5; i++) {
        generate_word(i);
        last_y_position[i] = -1;
    }

    game_state.score = 0;
    game_state.lives = 3;
    game_state.current_word = 0;
}

void update_game() {
    if(timerTimeOver()) {
        for(int i = 0; i < 5; i++) {
            if(words[i].active) {
                words[i].y++;
                if(words[i].y >= 23) {
                    game_state.lives--;
                    words[i].active = 0;
                    if(game_state.current_word < 4) {
                        game_state.current_word++;
                        words[game_state.current_word].active = 1;
                    }
                }
            }
        }
    }
}

void draw_game() {
    // Limpa posições anteriores
    for(int i = 0; i < 5; i++) {
        if(words[i].active || last_y_position[i] != -1) {
            screenSetColor(DARKGRAY, DARKGRAY);
            screenGotoxy(words[i].x, last_y_position[i]);
            printf("%*s", 20, " ");
        }
    }

    // Desenha palavras ativas
    for(int i = 0; i < 5; i++) {
        if(words[i].active) {
            screenSetColor(CYAN, DARKGRAY);
            screenGotoxy(words[i].x, words[i].y);
            printf("%s", words[i].word);
            last_y_position[i] = words[i].y;
        }
    }

    // Atualiza HUD
    screenSetColor(WHITE, BLACK);
    screenGotoxy(2, 24);
    printf("Score: %d | Lives: %d | Input: %s", 
          game_state.score, game_state.lives, input_buffer);
    screenUpdate();
}

void handle_input(int ch) {
    if(ch == 127) { // Backspace
        if(buffer_index > 0) buffer_index--;
    }
    else if(isprint(ch)) {
        input_buffer[buffer_index++] = tolower(ch);
    }
    input_buffer[buffer_index] = '\0';

    // Verifica acerto
    if(strcmp(input_buffer, words[game_state.current_word].word) == 0) {
        game_state.score += 10;
        words[game_state.current_word].active = 0;
        buffer_index = 0;
        input_buffer[0] = '\0';
        if(game_state.current_word < 4) {
            game_state.current_word++;
            words[game_state.current_word].active = 1;
        }
    } else if (strlen(input_buffer) >= strlen(words[game_state.current_word].word)) {
        // Caso erre a palavra:
        game_state.lives -- ;
        buffer_index = 0;
        input_buffer[0] = '\0';
    }
}

void restore_terminal() {
    keyboardDestroy();
    screenDestroy();
    printf("\033[0m\033[?25h\n");
    fflush(stdout);
}

void handle_sigint(int sig) {
    restore_terminal();
    exit(0);
}