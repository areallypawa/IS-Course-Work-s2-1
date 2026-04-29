#pragma once

/*
	   Сдесь нет реализации меню, так как это просто пример работы с бинарным деревом.
	   Вы можете реализовать меню, используя функции из класса Menu, который находится в файле menu.h.
	   По факту тут листья располагаются в виде:
			   10
			  /  \
			 5    20
			/ \     \
		   3   7     30
				\
				 6

	   и они никак не сортируются, так как это просто бинарное дерево, а не бинарное дерево поиска (BST).
	   Поэтому реализации пунктов со степика не будет, так как они относятся к BST, а не к обычному бинарному дереву.

*/

class BinaryTree
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
	void deleteTree(Node* node);
	void printPretty(Node* node, int depth, bool isLeft);


public:
	BinaryTree(bool demo);
	~BinaryTree();

	void setRoot(int value);
	Node* getRoot();

	void addLeft(Node* parent, int value);
	void addRight(Node* parent, int value);

	void print();      
	void printPretty();
	void buildDemoTree();
	void printDemo();
	};