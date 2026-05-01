#include <iostream>
#include <windows.h>
#include <chrono>
#include <string>



struct FuncLog {
    std::string category;
    std::string name;
    double duration_ms;
};

struct CategoryStats {
    char category[20];
    long long listTotalTime;
    long long arrayTotalTime;
    int listCount;
    int arrayCount;
};

extern FuncLog* logs;
extern int logCount;

void addLog(std::string category, std::string name, double duration);

template<typename Func>
auto measureTime(std::string category, std::string name, Func f) {
    auto start = chrono::high_resolution_clock::now();
    auto result = f();
    auto end = chrono::high_resolution_clock::now();

    chrono::duration<double, micro> duration = end - start;
    addLog(category, name, duration.count());

    return result;
}


void clear();
void clearInput();
void cin_ignore();
void pause();

void hideCursor();
void set_cords(int x, int y);