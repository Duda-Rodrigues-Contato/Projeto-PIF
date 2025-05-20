#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/ranking.h"

#define MAX_PLAYERS 100
#define MAX_LINE 128

void salvarPontuacao(PlayerScore player) {
    FILE *file = fopen("ranking.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %d\n", player.username, player.score);
        fclose(file);
    } else {
        fprintf(stderr, "Erro ao abrir o arquivo de ranking.\n");
    }
}

int compareScores(const void *a, const void *b) {
    PlayerScore *playerA = (PlayerScore *)a;
    PlayerScore *playerB = (PlayerScore *)b;
    return playerB->score - playerA->score;
}

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../include/ranking.h"

#define MAX_PLAYERS 100
#define MAX_LINE 128

void salvarPontuacao(PlayerScore player) {
    FILE *file = fopen("ranking.txt", "a");
    if (file != NULL) {
        fprintf(file, "%s %d\n", player.username, player.score);
        fclose(file);
    } else {
        fprintf(stderr, "Erro ao abrir o arquivo de ranking.\n");
    }
}

int compareScores(const void *a, const void *b) {
    PlayerScore *playerA = (PlayerScore *)a;
    PlayerScore *playerB = (PlayerScore *)b;
    return playerB->score - playerA->score;
}

void exibirRanking() {
    PlayerScore *players = malloc(sizeof(PlayerScore) * MAX_PLAYERS);
    int count = 0;

    if (players == NULL) {
        fprintf(stderr, "Erro de alocação de memória.\n");
        return;
    }

    FILE *file = fopen("ranking.txt", "r");
    if (file != NULL) {
        char line[MAX_LINE];
        while (fgets(line, sizeof(line), file) && count < MAX_PLAYERS) {
            if (sscanf(line, "%49s %d", players[count].username, &players[count].score) == 2) {
                count++;
            }
        }
        fclose(file);
    } else {
        fprintf(stderr, "Erro ao abrir o arquivo de ranking.\n");
        free(players);
        return;
    }

    qsort(players, count, sizeof(PlayerScore), compareScores);

    printf("\n--- Ranking ---\n");
    int top = count < 10 ? count : 10;
    for (int i = 0; i < top; i++) {
        printf("%d. %s - %d pontos\n", i + 1, players[i].username, players[i].score);
    }

    free(players);
}
