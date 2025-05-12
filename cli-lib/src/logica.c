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

// Variáveis globais
GameState game_state;
FallingWord words[WORD_COUNT];
char input_buffer[MAX_WORD_LEN] = {0};
int buffer_index = 0;
int last_y_position[WORD_COUNT];
struct timeval start_time, last_spawn_time;

// Implementações
void generate_word(int index) {
    words[index].letter = 'A' + (rand() % 26); // Letra aleatória (A-Z)
    words[index].x = 10 + (rand() % 60);       // Posição X aleatória (10-70)
    words[index].y = 1;                        // Sempre começa no topo (Y=1)
    words[index].active = 0;                   // Inicia desativada
}

void init_game() {
    gettimeofday(&start_time, NULL);
    gettimeofday(&last_spawn_time, NULL);
    srand(time(NULL)); // Inicializa gerador de números aleatórios
    screenInit(1);
    keyboardInit();
    timerInit(300);
    screenDrawBorders();

    // Inicialização do estado do jogo
    game_state.score = 0;
    game_state.lives = 3;
    game_state.current_phase = 1;
    game_state.time_elapsed = 0.0f;
    game_state.letters_active = 0;

    // Preenche o array de letras
    for(int i = 0; i < WORD_COUNT; i++) {
        generate_word(i); // Gera letra inicial
        last_y_position[i] = -1;
    }

    // Ativa a primeira letra
    words[0].active = 1;
    game_state.letters_active++;
}

void update_phase() {

    float phase_2_threshold = 30.0f + 0.1f;
    float phase_3_threshold = 60.0f + 0.1f;

    if(game_state.time_elapsed >= phase_3_threshold && game_state.current_phase != 3) {
        printf("Teste Mudança para FASE 3 (timer = 100ms)\n");
        game_state.current_phase = 3;
        timerUpdateTimer(100);
    } else if(game_state.time_elapsed >= phase_2_threshold && game_state.current_phase != 2) {
        printf("Teste Mudança para FASE 2 (timer = 200ms)\n");
        game_state.current_phase = 2;
        timerUpdateTimer(200);
    }
}

void update_game() {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);
    
    // Atualiza tempo total decorrido
    game_state.time_elapsed = (current_time.tv_sec - start_time.tv_sec) +
                             (current_time.tv_usec - start_time.tv_usec) / 1000000.0f;

    // Atualiza a fase do jogo
    update_phase();

    // Calcula tempo desde o último spawn
    float time_since_last_spawn = (current_time.tv_sec - last_spawn_time.tv_sec) +
                                 (current_time.tv_usec - last_spawn_time.tv_usec) / 1000000.0f;

    // Lógica de spawn de novas letras
    if(time_since_last_spawn > SPAWN_INTERVAL && game_state.letters_active < WORD_COUNT) {
        for(int i = 0; i < WORD_COUNT; i++) {
            if(!words[i].active) {
                generate_word(i); // Gera nova letra com posição aleatória
                words[i].active = 1;
                game_state.letters_active++;
                gettimeofday(&last_spawn_time, NULL); // Reinicia timer
                break;
            }
        }
    }

    // Atualiza posição das letras ativas
    if(timerTimeOver()) {
        for(int i = 0; i < WORD_COUNT; i++) {
            if(words[i].active) {
                words[i].y += game_state.current_phase; // Movimento vertical

                if(words[i].y >= 23) { // Letra atingiu a base
                    game_state.lives--;
                    words[i].active = 0;
                    game_state.letters_active--;
                }
            }
        }
    }
}

void draw_game() {

    // Limpa posições anteriores
    for(int i = 0; i < WORD_COUNT; i++) {
        if(last_y_position[i] != -1) {
            screenSetColor(DARKGRAY, DARKGRAY);
            screenGotoxy(words[i].x, last_y_position[i]);
            printf(" ");
        }
    }

    // Desenha letras ativas
    for(int i = 0; i < WORD_COUNT; i++) {
        if(words[i].active) {
            screenSetColor(CYAN, DARKGRAY);
            screenGotoxy(words[i].x, words[i].y);
            printf("%c", words[i].letter);
            last_y_position[i] = words[i].y; // Atualiza última posição
        }
    }

    // Atualiza HUD (interface do usuário)
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

    int matched = 0;
    
    if(ch == 127) { // Backspace
        if(buffer_index > 0) {
            buffer_index--;
            input_buffer[buffer_index] = '\0';
        }
        return; //Não processa msi nada se for backspace
    }
    else if(isprint(ch)) { // Caractere imprimível
        if(buffer_index < MAX_WORD_LEN) {
            input_buffer[buffer_index++] = toupper(ch); // Converte para maiúscula
            input_buffer[buffer_index] = '\0';
        }
    }

    // Verifica se o input corresponde a alguma letra ativa
    if(buffer_index > 0) {
        for(int i = 0; i < WORD_COUNT; i++) {
            if(words[i].active && (input_buffer[0] == words[i].letter)) {
                game_state.score += 10;
                buffer_index = 0;
                memset(input_buffer, 0, sizeof(input_buffer)); // Limpa o buffer
                words[i].active = 0;
                game_state.letters_active--;
                break; // Sai após o primeiro acerto
            }
        }
    }

    buffer_index = 0;
    memset(input_buffer, 0, sizeof(input_buffer));

}

void restore_terminal() {
    keyboardDestroy();
    screenDestroy();
    printf("\033[0m\033[?25h\n"); // Códigos ANSI para resetar o terminal
    fflush(stdout);
}

void handle_sigint(int sig) {
    (void)sig; // Elimina warning de parâmetro não utilizado
    restore_terminal();
    exit(0);
}