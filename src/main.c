#include <string.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

int main() {

    screenInit(1);
    telaInicial();
    screenUpdate();

    screenDestroy();

    return 0;
}
