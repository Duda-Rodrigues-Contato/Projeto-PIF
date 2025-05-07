#ifndef __SCREEN_H__
#define __SCREEN_H__

#include <stdio.h>

#define BOX_VLINE 0x78
#define BOX_HLINE 0x71

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
void telaInicial();

/*void desenhaBorda() {

    screenInit(1);

}*/

// Cor das palavras:
/*void corPalavras() {

    screenSetColor(WHITE, BLUE);

}*/


// Cor dos inimigos:
/*void corInimigos() {

    screenSetColor(RED, BLUE);
}*/


// Desenha os inimigos - Add funçção na função de tela do jogo:
/*void desenhoInimigo(int x, int y) {

    printf("😈");
    corInimigos();
    screenGotoxy(x, y);

}*/

#endif