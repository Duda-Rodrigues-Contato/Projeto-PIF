#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include "keyboard.h"
#include "screen.h"
#include "timer.h"
#include "logica.h"

int main() {
    signal(SIGINT, handle_sigint);
    atexit(restore_terminal);
    
    init_game();

    while(game_state.lives > 0 && game_state.time_elapsed < TOTAL_TIME) {
        if(keyhit()) {
            handle_input(readch());
        }
        update_game();
        draw_game();
    }

    screenClear();
    screenGotoxy(35, 12);
    if(game_state.time_elapsed >= TOTAL_TIME) {
        printf("TIME'S UP! Final Score: %d", game_state.score);
    } else {
        printf("GAME OVER! Final Score: %d", game_state.score);
    }
    screenUpdate();
    timerInit(3000);
    while(!timerTimeOver());

    return 0;
}