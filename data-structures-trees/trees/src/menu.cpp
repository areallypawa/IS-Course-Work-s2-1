#include "menu.h"
using namespace std;

void Logis::addLog(std::string category, std::string name, double duration)
{
    logs.emplace_back(category, name, duration);
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

void showStats(const Logis& logis) {
    auto& logs = logis.getLogs();

    std::map<std::string, std::map<std::string, CategoryStats>> stats;

    for (const auto& log : logs) {
        stats[log.name][log.category].total += log.duration;
        stats[log.name][log.category].count++;
    }

    for (const auto& [operation, categories] : stats) {
        std::cout << "\nОперация: " << operation << "\n";

        for (const auto& [category, stat] : categories) {
            double avg = stat.total / stat.count;
            std::cout << "  " << category
                << " | avg: " << avg
                << " | count: " << stat.count << "\n";
        }
    }
}