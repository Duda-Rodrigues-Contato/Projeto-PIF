#ifndef GAME_H
#define GAME_H

typedef struct {
    char texto[20];
    int x, y;
    int ativa;
} Palavra;

typedef struct {
    int x, y;
    int ativa;
} Inimigo;

typedef struct {
    int vidas;
    int progresso;
    int nivel;
} Jogo;

void iniciar_jogo(Jogo *jogo);
void atualizar_palavras(Palavra *palavras, int qtd);
void mover_inimigos(Inimigo *inimigos, int qtd);
void checar_digito(char input, Palavra *palavras, int qtd, Jogo *jogo);

#endif
