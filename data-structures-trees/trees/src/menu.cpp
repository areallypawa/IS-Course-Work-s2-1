#include <iostream>
#include "menu.h"
using namespace std;

Logis::FuncLog::FuncLog(std::string category, std::string name, double duration_ms) : category(category), name(name), duration_ms(duration_ms) {
}

Logis::CategoryStats::CategoryStats(char category[20], long long listTotalTime, long long arrayTotalTime, long long BSTTotalTime, long long AVLTotalTime, long long RBTotalTime, int listCount, int arrayCount, int BSTCount, int AVLCount, int RBCount)
{
    category = category;
    listTotalTime = listTotalTime;
    arrayTotalTime = arrayTotalTime;
    listCount = listCount;
    arrayCount = arrayCount;
    BSTTotalTime = BSTTotalTime;
    AVLTotalTime = AVLTotalTime;
    RBTotalTime = RBTotalTime;
    BSTCount = BSTCount;
    AVLCount = AVLCount;
    RBCount = RBCount;

}
void Logis::addLog(string category, string name, double duration) {
    if (!logs) setLog();

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

void Logis::setLog() {
    logs = nullptr;
    logCount = 0;
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

