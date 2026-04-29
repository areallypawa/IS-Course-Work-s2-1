#include <iostream>

#include "menu.h"
#include "binary_tree.h"
#include "bst.h"
#include "avl.h"
#include "red_black.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    /*
		Сдесь нет реализации меню, так как это просто пример работы с бинарным деревом.
		Вы можете реализовать меню, используя функции из класса Menu, который находится в файле menu.h.
        По факту тут листья располагаются в виде:
                10
               /  \
              5    20
             / \     \
            3   7     30
                 \
				  6

		и они никак не сортируются, так как это просто бинарное дерево, а не бинарное дерево поиска (BST).
		Поэтому реализации пунктов со степика не будет, так как они относятся к BST, а не к обычному бинарному дереву.

    */

	BinaryTree tree;

    tree.setRoot(10);
    auto root = tree.getRoot();

    tree.addLeft(root, 5);
    tree.addRight(root, 20);

    tree.addLeft(root->left, 3);
    tree.addRight(root->left, 7);

    tree.addRight(root->right, 30);

    tree.addLeft(root->left->right, 6);
    std::cout << "Обычный вывод:\n";
    tree.print();

    std::cout << "\n\nКрасивый вывод:\n";
    tree.printPretty();

	return 0;

}

