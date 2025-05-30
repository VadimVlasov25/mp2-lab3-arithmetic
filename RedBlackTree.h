#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>

enum Color { RED, BLACK }; // Определяем цвета узлов

// Структура узла дерева
struct Node {
    int data; // Значение узла
    Color color; // Цвет узла
    Node* left, * right, * parent; // Указатели на дочерние и родительский узлы

    Node(int data);
};

// Класс красно-черного дерева
class RedBlackTree {
private:
    Node* root; // Корень дерева

    void rotateLeft(Node*& pt); // Левый поворот
    void rotateRight(Node*& pt); // Правый поворот
    void fixViolation(Node*& pt); // Исправление нарушений свойств красно-черного дерева
    Node* BSTInsert(Node* root, Node* pt); // Вставка узла в двоичное дерево поиска

public:
    RedBlackTree(); // Конструктор
    void insert(const int& data); // Метод вставки
    void inorder(); // Метод для обхода дерева
    void inorderHelper(Node* root); // Вспомогательный метод для обхода
};

#endif // RED_BLACK_TREE_H
