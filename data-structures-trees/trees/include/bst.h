#pragma once
#include <iostream>
#include <iterator>
#include <string>
#include <conio.h>
#include <sstream>
#include <fstream>
#include <random>
#include "menu.h"

/*
	Не реализовано:
	- В отчете сравните скорость работы бинарного дерева с линейной структурой (двусвязным списком или динамическим массивом) и сделайте выводы.
	Остался только пункт с линейной структурой, так как в процессе реализации было принято решение не реализовывать двусвязный список, а использовать динамический массив (std::vector) для сравнения.
*/

/*
	SERVICE CODE
*/

extern int currentItems;
extern int currentChoose;

extern std::string items[];
extern std::string ChooseItems[];

constexpr int countItems = 6;
constexpr int coutChooseItems = 3;

struct trunk
{
	trunk *prev;
	std::string str;

	trunk(trunk *prev, std::string str)
	{
		this->prev = prev;
		this->str = str;
	}
};
/*
	SERVICE CODE
*/

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
	~BST();

	void setRoot(int value);
	Node *getRoot();
	void clear();

	void addLeft(Node *parent, int value);
	void addRight(Node *parent, int value);
	void insert(int value);
	void insertFromInput();
	void insertFromFile(const std::string &filename);
	bool search(int value);
	void deleteTree(Node *node);
	void deleteElement(int value);
	void print();
	void printPretty(Node *root, std::ostream &out);

	void inOrder();
	void preOrder();
	void postOrder();
	void levelOrder();
};

void showTrunk(trunk *p, std::ostream &out);
void insertAuto(BST &tree, int N);
void createTree(Logis &log);