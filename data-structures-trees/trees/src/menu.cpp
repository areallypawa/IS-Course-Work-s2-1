#include <iostream>
#include "menu.h"
using namespace std;

Logis::FuncLog::FuncLog(std::string category, std::string name, double duration_ms)
    : category(category), name(name), duration_ms(duration_ms) {
}

Logis::CategoryStats::CategoryStats(const char* cat)
{
    std::strncpy(category, cat, 19);
    category[19] = '\0';

    listTotalTime = 0;
    arrayTotalTime = 0;
    BSTTotalTime = 0;
    AVLTotalTime = 0;
    RBTotalTime = 0;

    listCount = 0;
    arrayCount = 0;
    BSTCount = 0;
    AVLCount = 0;
    RBCount = 0;
}

void Logis::addLog(std::string category, std::string name, double duration)
{
    FuncLog* newLogs = new FuncLog[logCount + 1];

    for (int i = 0; i < logCount; i++) {
        newLogs[i] = logs[i];
    }

    newLogs[logCount] = FuncLog(category, name, duration);

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

void show_menu(int current, int size_items, const string items[], const string str) {
    hideCursor();
    
    set_cords(0, 0);
    cout << "=============== " << str << " ===============\n";
    for (int i = 0; i < size_items; i++) {
        if (i == current)
            cout << " -> " << items[i] << "\n";
        else
            cout << "    " << items[i] << "\n";
    }
}