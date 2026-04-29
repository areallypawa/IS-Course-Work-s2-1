#include <iostream>
#include <string>
#include "bst.h"


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