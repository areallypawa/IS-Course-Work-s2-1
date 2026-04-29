#pragma once

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
	void deleteTree(Node* node);
	void printPretty(Node* node, int depth, bool isLeft);

public:
	BST();
	~BST();

	void setRoot(int value);
	Node* getRoot();

	void addLeft(Node* parent, int value);
	void addRight(Node* parent, int value);

	void print();
	void printPretty();

};