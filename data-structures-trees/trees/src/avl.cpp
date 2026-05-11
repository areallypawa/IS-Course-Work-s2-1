#include "avl.h"

using namespace std;

/*
    SERVICE CODE
*/

static int currentItems = 0;
static int currentChoose = 0;

/*
    SERVICE CODE
*/

AVL::Node::Node(int value) : value(value), left(nullptr), right(nullptr), height(0) {
}

AVL::AVL() {
    root = nullptr;
}

void AVL::deleteTree(Node* node) {
    if (!node) return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void AVL::clear() {
    deleteTree(root);
    root = nullptr;
}

AVL::~AVL() {
    deleteTree(root);
}

void AVL::setRoot(int value) {
    root = new Node(value);
}

AVL::Node* AVL::getRoot() {
    return root;
}

void AVL::addLeft(Node* parent, int value) {
    if (parent)
        parent->left = new Node(value);
}

void AVL::addRight(Node* parent, int value) {
    if (parent)
        parent->right = new Node(value);
}

void AVL::print(Node* node) {
    if (!node) return;

    cout << node->value << " ";
    print(node->left);
    print(node->right);
}

void AVL::print() {
    print(root);
}

void AVL::printPretty(Node* node, trunk* prev, bool isLeft, ostream& out) {
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

void AVL::printPretty(Node* root, ostream& out) {
    printPretty(root, nullptr, false, out);
}

AVL::Node* AVL::insertA(Node* node, int value)
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

void AVL::insert(int value) {
    root = insertA(root, value);
}

void AVL::insertAuto(int N) {
    for (int i = 0; i < N; ++i) {
        insert(rand() % 199 - 99);
    }
}

void AVL::insertFromInput() {
    cout << "Введи числа: ";

    string line;
    getline(cin, line);

    stringstream ss(line);
    int value;

    while (ss >> value) {
        this->insert(value);
    }
}

AVL::Node* AVL::findMin(Node* node) {
    while (node && node->left)
        node = node->left;
    return node;
}

AVL::Node* AVL::deleteNode(Node* node, int value) {
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

void AVL::deleteElement(int value) {
    root = deleteNode(root, value);
}

bool AVL::search(int value) {
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

void AVL::inOrder(Node* node) {
    if (!node) return;

    inOrder(node->left);
    cout << node->value << " ";
    inOrder(node->right);
}

void AVL::preOrder(Node* node) {
    if (!node) return;

    cout << node->value << " ";
    preOrder(node->left);
    preOrder(node->right);
}

void AVL::postOrder(Node* node) {
    if (!node) return;

    postOrder(node->left);
    postOrder(node->right);
    cout << node->value << " ";
}

#include <queue>
void AVL::levelOrder(Node* node) {
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

void AVL::inOrder() {
    inOrder(root);
}

void AVL::preOrder() {
    preOrder(root);
}

void AVL::postOrder() {
    postOrder(root);
}

void AVL::levelOrder() {
    levelOrder(root);
}

void AVL::insertFromFile(const string& filename) {
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

int AVL::getHeight(Node* node) {
    return node ? node->height : -1;
}

void AVL::updateHeight(Node* node) {
    if (node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
    }
}

int AVL::getBalance(Node* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

void AVL::swap(Node* a, Node* b) {
    int temp = a->value;
    a->value = b->value;
    b->value = temp;
}

AVL::Node* AVL::rotateRight(Node* y){
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);

    return x;
}

AVL::Node* AVL::rotateLeft(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);

    return y;
}

void AVL::balance(Node *node) {
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

void createTreeAvl(Logis& log) {
    AVL tree;
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
            tree.clear();
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

                MEASURE("AVL", "Insert Auto", tree.insertAuto(N));

                tree.printPretty(tree.getRoot(), cout);
                pause();
                clear();
                break;
            }
            case 1:
            {
                MEASURE("AVL", "Insert From Input", tree.insertFromInput());

                tree.printPretty(tree.getRoot(), cout);
                pause();
                clear();
                break;
            }
            case 2:
            {
                MEASURE("AVL", "Insert From File", tree.insertFromFile("data/input.txt"));

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
                cout << RED << "АВЛ дерево отсутствует" << '\n' << RESET;
                pause();
                clear();
                break;
            }
            cout << GREEN << "АВЛ дерево:" << '\n' << '\n' << RESET;
            MEASURE("AVL", "Print", tree.printPretty(tree.getRoot(), cout));

            pause();
            clear();
            break;
        }
        case 2:
        {
            int num;
            clear();
            if (!tree.getRoot()) {
                cout << RED << "АВЛ дерево" << '\n' << RESET;
                pause();
                clear();
                break;
            }
            cout << "AVL:" << '\n';
            tree.printPretty(tree.getRoot(), cout);
            cout << "Введите число которое необходимо найти: " << '\n';
            cin >> num;
            MEASURE("AVL", "Search", tree.search(num));
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
                cout << RED << "АВЛ дерево отсутствует" << '\n' << RESET;
                pause();
                clear();
                break;
            }
            cout << "AVL До удаления:" << '\n';
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
            MEASURE("AVL", "Delete", tree.deleteElement(num));
            cout << "AVL После удаления:" << '\n';
            tree.printPretty(tree.getRoot(), cout);
            pause();
            clear();
            break;
        }
        case 4:
        {
            clear();
            if (!tree.getRoot()) {
                cout << RED << "АВЛ дерево отсутствует" << '\n' << RESET;
                pause();
                clear();
                break;
            }
            cout << "Прямой обход: " << '\n';
            MEASURE("AVL", "PreOrder", tree.preOrder());
            cout << "\nСимметричный обход: " << '\n';
            MEASURE("AVL", "InOrder", tree.inOrder());
            cout << "\nОбратный обход: " << '\n';
            MEASURE("AVL", "PostOrder", tree.postOrder());
            cout << "\nПострочный обход: " << '\n';
            MEASURE("AVL", "LevelOrder", tree.levelOrder());
            cout << '\n' << "-------------------------------------" << '\n';
            tree.printPretty(tree.getRoot(), cout);
            pause();
            clear();

        }
        }
    } while (currentItems != countItems - 1);
}
