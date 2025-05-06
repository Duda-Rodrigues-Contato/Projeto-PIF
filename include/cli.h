#ifndef CLI_H
#define CLI_H

void cli_init();
void cli_clear();
void cli_reset();
void cli_gotoxy(int x, int y);
void cli_printf(const char *fmt, ...);
char cli_getkey();
void cli_flush();

#endif
