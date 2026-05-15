#include "red_black.h"

using namespace std;

static int currentItems = 0;
static int currentChoose = 0;

RedBlack::Node::Node(int value) : value(value), color(REDs), left(nullptr), right(nullptr), parent(nullptr) {
}


RedBlack::RedBlack()
{
    root = nullptr;
}

void RedBlack::clear()
{
    deleteTree(root);
    root = nullptr;
}


RedBlack::~RedBlack()
{
    deleteTree(root);
}

void RedBlack::deleteTree(Node* node) {
    if (!node) return;

    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

bool RedBlack::empty()
{
    return root == nullptr;
}

void RedBlack::setRoot(int value)
{
    root = new Node(value);
}

RedBlack::Node* RedBlack::getRoot()
{
    return root;
}

// ---------------- INSERT ----------------

void RedBlack::insert(int value)
{
    insertNode(value);
}

void RedBlack::insertAuto(int N)
{
    random_device rd;
    mt19937 gen(rd());

    uniform_int_distribution<int> dist(-1000000000, 1000000000);

    for (int i = 0; i < N; i++)
    {
        insert(dist(gen));
    }
}

void RedBlack::insertFromInput()
{
    cout << "Введи числа: ";

    string line;
    getline(cin, line);

    stringstream ss(line);
    int value;

    while (ss >> value)
        insert(value);
}

void RedBlack::insertFromFile(const string& filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cout << "Ошибка файла\n";
        return;
    }

    int value;
    while (file >> value)
        insert(value);
}

bool RedBlack::search(int value)
{
    return search(root, value);
}

bool RedBlack::search(Node* node, int value)
{
    if (!node) return false;

    if (node->value == value) return true;

    if (value < node->value)
        return search(node->left, value);

    return search(node->right, value);
}

void RedBlack::deleteElement(int value)
{
    Node* z = root;

    while (z && z->value != value)
        z = (value < z->value) ? z->left : z->right;

    if (!z) return;

    Node* y = z;
    Node* x = nullptr;
    Color yOriginalColor = y->color;

    if (!z->left)
    {
        x = z->right;
        transplant(z, z->right);
    }
    else if (!z->right)
    {
        x = z->left;
        transplant(z, z->left);
    }
    else
    {
        y = findMin(z->right);
        yOriginalColor = y->color;
        x = y->right;

        if (y->parent == z)
        {
            if (x) x->parent = y;
        }
        else
        {
            transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }

        transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
    }

    delete z;

    if (yOriginalColor == BLACK)
        fixDelete(x, (x ? x->parent : nullptr));
}

void RedBlack::fixDelete(Node* x, Node* parent)
{
    while (x != root && (x == nullptr || x->color == BLACK))
    {
        if (x == (parent ? parent->left : nullptr))
        {
            Node* w = parent->right;

            // CASE 1
            if (w && w->color == REDs)
            {
                w->color = BLACK;
                parent->color = REDs;
                rotateLeft(parent);
                w = parent->right;
            }

            // CASE 2
            if ((!w->left || w->left->color == BLACK) &&
                (!w->right || w->right->color == BLACK))
            {
                if (w) w->color = REDs;
                x = parent;
                parent = x ? x->parent : nullptr;
            }
            else
            {
                // CASE 3
                if (!w->right || w->right->color == BLACK)
                {
                    if (w->left) w->left->color = BLACK;
                    w->color = REDs;
                    rotateRight(w);
                    w = parent->right;
                }

                // CASE 4
                if (w)
                {
                    w->color = parent->color;
                    parent->color = BLACK;
                    if (w->right) w->right->color = BLACK;
                    rotateLeft(parent);
                }

                x = root;
                break;
            }
        }
        else
        {
            Node* w = parent->left;

            // зеркальные CASE 1-4 (аналогично)
            if (w && w->color == REDs)
            {
                w->color = BLACK;
                parent->color = REDs;
                rotateRight(parent);
                w = parent->left;
            }

            if ((!w->right || w->right->color == BLACK) &&
                (!w->left || w->left->color == BLACK))
            {
                if (w) w->color = REDs;
                x = parent;
                parent = x ? x->parent : nullptr;
            }
            else
            {
                if (!w->left || w->left->color == BLACK)
                {
                    if (w->right) w->right->color = BLACK;
                    w->color = REDs;
                    rotateLeft(w);
                    w = parent->left;
                }

                if (w)
                {
                    w->color = parent->color;
                    parent->color = BLACK;
                    if (w->left) w->left->color = BLACK;
                    rotateRight(parent);
                }

                x = root;
                break;
            }
        }
    }

    if (x)
        x->color = BLACK;
}

RedBlack::Node* RedBlack::findMin(Node* node)
{
    while (node && node->left)
        node = node->left;

    return node;
}

void RedBlack::checkBalance()
{
    if (!root)
    {
        cout << "Дерево пустое\n";
        return;
    }

    if (checkRedBlack(root))
        cout << "OK (RB свойства соблюдены)\n";
    else
        cout << "НАРУШЕНИЕ RB свойств\n";
}

bool RedBlack::checkRedBlack(Node* node)
{
    if (!node) return true;

    if (node->color == REDs)
    {
        if ((node->left && node->left->color == REDs) ||
            (node->right && node->right->color == REDs))
            return false;
    }

    return checkRedBlack(node->left) &&
        checkRedBlack(node->right);
}

void RedBlack::rotateLeft(Node* x)
{
    Node* y = x->right;

    x->right = y->left;

    if (y->left)
        y->left->parent = x;

    y->parent = x->parent;

    if (!x->parent)
        root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;

    y->left = x;
    x->parent = y;
}

void RedBlack::rotateRight(Node* y)
{
    Node* x = y->left;

    y->left = x->right;

    if (x->right)
        x->right->parent = y;

    x->parent = y->parent;

    if (!y->parent)
        root = x;
    else if (y == y->parent->left)
        y->parent->left = x;
    else
        y->parent->right = x;

    x->right = y;
    y->parent = x;
}

void RedBlack::insertNode(int value)
{
    Node* node = new Node(value);

    Node* parent = nullptr;
    Node* current = root;

    while (current)
    {
        parent = current;

        if (value < current->value)
            current = current->left;
        else if (value > current->value)
            current = current->right;
        else
        {
            delete node;
            return;
        }
    }

    node->parent = parent;

    if (!parent)
        root = node;
    else if (value < parent->value)
        parent->left = node;
    else
        parent->right = node;

    fixInsert(node);
}

int RedBlack::height(Node* node)
{
    if (!node)
        return 0;

    int leftHeight = height(node->left);
    int rightHeight = height(node->right);

    return max(leftHeight, rightHeight) + 1;
}

void RedBlack::printPretty(Node* root, trunk* prev, bool isLeft, ostream& out)
{
    if (root == nullptr)
        return;

    string prev_str = "    ";
    trunk* trunki = new trunk(prev, prev_str);

    // правое поддерево
    printPretty(root->right, trunki, true, out);

    if (!prev)
    {
        trunki->str = "--";
    }
    else if (isLeft)
    {
        trunki->str = ".--";
        prev_str = "   |";
    }
    else
    {
        trunki->str = "`--";
        prev->str = prev_str;
    }

    showTrunk(trunki, out);
    

    if (root->color == REDs)
        out << RED << root->value << RESET << endl;
    else
        out << root->value << endl;

    if (prev)
        prev->str = prev_str;

    trunki->str = "   |";

    // левое поддерево
    printPretty(root->left, trunki, false, out);

    delete trunki;
}

void RedBlack::printPretty(Node* root, ostream& out)
{
    printPretty(root, nullptr, false, out);
}

void RedBlack::fixInsert(Node* node)
{
    while (node != root &&
        node->parent &&
        node->parent->color == REDs)
    {
        Node* parent = node->parent;
        Node* grand = parent->parent;

        if (!grand)
            break;

        // parent слева
        if (parent == grand->left)
        {
            Node* uncle = grand->right;

            // CASE 1 recolor
            if (uncle && uncle->color == REDs)
            {
                parent->color = BLACK;
                uncle->color = BLACK;
                grand->color = REDs;

                node = grand;
            }
            else
            {
                // CASE 2
                if (node == parent->right)
                {
                    node = parent;
                    rotateLeft(node);

                    parent = node->parent;
                    grand = parent->parent;
                }

                // CASE 3
                parent->color = BLACK;
                grand->color = REDs;

                rotateRight(grand);
            }
        }
        else
        {
            Node* uncle = grand->left;

            if (uncle && uncle->color == REDs)
            {
                parent->color = BLACK;
                uncle->color = BLACK;
                grand->color = REDs;

                node = grand;
            }
            else
            {
                // CASE 2
                if (node == parent->left)
                {
                    node = parent;
                    rotateRight(node);

                    parent = node->parent;
                    grand = parent->parent;
                }

                // CASE 3
                parent->color = BLACK;
                grand->color = REDs;

                rotateLeft(grand);
            }
        }
    }

    root->color = BLACK;
}


void RedBlack::transplant(Node* u, Node* v)
{
    if (!u->parent)
        root = v;
    else if (u == u->parent->left)
        u->parent->left = v;
    else
        u->parent->right = v;

    if (v)
        v->parent = u->parent;
}

void RedBlack::print()
{
    print(root);
}

void RedBlack::print(Node* node)
{
    if (!node) return;

    cout << node->value << " ";
    print(node->left);
    print(node->right);
}

void RedBlack::inOrder(Node* node)
{
    if (!node) return;

    inOrder(node->left);
    cout << node->value << " ";
    inOrder(node->right);
}

void RedBlack::preOrder(Node* node)
{
    if (!node) return;

    cout << node->value << " ";
    preOrder(node->left);
    preOrder(node->right);
}

void RedBlack::postOrder(Node* node)
{
    if (!node) return;

    postOrder(node->left);
    postOrder(node->right);
    cout << node->value << " ";
}

void RedBlack::levelOrder(Node* node)
{
    if (!node) return;

    queue<Node*> q;
    q.push(node);

    while (!q.empty())
    {
        Node* cur = q.front();
        q.pop();

        cout << cur->value << " ";

        if (cur->left) q.push(cur->left);
        if (cur->right) q.push(cur->right);
    }
}

void createTreeRb(Logis& log) {
    RedBlack tree;
    currentChoose = 0;
    currentItems = 0;
    bool isBigNum = false;

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
					isBigNum = false;
                    cout << GREEN << "КЧ дерево:" << '\n' << '\n' << RESET;
                    tree.printPretty(tree.getRoot(), cout);
                }
                else {
                    cout << GREEN << "КЧ дерево успешно создано с " << N << " элементами" << '\n' << RESET;
					isBigNum = true;
                }
                pause();
                clear();
                break;
            }
            case 1:
            {
                MEASURE("RedBlack", "Insert From Input", tree.insertFromInput());

                cout << GREEN << "КЧ дерево успешно создано" << RESET;
                pause();
                clear();
                break;
            }
            case 2:
            {
                MEASURE("RedBlack", "Insert From File", tree.insertFromFile("data/input.txt"));

                cout << GREEN << "КЧ дерево успешно создано" << RESET;
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
            if (!isBigNum)
            {
                cout << GREEN << "КЧ дерево:" << '\n' << '\n' << RESET;
                MEASURE("RedBlack", "Print", tree.printPretty(tree.getRoot(), cout));
            }
            else
            {
                cout << GREEN << "Высота дерева: " << tree.height(tree.getRoot()) << RESET << '\n';
                MEASURE("RedBlack", "GetHeight", tree.height(tree.getRoot()));
            }
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
            if (!isBigNum)
            {
                cout << GREEN << "КЧ дерево:" << '\n' << '\n' << RESET;
                MEASURE("RedBlack", "Print", tree.printPretty(tree.getRoot(), cout));
            }
            else
            {
                cout << GREEN << "Высота дерева: " << tree.height(tree.getRoot()) << RESET << '\n';
                MEASURE("RedBlack", "GetHeight", tree.height(tree.getRoot()));
            }
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
            if (!isBigNum)
            {
                cout << GREEN << "КЧ дерево до удаления:" << '\n' << '\n' << RESET;
                tree.printPretty(tree.getRoot(), cout);
            }
            else
            {
                cout << GREEN << "Высота дерева до удаления: " << tree.height(tree.getRoot()) << RESET << '\n';
            }
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
            if (!isBigNum)
            {
                cout << GREEN << "КЧ дерево после удаления:" << '\n' << '\n' << RESET;
                tree.printPretty(tree.getRoot(), cout);
            }
            else
            {
                cout << GREEN << "Высота дерева после удаления: " << tree.height(tree.getRoot()) << RESET << '\n';
            }
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
            pause();
            clear();

        }
        }
    } while (currentItems != countItems - 1);
}
