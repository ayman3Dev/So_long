#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

int playerX = 10;
int playerY = 10;

void clearScreen() {
    printf("\033[H\033[J");  // ANSI escape code to clear the screen
}

void gotoxy(int x, int y) {
    printf("\033[%d;%dH", y, x);  // ANSI escape code to move the cursor to (x, y)
}

void drawPlayer() {
    gotoxy(playerX, playerY);
    printf("P");
}

void handleInput() {
    struct termios oldt, newt;
    int ch;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);

    clearScreen();

    switch (ch) {
        case 27:  // ESC key
            exit(0);
            break;
        case 'a':
            playerX--;
            break;
        case 'd':
            playerX++;
            break;
        case 'w':
            playerY--;
            break;
        case 's':
            playerY++;
            break;
    }

    drawPlayer();
}

int main() {
    while (1) {
        handleInput();
    }

    return 0;
}
