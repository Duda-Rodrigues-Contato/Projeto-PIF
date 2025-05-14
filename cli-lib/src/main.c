#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
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
<<<<<<< HEAD
    if (game_config.tempoContrario >= TOTAL_TIME) {
        printf("TIME'S UP! Final Score: %d", game_config.score);
    } else {
        printf("GAME OVER! Final Score: %d", game_config.score);
=======
    if (game_state.time_elapsed >= TOTAL_TIME) {
        printf("O TEMPO ACABOU! Final Score: %d", game_state.score);
    } else {
        printf("FIM DE JOGO! Final Score: %d", game_state.score);
>>>>>>> 75deac6fcbccb3806da954f779af84ac47106a40
    }
    screenUpdate();

    timerInit(3000);
    while (!timerTimeOver());

    PlayerScore jogador;
    strcpy(jogador.username, username);
<<<<<<< HEAD
    jogador.score = game_config.score;  // << CORREÇÃO AQUI
=======
    jogador.score = game_state.score;  
>>>>>>> 75deac6fcbccb3806da954f779af84ac47106a40

    salvarPontuacao(jogador);
    exibirRanking();

    return 0;
}
