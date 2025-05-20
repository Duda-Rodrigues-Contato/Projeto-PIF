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

gameConfig game_config;
palavrasCaindo palavras[WORD_COUNT];
char input_buffer[MAX_WORD_LEN] = {0};
int buffer_index = 0;
int ultimaPosicao_y[WORD_COUNT];
struct timeval tempoInicial, ultimoSpawnTempo;

void generate_word(int index) {
    palavras[index].letra = 'A' + (rand() % 26);
    palavras[index].x = SCRSTARTX + (rand() % (SCRENDX - SCRSTARTX));
    palavras[index].y = 2;
    palavras[index].ativo = 0;
    palavras[index].cor = rand() % 6 + 1;
}

void init_game() {
    gettimeofday(&tempoInicial, NULL);
    gettimeofday(&ultimoSpawnTempo, NULL);
    srand(time(NULL));
    screenInit(1);
    keyboardInit();
    timerInit(300);
    screenDrawBorders();

    game_config.score = 0;
    game_config.vidas = 3;
    game_config.faseAtual = 1;
    game_config.tempoContrario = 0.0f;
    game_config.letrasAtivas = 0;

    for(int i = 0; i < WORD_COUNT; i++) {
        generate_word(i);
        ultimaPosicao_y[i] = -1;
    }

    palavras[0].ativo = 1;
    game_config.letrasAtivas++;
}

void update_phase() {
    float tempoAlteradoFase2 = 30.0f + 0.1f;
    float tempoAlteradoFase3 = 60.0f + 0.1f;

    if(game_config.tempoContrario >= tempoAlteradoFase3 && game_config.faseAtual == 2) {
        game_config.faseAtual = 3;
        timerUpdateTimer(125);
    } else if(game_config.tempoContrario >= tempoAlteradoFase2 && game_config.faseAtual == 1) {
        game_config.faseAtual = 2;
        timerUpdateTimer(200);
    }
}

void update_game() {
    struct timeval current_time;
    gettimeofday(&current_time, NULL);

    game_config.tempoContrario = (current_time.tv_sec - tempoInicial.tv_sec) +
                                 (current_time.tv_usec - tempoInicial.tv_usec) / 1000000.0f;

    update_phase();

    float tempoDesdeUltimoSpawn = (current_time.tv_sec - ultimoSpawnTempo.tv_sec) +
                                  (current_time.tv_usec - ultimoSpawnTempo.tv_usec) / 1000000.0f;

    int letrasParaSpawnar = game_config.faseAtual;

    if(tempoDesdeUltimoSpawn > SPAWN_INTERVAL) {
        int contSpawn = 0;
        for(int i = 0; i < WORD_COUNT && contSpawn < letrasParaSpawnar; i++) {
            if(!palavras[i].ativo) {
                generate_word(i);
                palavras[i].ativo = 1;
                game_config.letrasAtivas++;
                contSpawn++;
            }
        }
        gettimeofday(&ultimoSpawnTempo, NULL);
    }

    if(timerTimeOver()) {
        for(int i = 0; i < WORD_COUNT; i++) {
            if(palavras[i].ativo) {
                palavras[i].y += 1;
                palavras[i].cor = rand() % 6 + 1;

                if(palavras[i].y >= SCRENDY) {
                    game_config.vidas--;
                    palavras[i].ativo = 0;
                    game_config.letrasAtivas--;
                }
            }
        }
    }
}

void draw_game() {
    for(int i = 0; i < WORD_COUNT; i++) {
        if(ultimaPosicao_y[i] != -1) {
            screenSetColor(CYAN, DARKGRAY);
            screenGotoxy(palavras[i].x, ultimaPosicao_y[i]);
            printf(" ");
            screenUpdate();
        }
    }

    for(int i = 0; i < WORD_COUNT; i++) {
        if(palavras[i].ativo && palavras[i].y < MAXY) {
            int cor = palavras[i].cor;
            switch (cor) {
                case 1: screenSetColor(RED, DARKGRAY); break;
                case 2: screenSetColor(GREEN, DARKGRAY); break;
                case 3: screenSetColor(YELLOW, DARKGRAY); break;
                case 4: screenSetColor(BLUE, DARKGRAY); break;
                case 5: screenSetColor(MAGENTA, DARKGRAY); break;
                case 6: screenSetColor(CYAN, DARKGRAY); break;
                default: screenSetColor(WHITE, DARKGRAY); break;
            }

            screenGotoxy(palavras[i].x, palavras[i].y);
            printf("%c", palavras[i].letra);
            ultimaPosicao_y[i] = palavras[i].y;
        }
    }

    screenSetColor(WHITE, BLACK);
    screenGotoxy(77, 54);
    printf("Tempo: %02d:%02d | Fase: %d | Score: %d | Vidas: %d",
          (int)game_config.tempoContrario / 60,
          (int)game_config.tempoContrario % 60,
          game_config.faseAtual,
          game_config.score,
          game_config.vidas);
    screenUpdate();
}

void handle_input(int ch) {
    int letracerta = 0; 

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
            if(palavras[i].ativo && (input_buffer[0] == palavras[i].letra)) {
                game_config.score += 10;
                letracerta = 1; 
                palavras[i].ativo = 0;
                game_config.letrasAtivas--;
                break;
            }
        }

        
        if(!letracerta && game_config.vidas > 0) {
            game_config.vidas--;
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
