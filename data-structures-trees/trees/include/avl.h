#pragma once
#include <iostream>
#include <iterator>
#include <string>
#include <conio.h>
#include <sstream>
#include <fstream>
#include <random>
#include "menu.h"

class AVL
{
private:
	struct Node
	{
		int value;
		Node* left;
		Node* right;
		int height;
		Node(int value);
	};
	Node* root;
	void print(Node* node);
	void printPretty(Node* node, trunk* prev, bool isLeft, std::ostream& out);
	Node* deleteNode(Node* node, int value);
	Node* insertA(Node* node, int value);

	void deleteTree(Node* node);
	Node* findMin(Node* node);
	int getHeight(Node* node);
	int getBalance(Node* node);
	void swap(Node* a, Node* b);
	
	Node* rotateRight(Node* y);
	Node* rotateLeft(Node* x);
	void balance(Node* node);
public:
	AVL();
	void clear();
	~AVL();
	void setRoot(int value);
	Node* getRoot();
	void insertAuto(int N);
	void insertFromInput();
	void insertFromFile(const std::string& filename);
	void deleteElement(int value);
	bool search(int value);
	
	void inOrder(Node* node);
	void preOrder(Node* node);
	void postOrder(Node* node);
	void levelOrder(Node* node);

	void print();
	void printPretty(Node* root, std::ostream& out = std::cout);
	
	void insert(int value);
	void updateHeight(Node* node);
};

void showTrunk(trunk* p, std::ostream& out);
void createTreeAvl(Logis& log);