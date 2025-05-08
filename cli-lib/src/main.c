#include <stdio.h>
#include <signal.h>
#include "keyboard.h"
#include "screen.h"
#include "timer.h"
#include "logica.h" // Já inclui todas as definições necessárias

// Declarações externas (definidas em game_logic.c)
extern GameState game_state;
extern FallingWord words[];
extern char input_buffer[];
extern int buffer_index;
extern int last_y_position[];

int main() {
    // Configura tratamento de Ctrl+C
    signal(SIGINT, handle_sigint);
    atexit(restore_terminal);
    
    // Inicializa o jogo
    init_game();

    // Loop principal
    while(game_state.lives > 0 && game_state.current_word < WORD_COUNT) {
        if(keyhit()) {
            handle_input(readch());
        }
        update_game();
        draw_game();
    }

    // Tela de Game Over
    screenClear();
    screenGotoxy(35, 12);
    printf("Game Over! Score: %d", game_state.score);
    screenUpdate();
    timerInit(2000);
    while(!timerTimeOver());

    return 0;
}