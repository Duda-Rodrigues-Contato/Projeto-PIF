#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/ranking.h"

#define MAX_PLAYERS 100

void salvarPontuacao(PlayerScore player) {
    FILE *file = fopen("ranking.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %d\n", player.username, player.score);
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo de ranking.\n");
    }
}

int compareScores(const void *a, const void *b) {
    PlayerScore *playerA = (PlayerScore *)a;
    PlayerScore *playerB = (PlayerScore *)b;
    return playerB->score - playerA->score;
}

void exibirRanking() {
    PlayerScore players[MAX_PLAYERS];
    int count = 0;

    FILE *file = fopen("ranking.txt", "r");
    if (file != NULL) {
        while (fscanf(file, "%49s %d", players[count].username, &players[count].score) == 2 && count < MAX_PLAYERS) {
            count++;
        }
        fclose(file);
    } else {
        printf("Erro ao abrir o arquivo de ranking.\n");
        return;
    }

    qsort(players, count, sizeof(PlayerScore), compareScores);

    printf("\n--- Ranking ---\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s - %d pontos\n", i + 1, players[i].username, players[i].score);
    }
}
