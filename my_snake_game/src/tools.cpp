#include "tools.h"
#include <windows.h>
#include <stdio.h>

// Set the window size
void SetWindowSize(int cols, int lines) {
    system("title Snake");
    char cmd[30];
    sprintf_s(cmd, "mode con cols=%d lines=%d", cols * 2, lines);
    system(cmd);
}

// Set the cursor position
void SetCursorPosition(const int x, const int y) {
    COORD position;
    position.X = x * 2;
    position.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

// Set the text color
void SetColor(int colorID) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colorID);
}

// Set the background color of the text
void SetBackColor() {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),
        FOREGROUND_BLUE |
        BACKGROUND_BLUE |
        BACKGROUND_GREEN |
        BACKGROUND_RED);
}