#include "shell.h"
#include "kernel.h"
#include "std_lib.h"

char user[64];
char host[64];
int currentTextColor;

void executeCommand(char *cmd, char arg[2][64], char *original_buf);
void prompt(char* name);
void randomAnswer();


void shell() {
    char buf[128];
    char cmd[64];
    char arg[2][64];

    strcpy(user, "user");
    host[0] = '\0';
    currentTextColor = 0x07;

    printString("Welcome to EorzeOS!\r\n");

    while (true) {
        prompt(user);
        readString(buf);
        parseCommand(buf, cmd, arg);
        executeCommand(cmd, arg, buf);
    }
}

void prompt(char* name) {
    printString(name);
    if (host[0] != '\0') {
        printString(host);
    }
    printString("> ");
}

void parseCommand(char *buf, char *cmd, char arg[2][64]) {
    int i = 0, j = 0, k = 0;
    int arg_idx = 0;

    clear(cmd, 64);
    clear(arg[0], 64);
    clear(arg[1], 64);

    while (buf[i] == ' ' || buf[i] == '\r' || buf[i] == '\n') i++;
    
    while (buf[i] != ' ' && buf[i] != '\r' && buf[i] != '\n' && buf[i] != '\0') {
        cmd[j++] = buf[i++];
    }
    cmd[j] = '\0';

    for (arg_idx = 0; arg_idx < 2; arg_idx++) {
        while (buf[i] == ' ') i++;
        k = 0;
        while (buf[i] != ' ' && buf[i] != '\r' && buf[i] != '\n' && buf[i] != '\0') {
            arg[arg_idx][k++] = buf[i++];
        }
        arg[arg_idx][k] = '\0';
    }
}

void randomAnswer() {
    int r = mod(getBiosTick(), 3);
    if (r == 0) {
        printString("yo\r\n");
    } else if (r == 1) {
        printString("ts unami gng </3\r\n");
    } else {
        printString("sygau\r\n");
    }
}

void executeCommand(char *cmd, char arg[2][64], char *original_buf) {
    int num1, num2, result;
    char result_str[32];

    if (strcmp(cmd, "yo")) {
        printString("gurt\r\n");
    } else if (strcmp(cmd, "gurt")) {
        printString("yo\r\n");
    } else if (strcmp(cmd, "user")) {
        if (arg[0][0] == '\0') {
            strcpy(user, "user");
        } else {
            strcpy(user, arg[0]);
        }
        printString("Username changed to ");
        printString(user);
        printString("\r\n");
    } else if (strcmp(cmd, "grandcompany")) {
        if (strcmp(arg[0], "maelstrom")) {
            currentTextColor = 0x0C; // Merah
            clearScreen(currentTextColor);
            strcpy(host, "@Storm");
        } else if (strcmp(arg[0], "twinadder")) {
            currentTextColor = 0x0E; // Kuning
            clearScreen(currentTextColor);
            strcpy(host, "@Serpent");
        } else if (strcmp(arg[0], "immortalflames")) {
            currentTextColor = 0x09; // Biru
            clearScreen(currentTextColor);
            strcpy(host, "@Flame");
        } else {
            printString("Unknown Grand Company.\r\n");
        }
    } else if (strcmp(cmd, "clear")) {
        host[0] = '\0';
        currentTextColor = 0x07; // Putih
        clearScreen(currentTextColor);
    } else if (strcmp(cmd, "add")) {
        atoi(arg[0], &num1);
        atoi(arg[1], &num2);
        result = num1 + num2;
        itoa(result, result_str);
        printString(result_str);
        printString("\r\n");
    } else if (strcmp(cmd, "sub")) {
        atoi(arg[0], &num1);
        atoi(arg[1], &num2);
        result = num1 - num2;
        itoa(result, result_str);
        printString(result_str);
        printString("\r\n");
    } else if (strcmp(cmd, "mul")) {
        atoi(arg[0], &num1);
        atoi(arg[1], &num2);
        result = num1 * num2;
        itoa(result, result_str);
        printString(result_str);
        printString("\r\n");
    } else if (strcmp(cmd, "div")) {
        atoi(arg[0], &num1);
        atoi(arg[1], &num2);
        if (num2 == 0) {
            printString("Error: Division by zero.\r\n");
        } else {
            result = div(num1, num2);
            itoa(result, result_str);
            printString(result_str);
            printString("\r\n");
        }
    } else if (strcmp(cmd, "yogurt")) {
        printString("gurt> ");
        randomAnswer();
    } else if (cmd[0] != '\0') {
        printString(original_buf);
        printString("\r\n");
    }
}
