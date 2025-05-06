#ifndef GAME_H
#define GAME_H

typedef struct {
    int x, y;
    char palavra[20];
    int ativa;
} Palavra;

typedef struct {
    int x, y;
    int ativo;
} Inimigo;

void iniciar_jogo();
void atualizar_jogo();
void desenhar_jogo();
void verificar_colisoes();

#endif
