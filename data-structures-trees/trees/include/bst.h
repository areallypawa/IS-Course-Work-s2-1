#pragma once
#include <iostream>
#include <iterator>
#include <string>
#include <conio.h>
#include <random>
#include "menu.h"
/*
	SERVICE CODE
*/

extern int currentItems;
extern int currentChoose;

extern std::string items[];
extern std::string ChooseItems[];

constexpr int countItems = 5;
constexpr int coutChooseItems = 3;

/*
	SERVICE CODE
*/

class BST
{
private:

	struct Node {
		int value;
		Node* left;
		Node* right;


		Node(int value);
	};
	Node* root;

	void print(Node* node);
	void printPretty(Node* node, int depth, bool isLeft);
	Node* deleteNode(Node* node, int value);
	Node* findMin(Node* node);
public:
	BST();
	~BST();

	void setRoot(int value);
	Node* getRoot();

	void addLeft(Node* parent, int value);
	void addRight(Node* parent, int value);
	void insert(int value);
	bool search(int value);
	void deleteTree(Node* node);
	void deleteElement(int value);
	void print();
	void printPretty();

};

void insertAuto(BST& tree, int N);
void createTree(Logis& log);