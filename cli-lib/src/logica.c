#include "logica.h"
#include "keyboard.h"
#include "screen.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <sys/time.h>

GameState game_state;
FallingWord words[WORD_COUNT];
char input_buffer[MAX_WORD_LEN] = {0};
int buffer_index = 0;
int last_y_position[WORD_COUNT];
struct timeval start_time, last_spawn_time;

void generate_word(int index) {
    words[index].letter = 'A' + (rand() % 26); 
    words[index].x = 10 + (rand() % 60);       
    words[index].y = 1;                        
    words[index].active = 0;                   
}

void init_game() {
    gettimeofday(&start_time, NULL);
    gettimeofday(&last_spawn_time, NULL);
    srand(time(NULL)); 
    screenInit(1);
    keyboardInit();
    timerInit(300);
    screenDrawBorders();

    game_state.score = 0;
    game_state.lives = 3;
    game_state.current_phase = 1;
    game_state.time_elapsed = 0.0f;
    game_state.letters_active = 0;

    
    for(int i = 0; i < WORD_COUNT; i++) {
        generate_word(i); 
        last_y_position[i] = -1;
    }

    
    words[0].active = 1;
    game_state.letters_active++;
}

void update_phase() {

    float phase_2_threshold = 30.0f + 0.1f;
    float phase_3_threshold = 60.0f + 0.1f;

    if(game_state.time_elapsed >= phase_3_threshold && game_state.current_phase == 2) {
        printf("Teste Mudança para FASE 3 (timer = 100ms)\n");
        game_state.current_phase = 3;
        timerUpdateTimer(100);
    } else if(game_state.time_elapsed >= phase_2_threshold && game_state.current_phase == 1) {
        printf("Teste Mudança para FASE 2 (timer = 200ms)\n");
        game_state.current_phase = 2;
        timerUpdateTimer(200);
    }
}

void update_game() {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    
    
    game_state.time_elapsed = (current_time.tv_sec - start_time.tv_sec) +
                             (current_time.tv_usec - start_time.tv_usec) / 1000000.0f;

    
    update_phase();

    
    float time_since_last_spawn = (current_time.tv_sec - last_spawn_time.tv_sec) +
                                 (current_time.tv_usec - last_spawn_time.tv_usec) / 1000000.0f;

    
    if(time_since_last_spawn > SPAWN_INTERVAL && game_state.letters_active < WORD_COUNT) {
        for(int i = 0; i < WORD_COUNT; i++) {
            if(!words[i].active) {
                generate_word(i); 
                words[i].active = 1;
                game_state.letters_active++;
                gettimeofday(&last_spawn_time, NULL); 
                break;
            }
        }
    }

    
    if(timerTimeOver()) {
        for(int i = 0; i < WORD_COUNT; i++) {
            if(words[i].active) {
                words[i].y += game_state.current_phase; 

                if(words[i].y >= 23) { 
                    game_state.lives--;
                    words[i].active = 0;
                    game_state.letters_active--;
                }
            }
        }
    }
}

void draw_game() {

    
    for(int i = 0; i < WORD_COUNT; i++) {
        if(last_y_position[i] != -1) {
            screenSetColor(DARKGRAY, DARKGRAY);
            screenGotoxy(words[i].x, last_y_position[i]);
            printf(" ");
        }
    }

    
    for(int i = 0; i < WORD_COUNT; i++) {
        if(words[i].active) {
            screenSetColor(CYAN, DARKGRAY);
            screenGotoxy(words[i].x, words[i].y);
            printf("%c", words[i].letter);
            last_y_position[i] = words[i].y; 
        }
    }

    
    screenSetColor(WHITE, BLACK);
    screenGotoxy(2, 24);
    printf("Time: %02d:%02d | Phase: %d | Score: %d | Lives: %d | Input: %s",
          (int)game_state.time_elapsed / 60,
          (int)game_state.time_elapsed % 60,
          game_state.current_phase,
          game_state.score,
          game_state.lives,
          input_buffer);
    screenUpdate();
}


void handle_input(int ch) {
    
    if(ch == 127) { 
        if(buffer_index > 0) {
            buffer_index--;
            input_buffer[buffer_index] = '\0';
        }
        return; 
    }
    else if(isprint(ch)) { 
        if(buffer_index < MAX_WORD_LEN) {
            input_buffer[buffer_index++] = toupper(ch); 
            input_buffer[buffer_index] = '\0';
        }
    }

    
    if(buffer_index > 0) {
        for(int i = 0; i < WORD_COUNT; i++) {
            if(words[i].active && (input_buffer[0] == words[i].letter)) {
                game_state.score += 10;
                buffer_index = 0;
                memset(input_buffer, 0, sizeof(input_buffer)); 
                words[i].active = 0;
                game_state.letters_active--;
                break; 
            }
        }
    }

    buffer_index = 0;
    memset(input_buffer, 0, sizeof(input_buffer));

}

void restore_terminal() {
    keyboardDestroy();
    screenDestroy();
    printf("\033[0m\033[?25h\n"); 
    fflush(stdout);
}

void handle_sigint(int sig) {
    (void)sig; 
    restore_terminal();
    exit(0);
}