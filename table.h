#ifndef TABLE_H
#define TABLE_H

#include <string>
#include "polynom.h"
#include "RedBlackTree.h"

class Table {
public:
    virtual void Insert(const std::string& name, const Polynom& value) = 0;
    virtual bool Find(const std::string& name, Polynom& value) = 0;
    virtual ~Table() {}
};

class TableArray : public Table {
    // Реализация на основе массива
};

class RBT : public Table {
    // Конструктор узла
    Node::Node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}

    // Конструктор красно-черного дерева
    RedBlackTree::RedBlackTree() : root(nullptr) {}

    // Левый поворот
    void RedBlackTree::rotateLeft(Node*& pt) {
        Node* pt_y = pt->right; // Узел, который станет новым корнем поддерева
        pt->right = pt_y->left; // Переносим левое поддерево pt_y к правому поддереву pt

        if (pt_y->left != nullptr)
            pt_y->left->parent = pt;

        pt_y->parent = pt->parent;

        if (pt->parent == nullptr)
            root = pt_y; // Если pt был корнем, обновляем корень
        else if (pt == pt->parent->left)
            pt->parent->left = pt_y; // Если pt был левым дочерним узлом
        else
            pt->parent->right = pt_y; // Если pt был правым дочерним узлом

        pt_y->left = pt; // Перемещаем pt в левое поддерево pt_y
        pt->parent = pt_y; // Обновляем родителя pt
    }

    // Правый поворот
    void RedBlackTree::rotateRight(Node*& pt) {
        Node* pt_y = pt->left; // Узел, который станет новым корнем поддерева
        pt->left = pt_y->right; // Переносим правое поддерево pt_y к левому поддереву pt

        if (pt_y->right != nullptr)
            pt_y->right->parent = pt;

        pt_y->parent = pt->parent;

        if (pt->parent == nullptr)
            root = pt_y; // Если pt был корнем, обновляем корень
        else if (pt == pt->parent->left)
            pt->parent->left = pt_y; // Если pt был левым дочерним узлом
        else
            pt->parent->right = pt_y; // Если pt был правым дочерним узлом

        pt_y->right = pt; // Перемещаем pt в правое поддерево pt_y
        pt->parent = pt_y; // Обновляем родителя pt
    }

    // Исправление нарушений свойств красно-черного дерева
    void RedBlackTree::fixViolation(Node*& pt) {
        Node* parent_pt = nullptr;
        Node* grandparent_pt = nullptr;

        // Пока текущий узел не корень и родитель красный
        while ((pt != root) && (pt->color == RED) && (pt->parent->color == RED)) {
            parent_pt = pt->parent;
            grandparent_pt = pt->parent->parent;

            // Случай A: Родитель pt - левый ребенок деда pt
            if (parent_pt == grandparent_pt->left) {
                Node* uncle_pt = grandparent_pt->right;

                // Случай 1: Дядя pt тоже красный, только перекрашивание
                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grandparent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grandparent_pt; // Поднимаем деда
                }
                else {
                    // Случай 2: pt - правый ребенок своего родителя
                    if (pt == parent_pt->right) {
                        rotateLeft(parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    // Случай 3: pt - левый ребенок своего родителя
                    rotateRight(grandparent_pt);
                    std::swap(parent_pt->color, grandparent_pt->color);
                    pt = parent_pt;
                }
            }
            else { // Случай B: Родитель pt - правый ребенок деда pt
                Node* uncle_pt = grandparent_pt->left;

                // Случай 1: Дядя pt тоже красный, только перекрашивание
                if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
                    grandparent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grandparent_pt; // Поднимаем деда
                }
                else {
                    // Случай 2: pt - левый ребенок своего родителя
                    if (pt == parent_pt->left) {
                        rotateRight(parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    // Случай 3: pt - правый ребенок своего родителя
                    rotateLeft(grandparent_pt);
                    std::swap(parent_pt->color, grandparent_pt->color);
                    pt = parent_pt;
                }
            }
        }
        root->color = BLACK; // Убедимся, что корень черный
    }

    // Вставка нового узла
    Node* RedBlackTree::BSTInsert(Node* root, Node* pt) {
        // Если дерево пустое, возвращаем новый узел
        if (root == nullptr) {
            return pt;
        }

        // Вставляем узел в соответствующее место в дереве
        if (pt->data < root->data) {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        }
        else if (pt->data > root->data) {
            root->right;
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }

        return root; // Возвращаем (неизмененный) указатель
    }

    // Вставка нового узла
    void RedBlackTree::insert(const int& data) {
        Node* pt = new Node(data); // Создаем новый узел
        root = BSTInsert(root, pt); // Вставляем узел в двоичное дерево поиска
        fixViolation(pt); // Исправляем нарушения свойств красно-черного дерева
    }

    // Обход дерева в порядке возрастания
    void RedBlackTree::inorderHelper(Node* root) {
        if (root == nullptr) return;

        inorderHelper(root->left); // Обходим левое поддерево
        std::cout << root->data << " "; // Выводим значение узла
        inorderHelper(root->right); // Обходим правое поддерево
    }

    // Метод для обхода дерева
    void RedBlackTree::inorder() {
        inorderHelper(root); // Начинаем обход с корня
    }

};

class HashT : public Table {
    // Реализация на основе хеш-таблицы
};

#endif // TABLE_H
