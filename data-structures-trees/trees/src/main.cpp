#include <iostream>

#include "menu.h"
#include "binary_tree.h"
#include "bst.h"
#include "avl.h"
#include "red_black.h"

using namespace std;

int main()
{
    setlocale(0, "ru");
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
            createTree(log);
            clear();
            break;
        }
        case 2:
        {
            break;
        }
        case 3:
        {
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
            break;
        }
        }

    } while (currentGlobal != countGlobal - 1);
	
    return 0;

}

