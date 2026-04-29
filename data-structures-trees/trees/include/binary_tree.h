#pragma once

class BinaryTree
{
private:
	struct Pos {
		int x;
		int y;
	};

	struct Node {
		int value;
		Node* left;
		Node* right;

		Pos pos;

		Node(int value);
	};
	Node* root;

	void print(Node* node);
	void deleteTree(Node* node);
	void printPretty(Node* node, int depth, bool isLeft);

public:
	BinaryTree();
	~BinaryTree();

	void setRoot(int value);
	Node* getRoot();

	void addLeft(Node* parent, int value);
	void addRight(Node* parent, int value);

	void print();      
	void printPretty();

	};