#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <windows.h>
#include <chrono>
#include <string>
#include <vector>
#include <map>


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

struct CategoryStats {
    double total;
    int count;

    CategoryStats() { total = 0; count = 0; };
};

void clear();
void clearInput();
void cin_ignore();
void pause();

void hideCursor();
void set_cords(int x, int y);
void show_menu(int current, int size_items, const std::string items[], const std::string str);