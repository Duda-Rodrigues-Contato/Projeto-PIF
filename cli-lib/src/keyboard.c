/**
 * keyboard.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include <termios.h>
#include <unistd.h>

#include "keyboard.h"

static struct termios consiguracaoInicial, novasConfigs;
static int pegarCaracter;


void keyboardInit()
{
    tcgetattr(0,&consiguracaoInicial);
    novasConfigs = consiguracaoInicial;
    novasConfigs.c_lflag &= ~ICANON;
    novasConfigs.c_lflag &= ~ECHO;
    novasConfigs.c_lflag &= ~ISIG;
    novasConfigs.c_cc[VMIN] = 1;
    novasConfigs.c_cc[VTIME] = 0;
    tcsetattr(0, TCSANOW, &novasConfigs);
}

void keyboardDestroy()
{
    tcsetattr(0, TCSANOW, &consiguracaoInicial);
}

int keyhit()
{
    unsigned char ch;
    int nread;

    if (pegarCaracter != -1) return 1;
    
    novasConfigs.c_cc[VMIN]=0;
    tcsetattr(0, TCSANOW, &novasConfigs);
    nread = read(0,&ch,1);
    novasConfigs.c_cc[VMIN]=1;
    tcsetattr(0, TCSANOW, &novasConfigs);
    
    if(nread == 1) 
    {
        pegarCaracter = ch;
        return 1;
    }
    
    return 0;
}

int readch()
{
    char ch;

    if(pegarCaracter != -1)
    {
        ch = pegarCaracter;
        pegarCaracter = -1;
        return ch;
    }
    read(0,&ch,1);
    return ch;
}
