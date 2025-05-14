#ifndef RANKING_H
#define RANKING_H

typedef struct {
    char username[50];
    int score;
} PlayerScore;

void salvarPontuacao(PlayerScore player);
void exibirRanking();

#endif
