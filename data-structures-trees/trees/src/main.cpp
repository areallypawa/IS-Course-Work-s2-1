#include <iostream>

#include "menu.h"
#include "binary_tree.h"
#include "bst.h"
#include "avl.h"
#include "red_black.h"

int main()
{
	setlocale(LC_ALL, "Russian");
	BinaryTree tree;
    // корень
    tree.setRoot(10);
    auto root = tree.getRoot();

    // уровень 1
    tree.addLeft(root, 5);
    tree.addRight(root, 20);

    // уровень 2
    tree.addLeft(root->left, 3);
    tree.addRight(root->left, 7);

    tree.addRight(root->right, 30);

    // уровень 3
    tree.addLeft(root->left->right, 6);

    // обычный вывод
    std::cout << "Обычный вывод:\n";
    tree.print();

    std::cout << "\n\nКрасивый вывод:\n";
    tree.animateBuild();

	return 0;

}

