#include <iostream>
#include <string>
#include "bst.h"

/* 
    SERVICE CODE 
*/

int currentItems = 0;
int currentChoose = 0;


std::string items[] =
{
    "Создать дерево",
    "Вывести дерево",
    "Сравнение скорости -> вставки / удаления / получения", 
    "Обход дерева",
    "Очистить логи",
    "Выход"
};

int countItems = sizeof(items) / sizeof(std::string);

std::string ChooseItems[] =
{
    "Создать дерево",
    "Вывести дерево",
    "Сравнение скорости -> вставки / удаления / получения",
    "Обход дерева",
    "Очистить логи",
    "Выход"
};


/*
    SERVICE CODE
*/

BST::Node::Node(int value) : value(value), left(nullptr), right(nullptr) {
}

BST::BST() {
    root = nullptr;
}

void BST::deleteTree(Node* node) {
    if (!node) return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

BST::~BST() {
    deleteTree(root);
}

void BST::setRoot(int value) {
    root = new Node(value);
}

BST::Node* BST::getRoot() {
    return root;
}

void BST::addLeft(Node* parent, int value) {
    if (parent)
        parent->left = new Node(value);
}

void BST::addRight(Node* parent, int value) {
    if (parent)
        parent->right = new Node(value);
}

void BST::print(Node* node) {
    if (!node) return;

    std::cout << node->value << " ";
    print(node->left);
    print(node->right);
}

void BST::print() {
    print(root);
}

void BST::printPretty(Node* node, int depth, bool isLeft) {
    if (!node) return;
    printPretty(node->right, depth + 1, false);
    for (int i = 0; i < depth; i++)
        std::cout << "    ";

    if (depth == 0) {
        std::cout << "--> ";
    }
    else if (isLeft) {
        std::cout << "`--> ";
    }
    else {
        std::cout << ".--> ";
    }
    std::cout << node->value << std::endl;
    printPretty(node->left, depth + 1, true);
}

void BST::printPretty() {
    printPretty(root, 0, false);
}

void BST::insert(int value) {
    if (!root) {
        root = new Node(value);
        return;
    }

    Node* current = root;
    while (true) {
        if (value < current->value) {
            if (!current->left) {
                current->left = new Node(value);
                return;
            }
            current = current->left;
        }
        else {
            if (!current->right) {
                current->right = new Node(value);
                return;
            }
            current = current->right;
        }
    }
}

bool BST::search(int value) {
    Node* current = root;

    while (current) {
        if (value == current->value)
            return true;
        else if (value < current->value)
            current = current->left;
        else
            current = current->right;
    }

    return false;
}

/*
    1. Формирование бинарного дерева из N элементов
    a. N rand элементов  
    b. N user элементов
    c. N file элементов
*/

void createTree() {
    BST tree;

    //do {


    //} while (current != countItems - 1);



    std::cout << "Введите числа:\n";
    int x;
    while (true) {
        std::cin >> x;
        if (x == 0) break;
        tree.insert(x);
    }

    std::cout << "\nДерево:\n";
    tree.printPretty();

    std::cout << "\nПоиск чисел (0 — выход):\n";

    while (true) {
        std::cin >> x;
        if (x == 0) break;

        if (tree.search(x))
            std::cout << "Найдено\n";
        else
            std::cout << "Не найдено\n";
    }
}

