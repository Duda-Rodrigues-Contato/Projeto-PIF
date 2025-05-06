#include "../include/game.h"
#include "../cli-lib/cli.h"
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_PALAVRAS 5
#define MAX_INIMIGOS 5

Palavra palavras[MAX_PALAVRAS];
Inimigo inimigos[MAX_INIMIGOS];

void iniciar_jogo() {
    for (int i = 0; i < MAX_PALAVRAS; i++) {
        palavras[i].x = rand() % 40;
        palavras[i].y = 0;
        strcpy(palavras[i].palavra, "hack");
        palavras[i].ativa = 1;
    }

    for (int i = 0; i < MAX_INIMIGOS; i++) {
        inimigos[i].x = rand() % 40;
        inimigos[i].y = 20;
        inimigos[i].ativo = 1;
    }
}

void atualizar_jogo() {
    for (int i = 0; i < MAX_PALAVRAS; i++) {
        if (palavras[i].ativa) {
            palavras[i].x++; // palavras "caem" para a direita
        }
    }

    for (int i = 0; i < MAX_INIMIGOS; i++) {
        if (inimigos[i].ativo) {
            inimigos[i].y--; // inimigos sobem
        }
    }

    verificar_colisoes();
}

void desenhar_jogo() {
    cli_clear();

    for (int i = 0; i < MAX_PALAVRAS; i++) {
        if (palavras[i].ativa) {
            cli_draw_text(palavras[i].x, palavras[i].y, palavras[i].palavra);
        }
    }

    for (int i = 0; i < MAX_INIMIGOS; i++) {
        if (inimigos[i].ativo) {
            cli_draw_text(inimigos[i].x, inimigos[i].y, "V");
        }
    }

    cli_present();
}

void verificar_colisoes() {
    for (int i = 0; i < MAX_PALAVRAS; i++) {
        for (int j = 0; j < MAX_INIMIGOS; j++) {
            if (palavras[i].ativa && inimigos[j].ativo &&
                palavras[i].x == inimigos[j].x &&
                palavras[i].y == inimigos[j].y) {
                palavras[i].ativa = 0; // palavra destruída
            }
        }
    }
}
