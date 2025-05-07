#include "screen.h"

void screenDrawInimigos() {

    desenhoInimigo(MAXX * 0.5, MAXY * 0.5);
    screenGotoxy(MINX, MINY);

    for (int i = MINX - 1; i < MAXX; i++) {

        desenhoInimigo(i, MINY);

    }

    screenGotoxy(MAXX, MINY);

}


void screenInit() {

    screenClear();
    screenColorBackgroung();
    desenhaBorda();
    desenhoInimigo(MAXX * 0.5, MINY);
    screenDrawInimigos();

}
