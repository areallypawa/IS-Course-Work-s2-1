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

