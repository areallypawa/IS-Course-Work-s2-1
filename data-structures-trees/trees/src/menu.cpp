#include <iostream>
#include "menu.h"
using namespace std;

int logCount = 0;
FuncLog* logs = nullptr;

void addLog(string category, string name, double duration) {
    FuncLog* newLogs = new FuncLog[logCount + 1];

    for (int i = 0; i < logCount; i++) {
        newLogs[i] = logs[i];
    }

    newLogs[logCount].name = name;
    newLogs[logCount].duration_ms = duration;
    newLogs[logCount].category = category;
    delete[] logs;
    logs = newLogs;
    logCount++;
}

void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void clearInput() {
    cin.clear();
    cin.ignore(10000000, '\n');
}

void pause() {
    cout << '\n';
    system("Pause");
}

void hideCursor() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hConsole, &cursorInfo);
}

void set_cords(int x, int y) {
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hStdout, pos);
}

