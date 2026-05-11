#include <iostream>

#include "menu.h"
#include "binary_tree.h"
#include "bst.h"
#include "avl.h"
#include "red_black.h"

using namespace std;

int main()
{
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    Logis log;
    do {
        while (true) {
            show_menu(currentGlobal, countGlobal, itemsGlobal, "МЕНЮ");
            int key = _getch();

            if (key == 72 && currentGlobal > 0) currentGlobal--;
            if (key == 80 && currentGlobal < countGlobal - 1) currentGlobal++;
            if (key == 13) break;
        }
        switch (currentGlobal) {
        case 0:
        {
            clear();
            BinaryTree tree(1);
            pause();
            clear();
            break;
        }
        case 1:
        {   
            clear();
            createTreeBst(log);
            clear();
            break;
        }
        case 2:
        {
            clear();
            createTreeAvl(log);
            clear();
            break;
        }
        case 3:
        {
			//Red-Black
            break;
        }
        case 4:
        {
            clear();
            showSplitScreen(log);
            _getch();
            clear();
            break;
        }
        case 5:
        {
            clear();
            log.delLog();
            cout << GREEN << "Логи очищенны" << RESET;
            pause();
            clear();
            break;
        }
        case 6:
        {
			//Exit
            break;
        }
        }

    } while (currentGlobal != countGlobal - 1);
    log.delLog();
    return 0;

}

