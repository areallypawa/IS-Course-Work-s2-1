#pragma once
#include <iostream>
#include <sstream>
#include <fstream>
#include <queue>
#include <random>
#include <chrono>
#include <conio.h>

#include "menu.h"

class RedBlack
{
private:

    enum Color
    {
        REDs,
        BLACK
    };

    struct Node
    {
        int value;

        Color color;

        Node* left;
        Node* right;
        Node* parent;

        Node(int value);
    };

    Node* root;

private:

    void deleteTree(Node* node);
    void rotateLeft(Node* x);
    void rotateRight(Node* y);
    void fixInsert(Node* node);
    void insertNode(int value);
    bool search(Node* node, int value);
    bool checkRedBlack(Node* node);

    Node* findMin(Node* node);

    void print(Node* node);
    void printPretty(Node* node,
        trunk* prev,
        bool isLeft,
        std::ostream& out);

public:
    RedBlack();
    ~RedBlack();
    void clear();
    bool empty();

    void setRoot(int value);
    Node* getRoot();

    void insert(int value);
    void insertAuto(int N);
    void insertFromInput();
    void insertFromFile(const std::string& filename);
    void deleteElement(int value);
    bool search(int value);
    void checkBalance();
    void transplant(Node* u, Node* v);
    void inOrder(Node* node);
    void preOrder(Node* node);
    void postOrder(Node* node);
    void levelOrder(Node* node);
    void print();
    int height(Node* node);
    void printPretty(Node* root,
        std::ostream& out = std::cout);

    void fixDelete(Node* x, Node* parent);
};

void showTrunk(trunk* p, std::ostream& out);
void createTreeRb(Logis& log);