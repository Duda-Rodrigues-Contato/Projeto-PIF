#include "../include/game.h"
#include "../cli-lib/cli.h"
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main() {
    cli_init();
    srand(time(NULL));

    iniciar_jogo();

    while (1) {
        atualizar_jogo();
        desenhar_jogo();
        usleep(200000); 
    }

    cli_close();
    return 0;
}
