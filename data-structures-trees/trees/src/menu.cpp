#include "menu.h"
using namespace std;


int currentGlobal = 0;
string itemsGlobal[] = {
    "Работа с бинарным деревом (тест)",
    "Работа с BST деревом",
    "Работа с AVL деревом",
    "Работа с Red-Black деревом",
    "Смотреть логи",
    "Очистить логи",
    "Выход"
};


void Logis::addLog(string category, string name, double duration)
{
    logs.emplace_back(category, name, duration);
}

void Logis::delLog() 
{
    logs.clear();
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

void drawWindow(int x, int y, int width, int height, const char* title) {
    set_cords(x, y);
    cout << "+";
    for (int i = 0; i < width - 2; i++) cout << "-";
    cout << "+";

    if (title != nullptr) {
        set_cords(x + 2, y);
        cout << title;
    }

    for (int i = 1; i < height - 1; i++) {
        set_cords(x, y + i);
        cout << "|";
        set_cords(x + width - 1, y + i);
        cout << "|";
    }

    set_cords(x, y + height - 1);
    cout << "+";
    for (int i = 0; i < width - 2; i++) cout << "-";
    cout << "+";
}

void displayStatsTable(Logis& logger,
    int startX,
    int startY,
    int width,
    int height) {

    const auto& logs = logger.getLogs();

    if (logs.empty()) {
        set_cords(startX + 2, startY + 2);
        cout << "Нет данных";
        return;
    }

    struct TreeStats {
        string operation;

        double bstTotal = 0;
        double avlTotal = 0;
        double rbTotal = 0;

        int bstCount = 0;
        int avlCount = 0;
        int rbCount = 0;
    };

    map<string, TreeStats> statsMap;

    // ==================== СБОР СТАТИСТИКИ ====================

    for (const auto& log : logs) {

        if (statsMap.find(log.name) == statsMap.end()) {

            TreeStats stat;
            stat.operation = log.name;

            statsMap[log.name] = stat;
        }

        auto& stat = statsMap[log.name];

        if (log.category == "BST") {
            stat.bstTotal += log.duration;
            stat.bstCount++;
        }
        else if (log.category == "AVL") {
            stat.avlTotal += log.duration;
            stat.avlCount++;
        }
        else if (
            log.category == "RB" ||
            log.category == "RedBlack" ||
            log.category == "Red-Black"
            ) {

            stat.rbTotal += log.duration;
            stat.rbCount++;
        }
    }

    // ==================== ТАБЛИЦА ====================

    int currentY = startY + 1;

    set_cords(startX + 2, currentY);
    cout << "Operation";

    set_cords(startX + 28, currentY);
    cout << "BST";

    set_cords(startX + 48, currentY);
    cout << "AVL";

    set_cords(startX + 68, currentY);
    cout << "RB";

    currentY++;

    set_cords(startX + 1, currentY);

    for (int i = 0; i < width - 2; i++)
        cout << "-";

    currentY++;

    // ==================== ВЫВОД ====================

    for (auto& pair : statsMap) {

        auto& stat = pair.second;

        set_cords(startX + 2, currentY);

        string op = stat.operation;

        if (op.length() > 20)
            op = op.substr(0, 17) + "...";

        cout << op;

        // BST
        set_cords(startX + 28, currentY);

        if (stat.bstCount > 0) {

            double avg =
                stat.bstTotal / stat.bstCount;

            printf("%.1f ms", avg);
        }
        else {
            cout << "---";
        }

        // AVL
        set_cords(startX + 48, currentY);

        if (stat.avlCount > 0) {

            double avg =
                stat.avlTotal / stat.avlCount;

            printf("%.1f ms", avg);
        }
        else {
            cout << "---";
        }

        // RED BLACK
        set_cords(startX + 68, currentY);

        if (stat.rbCount > 0) {

            double avg =
                stat.rbTotal / stat.rbCount;

            printf("%.1f ms", avg);
        }
        else {
            cout << "---";
        }

        currentY++;

        if (currentY >= startY + height - 2)
            break;
    }
}

void displayDetailedLogs(Logis& logger,
    int startX,
    int startY,
    int width,
    int height) {

    const auto& logs = logger.getLogs();

    if (logs.empty()) {
        set_cords(startX + 2, startY + 2);
        cout << "Нет данных";
        return;
    }

    int currentY = startY + 1;

    // Заголовки
    set_cords(startX + 2, currentY);
    cout << "Операция";

    set_cords(startX + 30, currentY);
    cout << "Категория";

    set_cords(startX + 50, currentY);
    cout << "Время (us)";

    currentY++;

    set_cords(startX + 1, currentY);

    for (int i = 0; i < width - 2; i++)
        cout << "-";

    currentY++;

    // Логи
    for (const auto& log : logs) {

        set_cords(startX + 2, currentY);

        string name = log.name;

        if (name.length() > 24)
            name = name.substr(0, 21) + "...";

        cout << name;

        set_cords(startX + 30, currentY);
        cout << log.category;

        set_cords(startX + 50, currentY);
        cout << log.duration;

        currentY++;

        if (currentY >= startY + height - 2)
            break;
    }
}

void showSplitScreen(Logis& logger) {

    system("cls");

    CONSOLE_SCREEN_BUFFER_INFO csbi;

    GetConsoleScreenBufferInfo(
        GetStdHandle(STD_OUTPUT_HANDLE),
        &csbi
    );

    int screenWidth =
        csbi.srWindow.Right - csbi.srWindow.Left + 1;

    int screenHeight =
        csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

    int leftWidth = screenWidth / 2;
    int rightWidth = screenWidth - leftWidth - 1;

    int windowHeight = screenHeight - 2;

    // Левая часть
    drawWindow(
        0,
        0,
        leftWidth,
        windowHeight,
        " СРАВНЕНИЕ BST vs AVL vs Red-Black "
    );

    displayStatsTable(
        logger,
        0,
        0,
        leftWidth,
        windowHeight
    );

    // Правая часть
    drawWindow(
        leftWidth + 1,
        0,
        rightWidth,
        windowHeight,
        " ДЕТАЛЬНЫЕ ЛОГИ "
    );

    displayDetailedLogs(
        logger,
        leftWidth + 1,
        0,
        rightWidth,
        windowHeight
    );

    // Нижняя строка
    const auto& logs = logger.getLogs();

    int bstCount = 0;
    int avlCount = 0;
    int rbCount = 0;

    double bstTotal = 0;
    double avlTotal = 0;
    double rbTotal = 0;

    for (const auto& log : logs) {

        if (log.category == "BST") {
            bstCount++;
            bstTotal += log.duration;
        }
        else if (log.category == "AVL") {
            avlCount++;
            avlTotal += log.duration;
        }
        else if (
            log.category == "RB" ||
            log.category == "RedBlack" ||
            log.category == "Red-Black"
            ) {

            rbCount++;
            rbTotal += log.duration;
        }
    }

    set_cords(0, screenHeight - 1);

    cout << "Всего операций: " << logs.size();
    cout << " | BST: " << bstCount;
    if (bstCount > 0) {
        cout << " avg " << bstTotal / bstCount << " ms";
    }
    cout << " | AVL: " << avlCount;
    if (avlCount > 0) {
        cout << " avg " << avlTotal / avlCount << " ms";
    }
    cout << " | RB: " << rbCount;
    if (rbCount > 0) {
        cout << " avg " << rbTotal / rbCount << " ms";
    }
    cout
        << " | Нажмите любую клавишу...";
}