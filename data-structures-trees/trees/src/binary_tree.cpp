#include <iostream>
#include <string>
#include "binary_tree.h"


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

void BinaryTree::printPretty(Node* node, int depth, bool isLeft) {
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

void BinaryTree::printPretty() {
    printPretty(root, 0, false);
}