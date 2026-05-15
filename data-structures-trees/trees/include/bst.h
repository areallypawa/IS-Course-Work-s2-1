#pragma once
#include <iostream>
#include <iterator>
#include <string>
#include <conio.h>
#include <sstream>
#include <fstream>
#include <random>
#include "menu.h"

class BST
{
private:
	struct Node
	{
		int value;
		Node *left;
		Node *right;

		Node(int value);
	};
	Node *root;

	void print(Node *node);
	void printPretty(Node *node, trunk *prev, bool isLeft, std::ostream &out);
	Node *deleteNode(Node *node, int value);
	Node *findMin(Node *node);

	void inOrder(Node *node);
	void preOrder(Node *node);
	void postOrder(Node *node);
	void levelOrder(Node *node);

public:
	BST();
	void clear();
	~BST();

	void setRoot(int value);
	Node *getRoot();

	void insert(int value);
	void insertAuto(int N);
	void insertFromInput();
	void insertFromFile(const std::string &filename);
	bool search(int value);
	void deleteTree(Node *node);
	void deleteElement(int value);
	void print();
	void printPretty(Node *root, std::ostream &out);
	int height(Node* node);
	
	void inOrder();
	void preOrder();
	void postOrder();
	void levelOrder();
};

void showTrunk(trunk *p, std::ostream &out);
void createTreeBst(Logis &log);