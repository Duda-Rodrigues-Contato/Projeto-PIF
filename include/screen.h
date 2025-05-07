#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <stdio.h>

#define MAXX 80
#define MAXY 24
#define MINX 1
#define MINY 1

typedef enum {

    BLACK,
    WHITE, 
    RED, 
    GREEN, 
    BROWN, 
    BLUE, 
    MAGENTA, 
    CYAN, 
    LIGHTGRAY,
    DARKGRAY, 
    LIGHTRED, 
    LIGHTGREEN, 
    YELLOW, 
    LIGHTBLUE, 
    LIGHTMAGENTA, 
    LIGHTCYAN, 

} screenColor;

void screenInit();
void screenUpdate();
void screenDestroy();
void screenGotoxy(int x, int y);
void screenSetColor(screenColor fg, screenColor bg);


void desenhaBorda() {

    screenInit(1);

}


void corPalavras() {

    screenSetColor(WHITE, BLUE);

}

void screenColorBackgroung() {

    screenSetColor(BLACK, WHITE);
}


void corInimigos() {

    screenSetColor(RED, BLUE);
}

void desenhoInimigo(int x, int y) {

    printf("😈");
    corInimigos();
    screenGotoxy(x, y);

}


#endif