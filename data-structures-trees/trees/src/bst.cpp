#include "bst.h"

using namespace std;

static int currentItems = 0;
static int currentChoose = 0;

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

void BST::clear() {
    deleteTree(root);
    root = nullptr;
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

    cout << node->value << " ";
    print(node->left);
    print(node->right);
}

void BST::print() {
    print(root);
}

void BST::printPretty(Node* node, trunk* prev, bool isLeft, ostream& out) {
    if (!node) return;

    string prev_str = "    ";
    trunk tmp(prev, prev_str);

    printPretty(node->right, &tmp, false, out);

    if (!prev) {
        tmp.str = "--> ";
    }
    else if (isLeft) {
        tmp.str = "`--> ";
        prev_str = "   |";
    }
    else {
        tmp.str = ".--> ";
        prev->str = prev_str;
    }

    int count = 0;
    showTrunk(&tmp, out);
    out << node->value << '\n';

    if (prev) {
        prev->str = prev_str;
    }
    tmp.str = "   |";
    printPretty(node->left, &tmp, true, out);
}

void BST::printPretty(Node* root, ostream& out) {
    printPretty(root, nullptr, false, out);
}

void BST::insert(int value) {
    if (!root) {
        root = new Node(value);
        return;
    }

    Node* current = root;
    while (true) {
        if (value < current->value) {
            if (!current->left) {
                current->left = new Node(value);
                return;
            }
            current = current->left;
        }
        else {
            if (!current->right) {
                current->right = new Node(value);
                return;
            }
            current = current->right;
        }
    }
}

void BST::insertFromInput() {
    cout << "Введи числа: ";

    string line;
    getline(cin, line);

    stringstream ss(line);
    int value;

    while (ss >> value) {
        this->insert(value);
    }
}

BST::Node* BST::findMin(Node* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

BST::Node* BST::deleteNode(Node* node, int value) {
    if (!node) return nullptr;

    if (value < node->value) {
        node->left = deleteNode(node->left, value);
    }
    else if (value > node->value) {
        node->right = deleteNode(node->right, value);
    }
    else {
        if (!node->left) {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        else if (!node->right) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        Node* temp = findMin(node->right);

        node->value = temp->value;

        node->right = deleteNode(node->right, temp->value);
    }

    return node;
}

void BST::deleteElement(int value) {
    root = deleteNode(root, value);
}

bool BST::search(int value) {
    Node* current = root;

    while (current) {
        if (value == current->value)
            return true;
        else if (value < current->value)
            current = current->left;
        else
            current = current->right;
    }

    return false;
}

void BST::insertAuto(int N) {
    for (int i = 0; i < N; ++i) {
        insert(rand() % 199 - 99);
    }
}

void BST::inOrder(Node* node) {
    if (!node) return;

    inOrder(node->left);
    cout << node->value << " ";
    inOrder(node->right);
}

void BST::preOrder(Node* node) {
    if (!node) return;

    cout << node->value << " ";
    preOrder(node->left);
    preOrder(node->right);
}

void BST::postOrder(Node* node) {
    if (!node) return;

    postOrder(node->left);
    postOrder(node->right);
    cout << node->value << " ";
}

#include <queue>
void BST::levelOrder(Node* node) {
    if (!node) return;

    queue<Node*> q;
    q.push(node);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        cout << current->value << " ";

        if (current->left)
            q.push(current->left);

        if (current->right)
            q.push(current->right);
    }
}

void BST::inOrder() {
    inOrder(root);
}

void BST::preOrder() {
    preOrder(root);
}

void BST::postOrder() {
    postOrder(root);
}

void BST::levelOrder() {
    levelOrder(root);
}

void BST::insertFromFile(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        clear();
        cout << RED << "Ошибка открытия файла\n" << RESET;
        return;
    }

    int value;

    while (file >> value) {
        insert(value);
    }

    file.close();
}

void createTreeBst(Logis& log) {
    BST tree;
    currentItems = 0;
    currentChoose = 0;
    do {
        while (true) {
            show_menu(currentItems, countItems, items, "МЕНЮ");
            int key = _getch();

            if (key == 72 && currentItems > 0) currentItems--;
            if (key == 80 && currentItems < countItems - 1) currentItems++;
            if (key == 13) break;
        }

        switch (currentItems) {
        case 0:
        {
            int N;
            int currentClear = 0;
            string a[2] = { "Да", "Нет" };
            if (tree.getRoot()) {
                clear();
                while (true) {
                    show_menu(currentClear, 2, a, "Перезаписать дерево?");
                    int key = _getch();

                    if (key == 72 && currentClear > 0) currentClear--;
                    if (key == 80 && currentClear < 2 - 1) currentClear++;
                    if (key == 13) break;
                }
                switch (currentClear) {
                case 0:
                {
                    tree.clear();
                    break;
                }
                }
            }
            clear();
            while (true) {
                show_menu(currentChoose, coutChooseItems, ChooseItems, "Выбор функции");
                int key = _getch();

                if (key == 72 && currentChoose > 0) currentChoose--;
                if (key == 80 && currentChoose < coutChooseItems - 1) currentChoose++;
                if (key == 13) break;
            }
            switch (currentChoose) {
            case 0:
            {
                cout << "Введи N: ";
                cin >> N;

                MEASURE("BST", "Insert Auto", tree.insertAuto(N));
                if (N <= 100) {
                    cout << GREEN << "АВЛ дерево:" << '\n' << '\n' << RESET;
                    tree.printPretty(tree.getRoot(), cout);
                }
                else cout << GREEN << "АВЛ дерево успешно создано с " << N << " элементами" << '\n' << RESET;

                pause();
                clear();
                break;
            }
            case 1:
            {
                MEASURE("BST", "Insert From Input", tree.insertFromInput());

                tree.printPretty(tree.getRoot(), cout);
                pause();
                clear();
                break;
            }
            case 2:
            {
				MEASURE("BST", "Insert From File", tree.insertFromFile("data/input.txt"));

				tree.printPretty(tree.getRoot(), cout);
                pause();
				clear();
                break;
            }
            }
            break;
        }
        case 1:
        {
            clear();
            if (!tree.getRoot()) {
                cout<< RED << "Двоичное дерево поиска отсутствует" << '\n' << RESET;
                pause();
                clear();
                break;
            }
            cout << GREEN << "Двоичное дерево поиска:" << '\n' << '\n' << RESET;
            MEASURE("BST", "Print", tree.printPretty(tree.getRoot(), cout));
            
            pause();
            clear();
            break;
        }
        case 2:
        {
            int num;
            clear();
            if (!tree.getRoot()) {
                cout << RED << "Двоичное дерево поиска отсутствует" << '\n' << RESET;
                pause();
                clear();
                break;
            }
            cout << "BST:" << '\n';
            tree.printPretty(tree.getRoot(), cout);
            cout << "Введите число которое необходимо найти: " << '\n';
            cin >> num;
			MEASURE("BST", "Search", tree.search(num));
            if (tree.search(num)) {
                clear();
                cout << GREEN << "Элемент найден" << '\n' << RESET;
                pause();
                clear();
                break;
            }
            else {
                clear();
                cout << RED << "Такой элемент отсутствует!!!" << '\n' << RESET;
                pause();
                clear();
                break;
            }
		}
        case 3:
        {
            int num;
            clear();
            if (!tree.getRoot()) {
                cout << RED << "Двоичное дерево поиска отсутствует" << '\n' << RESET;
                pause();
                clear();
                break;
            }
            cout << "BST До удаления:" << '\n';
            tree.printPretty(tree.getRoot(), cout);
            cout << "Введите число которое необходимо удалить: " << '\n';
            cin >> num;
            if (!tree.search(num)) {
                clear();
                cout << RED << "Такой элемент отсутствует!!!" << '\n' << RESET;
                pause();
                clear();
                break;
            }
            MEASURE("BST", "Delete", tree.deleteElement(num));
            cout << "BST После удаления:" << '\n';
            tree.printPretty(tree.getRoot(), cout);
            pause();
            clear();
            break;
        }
        case 4:
        {
			clear();
            if (!tree.getRoot()) {
                cout << RED << "Двоичное дерево поиска отсутствует" << '\n' << RESET;
                pause();
                clear();
                break;
            }
			cout << "Прямой обход: " << '\n';
            MEASURE("BST", "PreOrder", tree.preOrder());
            cout << "\nСимметричный обход: " << '\n';
            MEASURE("BST", "InOrder", tree.inOrder());
            cout << "\nОбратный обход: " << '\n';
            MEASURE("BST", "PostOrder", tree.postOrder());
            cout << "\nПострочный обход: " << '\n';
            MEASURE("BST", "LevelOrder", tree.levelOrder());
            cout << '\n' << "-------------------------------------" << '\n';
			tree.printPretty(tree.getRoot(), cout);
            pause();
			clear();

        }
        }
    } while (currentItems != countItems - 1);
}
