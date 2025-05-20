#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include "keyboard.h"
#include "screen.h"
#include "timer.h"
#include "logica.h"
#include "../include/ranking.h"

int main() {
    char username[50];

    printf("Digite seu nome de usuário: ");
    scanf("%49s", username);

    signal(SIGINT, handle_sigint);
    atexit(restore_terminal);
    
    init_game();

    while (game_config.vidas > 0 && game_config.tempoContrario < TOTAL_TIME) {
        if (keyhit()) {
            handle_input(readch());
        }
        update_game();
        draw_game();
    }

    screenClear();
    screenGotoxy(35, 12);

    if (game_config.tempoContrario >= TOTAL_TIME) {
        printf("O TEMPO ACABOU! Final Score: %d", game_config.score);
    } else {
        printf("FIM DE JOGO! Final Score: %d", game_config.score);
    }
    screenUpdate();

    timerInit(3000);
    while (!timerTimeOver());

    PlayerScore jogador;
    strcpy(jogador.username, username);

    jogador.score = game_config.score;

    salvarPontuacao(jogador);
    exibirRanking();

    return 0;
}
