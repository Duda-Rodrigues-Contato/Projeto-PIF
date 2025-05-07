#include <stdio.h>
#include "screen.h"

void screenUpdate() {

    fflush(stdout);

}


void screenDestroy() {

    printf("\033[0m\033[?25h"); // Reset

}


void screenGotoxy(int x, int y) {

    printf("\033[%d;%dH", x, y);

}


void screenSetColor(screenColor fg, screenColor bg) {

    printf("\033[3%d;4%dm", fg, bg);

}


// Desenha escolha de nível:
void escolhaNivel() {

    printf("Digite seu nível: ");
    screenGotoxy(MAXX * 0.5, MINY * 0.5);
    screenUpdate();

}


// Desenha tela inicial:
void telaInicial() {

    screenInit();
    screenSetColor(BLACK, WHITE);
    escolhaNivel();

    screenUpdate();

}


void screenInit() {

    telaInicial();
    screenGotoxy(MINX, MINY);
    printf("\033[2J\033[H]]"); // Limpa a tela

}
/*void screenDrawInimigos() {

    desenhoInimigo(MAXX * 0.5, MAXY * 0.5);
    screenGotoxy(MINX, MINY);

    for (int i = MINX - 1; i < MAXX; i++) {

        desenhoInimigo(i, MINY);

    }

    screenGotoxy(MAXX, MINY);

}*/