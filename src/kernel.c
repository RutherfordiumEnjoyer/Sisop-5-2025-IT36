#include "shell.h"
#include "kernel.h"

int main() {
    clearScreen(0x07);
    shell();
}

void printString(char *str) {
    int i = 0;
    while (str[i] != '\0') {
        interrupt(0x10, 0x0E00 | str[i], 0, 0, 0);
        i++;
    }
}

void readString(char *buf) {
    int i = 0;
    char ch;
    while (1) {
        ch = interrupt(0x16, 0, 0, 0, 0) & 0xFF;
        if (ch == 0x0D) { // Enter key
            buf[i] = '\0';
            printString("\r\n");
            return;
        } else if (ch == 0x08) { // Backspace
            if (i > 0) {
                i--;
                printString("\b \b");
            }
        } else {
            buf[i] = ch;
            interrupt(0x10, 0x0E00 | ch, 0, 0, 0);
            i++;
        }
    }
}

void clearScreen(int color) {
    int i = 0;
    for (i = 0; i < 80 * 25 * 2; i += 2) {
        putInMemory(0xB800, i, ' ');
        putInMemory(0xB800, i + 1, color);
    }
    interrupt(0x10, 0x0200, 0, 0, 0); // Set cursor to (0,0)
}
