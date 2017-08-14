#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

struct termios orig_termios;

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

/*
** This function is disabling automatic ECHO. So you can't see what you type.
** c_lflag = local flag which is dumping ground for other states
** 
*/
void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);

    struct termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO | ICANON); // ICANON makes input byte by byte

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main() {
    enableRawMode();
    char c;
    while ( read(STDIN_FILENO, &c, 1) == 1 && c != 'q' );
    return 0;
}
