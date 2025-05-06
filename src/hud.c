#include "hud.h"
#include "cli.h"
#include <stdio.h>

void renderizar_hud(Jogo jogo) {
    cli_gotoxy(40, 2);
    cli_printf("Ataque: [");
    int barras = jogo->progresso / 10;
    for (int i = 0; i < 10; i++) {
        if (i < barras)
            cli_printf("=");
        else
            cli_printf(" ");
    }
    cli_printf("] %d%%", jogo->progresso);

    cli_gotoxy(40, 4);
    cli_printf("Vidas: ");
    for (int i = 0; i < jogo->vidas; i++) {
        cli_printf("❤️");
    }
}