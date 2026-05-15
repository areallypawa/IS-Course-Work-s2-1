# Курсовая работа Binary Search Tree / AVL Tree / Red-Black Tree (CMake Project) 

Репозиторий содержит реализации основных структур данных деревьев поиска:

- 🌿 Бинарное дерево поиска (BST)
- ⚖️ АВЛ-дерево (AVL Tree)
- 🔴⚫ Красно-чёрное дерево (Red-Black Tree)

Проект собран с использованием **CMake** и может быть открыт в **Visual Studio**, **CLion** или любой IDE с поддержкой CMake.

---

# 📌 Описание проекта

## 🌿 BST (Binary Search Tree)
Обычное бинарное дерево поиска:
- Вставка: O(log n) в среднем случае
- Поиск: O(log n)
- Худший случай: O(n) (вырожденное дерево)

---

## ⚖️ AVL Tree
Самобалансирующееся дерево поиска:
- Строгий баланс высоты поддеревьев
- Все операции: O(log n)
- Используются повороты (rotations)

---

## 🔴⚫ Red-Black Tree
Самобалансирующееся дерево:
- Менее строгий баланс, чем AVL
- Все операции: O(log n)
- Используется в std::map / std::set

---

# 🛠️ Требования

Для запуска проекта нужно:

- CMake (3.15+)
- Visual Studio 2019/2022 (или другой C++ компилятор)
- Поддержка C++17 или выше

---

# 💻 Как открыть проект в Visual Studio

1. Склонируй репозиторий:

```bash
git clone https://github.com/your-username/your-repo.git
cd your-repo
```

2. Открой папку в Visual Studio:

```
File → Open → Folder → выбери папку проекта
```

3. Visual Studio сама найдёт `CMakeLists.txt`

4. Выбери конфигурацию:
- Debug / Release
- x64 (рекомендуется)

5. Нажми Run ▶

---

# 🧪 Сборка через терминал (CMake)

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

---

# 📂 Структура проекта

```
.
├── src/
│   ├── bst.cpp
│   ├── avl.cpp
│   ├── binary_tree.cpp
│   ├── red_black.cpp
|   ├── menu.cpp
│   └── main.cpp
├── include/
│   ├── bst.h
│   ├── avl.h
│   ├── binary_tree.h
|   ├── menu.h
│   └── red_black.h
├── CMakeLists.txt
└── README.md
```

---

# 🚀 Возможности проекта

- Вставка элементов
- Удаление элементов
- Поиск элементов
- Обход дерева (inorder / preorder / postorder)
- Демонстрация балансировки AVL и Red-Black Tree

---

# 🎯 Цель

Проект создан для изучения:

- структур данных
- алгоритмов балансировки деревьев
- C++
- CMake
- сравнительного анализа BST, AVL и Red-Black Tree

---

# 📄 Лицензия

Проект создан в учебных целях и может свободно использоваться.
