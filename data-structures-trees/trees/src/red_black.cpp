#include "red_black.h"

using namespace std;

static int currentItems = 0;
static int currentChoose = 0;

RedBlack::Node::Node(int value) : value(value), left(nullptr), right(nullptr), height(0) {
}

RedBlack::RedBlack() {
    root = nullptr;
}

void RedBlack::deleteTree(Node* node) {
    if (!node) return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void RedBlack::clear() {
    deleteTree(root);
    root = nullptr;
}

RedBlack::~RedBlack() {
    deleteTree(root);
}

void RedBlack::setRoot(int value) {
    root = new Node(value);
}

RedBlack::Node* RedBlack::getRoot() {
    return root;
}

void RedBlack::addLeft(Node* parent, int value) {
    if (parent)
        parent->left = new Node(value);
}

void RedBlack::addRight(Node* parent, int value) {
    if (parent)
        parent->right = new Node(value);
}

void RedBlack::print(Node* node) {
    if (!node) return;

    cout << node->value << " ";
    print(node->left);
    print(node->right);
}

void RedBlack::print() {
    print(root);
}

void RedBlack::printPretty(Node* node, trunk* prev, bool isLeft, ostream& out) {
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

void RedBlack::printPretty(Node* root, ostream& out) {
    printPretty(root, nullptr, false, out);
}

RedBlack::Node* RedBlack::insertA(Node* node, int value)
{
    if (!node)
        return new Node(value);

    if (value < node->value)
        node->left = insertA(node->left, value);
    else if (value > node->value)
        node->right = insertA(node->right, value);
    else
        return node;

    updateHeight(node);

    int balance = getBalance(node);

    // Left Left
    if (balance > 1 && value < node->left->value)
        return rotateRight(node);

    // Right Right
    if (balance < -1 && value > node->right->value)
        return rotateLeft(node);

    // Left Right
    if (balance > 1 && value > node->left->value)
    {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right Left
    if (balance < -1 && value < node->right->value)
    {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

void RedBlack::insert(int value) {
    root = insertA(root, value);
}

void RedBlack::insertAuto(int N) {
    for (int i = 0; i < N; ++i) {
        insert(rand() % 199999 - 99999);
        // insert(rand() % 199 - 99);
    }
}

void RedBlack::insertFromInput() {
    cout << "Введи числа: ";

    string line;
    getline(cin, line);

    stringstream ss(line);
    int value;

    while (ss >> value) {
        this->insert(value);
    }
}

RedBlack::Node* RedBlack::findMin(Node* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

RedBlack::Node* RedBlack::deleteNode(Node* node, int value) {
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

void RedBlack::deleteElement(int value) {
    root = deleteNode(root, value);
}

bool RedBlack::search(int value) {
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

void RedBlack::inOrder(Node* node) {
    if (!node) return;

    inOrder(node->left);
    cout << node->value << " ";
    inOrder(node->right);
}

void RedBlack::preOrder(Node* node) {
    if (!node) return;

    cout << node->value << " ";
    preOrder(node->left);
    preOrder(node->right);
}

void RedBlack::postOrder(Node* node) {
    if (!node) return;

    postOrder(node->left);
    postOrder(node->right);
    cout << node->value << " ";
}

#include <queue>
void RedBlack::levelOrder(Node* node) {
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

void RedBlack::insertFromFile(const string& filename) {
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

int RedBlack::getHeight(Node* node) {
    return node ? node->height : -1;
}

void RedBlack::updateHeight(Node* node) {
    if (node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

int RedBlack::getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

void RedBlack::swap(Node* a, Node* b) {
    int temp = a->value;
    a->value = b->value;
    b->value = temp;
}

RedBlack::Node* RedBlack::rotateRight(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

RedBlack::Node* RedBlack::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

void RedBlack::balance(Node* node) {
    int balance = getBalance(node);
    if (balance == -2) {
        if (getBalance(node->left) == 1) rotateLeft(node->left);
        rotateRight(node);
    }
    if (balance == 2) {
        if (getBalance(node->right) == -1) rotateRight(node->right);
        rotateLeft(node);
    }
}

void createTreeRb(Logis& log) {
    RedBlack tree;
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

                MEASURE("RedBlack", "Insert Auto", tree.insertAuto(N));
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
                MEASURE("RedBlack", "Insert From Input", tree.insertFromInput());

                tree.printPretty(tree.getRoot(), cout);
                pause();
                clear();
                break;
            }
            case 2:
            {
                MEASURE("RedBlack", "Insert From File", tree.insertFromFile("data/input.txt"));

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
                cout << RED << "КЧ дерево отсутствует" << '\n' << RESET;
                pause();
                clear();
                break;
            }
            cout << GREEN << "КЧ дерево:" << '\n' << '\n' << RESET;
            MEASURE("RedBlack", "Print", tree.printPretty(tree.getRoot(), cout));

            pause();
            clear();
            break;
        }
        case 2:
        {
            int num;
            clear();
            if (!tree.getRoot()) {
                cout << RED << "КЧ дерево отсутствует" << '\n' << RESET;
                pause();
                clear();
                break;
            }
            cout << "RedBlack:" << '\n';
            tree.printPretty(tree.getRoot(), cout);
            cout << "Введите число которое необходимо найти: " << '\n';
            cin >> num;
            MEASURE("RedBlack", "Search", tree.search(num));
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
                cout << RED << "КЧ дерево отсутствует" << '\n' << RESET;
                pause();
                clear();
                break;
            }
            cout << "RedBlack До удаления:" << '\n';
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
            MEASURE("RedBlack", "Delete", tree.deleteElement(num));
            cout << "КЧ После удаления:" << '\n';
            tree.printPretty(tree.getRoot(), cout);
            pause();
            clear();
            break;
        }
        case 4:
        {
            clear();
            if (!tree.getRoot()) {
                cout << RED << "КЧ дерево отсутствует" << '\n' << RESET;
                pause();
                clear();
                break;
            }
            cout << "Прямой обход: " << '\n';
            MEASURE("RedBlack", "PreOrder", tree.preOrder(tree.getRoot()));
            cout << "\nСимметричный обход: " << '\n';
            MEASURE("RedBlack", "InOrder", tree.inOrder(tree.getRoot()));
            cout << "\nОбратный обход: " << '\n';
            MEASURE("RedBlack", "PostOrder", tree.postOrder(tree.getRoot()));
            cout << "\nПострочный обход: " << '\n';
            MEASURE("RedBlack", "LevelOrder", tree.levelOrder(tree.getRoot()));
            cout << '\n' << "-------------------------------------" << '\n';
            tree.printPretty(tree.getRoot(), cout);
            pause();
            clear();

        }
        }
    } while (currentItems != countItems - 1);
}
