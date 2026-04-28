#include <iostream>
#include <string>
#include "binary_tree.h"

#include <windows.h>
#include <thread>
#include <chrono>
#include "menu.h"

BinaryTree::Node::Node(int value) : value(value), left(nullptr), right(nullptr) {
}

BinaryTree::BinaryTree() {
    root = nullptr;
}

void BinaryTree::deleteTree(Node* node) {
    if (!node) return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

BinaryTree::~BinaryTree() {
    deleteTree(root);
}

void BinaryTree::setRoot(int value) {
    root = new Node(value);
}

BinaryTree::Node* BinaryTree::getRoot() {
    return root;
}

void BinaryTree::addLeft(Node* parent, int value) {
    if (parent)
        parent->left = new Node(value);
}

void BinaryTree::addRight(Node* parent, int value) {
    if (parent)
        parent->right = new Node(value);
}

void BinaryTree::print(Node* node) {
    if (!node) return;

    std::cout << node->value << " ";
    print(node->left);
    print(node->right);
}

void BinaryTree::print() {
    print(root);
}

void wait(int ms) {
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

void BinaryTree::draw(BinaryTree::Node* node) {
    if (!node) return;

    set_cords(node->pos.x, node->pos.y);
    std::cout << node->value;

    if (node->left) {
        set_cords((node->pos.x + node->left->pos.x) / 2,
            (node->pos.y + node->left->pos.y) / 2);
        std::cout << "/";
    }

    if (node->right) {
        set_cords((node->pos.x + node->right->pos.x) / 2,
            (node->pos.y + node->right->pos.y) / 2);
        std::cout << "\\";
    }

    draw(node->left);
    draw(node->right);
}

void BinaryTree::layout(BinaryTree::Node* node, int x, int y, int offset) {
    if (!node) return;

    node->pos = { x, y };

    layout(node->left, x - offset, y + 4, offset / 2);
    layout(node->right, x + offset, y + 4, offset / 2);
}


void BinaryTree::animateBuild() {
    system("cls");
    hideCursor();

    // шаг 1 Ч корень
    setRoot(10);
    layout(root, 40, 1, 20);
    system("cls");
    draw(root);
    wait(400);

    // шаг 2
    addLeft(root, 5);
    layout(root, 40, 1, 20);
    system("cls");
    draw(root);
    wait(400);

    // шаг 3
    addRight(root, 20);
    layout(root, 40, 1, 20);
    system("cls");
    draw(root);
    wait(400);

    // шаг 4
    addLeft(root->left, 3);
    layout(root, 40, 1, 20);
    system("cls");
    draw(root);
    wait(400);

    // шаг 5
    addRight(root->left, 7);
    layout(root, 40, 1, 20);
    system("cls");
    draw(root);
    wait(400);

    // шаг 6
    addRight(root->right, 30);
    layout(root, 40, 1, 20);
    system("cls");
    draw(root);
    wait(400);
}