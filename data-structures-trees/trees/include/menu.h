#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <chrono>
#include <string>
#include <vector>
#include <map>

#define MEASURE(cat, name, expr) \
    do { log.measureTime(cat, name, [&]() { expr; }); } while(0)

#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define RED "\033[31m"
#define RESET   "\033[0m"

extern int currentGlobal;

constexpr int countItems = 6;
constexpr int coutChooseItems = 3;

extern std::string itemsGlobal[];
extern std::string items[];
extern std::string ChooseItems[];
constexpr int countGlobal = 7;

struct trunk
{
    trunk* prev;
    std::string str;

    trunk(trunk* prev, std::string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

class Logis {
private:
    struct FuncLog {
        std::string category;
        std::string name;
        double duration;

        FuncLog(std::string c, std::string n, double d)
            : category(c), name(n), duration(d) {
        }
    };

    std::vector<FuncLog> logs;

public:
    void addLog(std::string category, std::string name, double duration);
    void delLog();

    template<typename Func>
    auto measureTime(std::string category, std::string name, Func f) {
        auto start = std::chrono::high_resolution_clock::now();

        if constexpr (std::is_void_v<decltype(f())>) {
            f();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration<double, std::micro>(end - start);
            addLog(category, name, duration.count());
        }
        else {
            auto result = f();
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration<double, std::micro>(end - start);
            addLog(category, name, duration.count());
            return result;
        }
    }

    const std::vector<FuncLog>& getLogs() const {
        return logs;
    }
};

struct CompareStats {
    std::string operation;

    double listTotal = 0;
    double arrayTotal = 0;

    int listCount = 0;
    int arrayCount = 0;
};

void clear();
void clearInput();
void cin_ignore();
void pause();

void hideCursor();
void set_cords(int x, int y);
void show_menu(int current, int size_items, const std::string items[], const std::string str);
void displayStatsTable(Logis& logger,
    int startX,
    int startY,
    int width,
    int height);

void displayDetailedLogs(Logis& logger,
    int startX,
    int startY,
    int width,
    int height);

void showSplitScreen(Logis& logger);