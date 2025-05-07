#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int main() {

    screenInit(1);
    screenInit();
    keyboardInit();
    
    while(1) {

        screenDrawInimigos();
        screenUpdate();

    }

    return 0;
}
