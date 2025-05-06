#include "game.h"
#include <string.h>

void iniciar_jogo(Jogo *jogo) {
    jogo->vidas = 3;
    jogo->progresso = 0;
    jogo->nivel = 1;
}

void atualizar_palavras(Palavra *palavras, int qtd) {
    for (int i = 0; i < qtd; i++) {
        if (palavras[i].ativa) {
            palavras[i].y += 1;
        }
    }
}

void mover_inimigos(Inimigo *inimigos, int qtd) {
    for (int i = 0; i < qtd; i++) {
        if (inimigos[i].ativa) {
            inimigos[i].y -= 1;
        }
    }
}

void checar_digito(char input, Palavra *palavras, int qtd, Jogo *jogo) {
    for (int i = 0; i < qtd; i++) {
        if (palavras[i].ativa && palavras[i].texto[0] == input) {
            memmove(palavras[i].texto, palavras[i].texto + 1, strlen(palavras[i].texto));
            if (strlen(palavras[i].texto) == 0) {
                palavras[i].ativa = 0;
                jogo->progresso += 10;
            }
            break;
        }
    }
}
