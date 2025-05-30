#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include <iostream>

enum Color { RED, BLACK }; // ���������� ����� �����

// ��������� ���� ������
struct Node {
    int data; // �������� ����
    Color color; // ���� ����
    Node* left, * right, * parent; // ��������� �� �������� � ������������ ����

    Node(int data);
};

// ����� ������-������� ������
class RedBlackTree {
private:
    Node* root; // ������ ������

    void rotateLeft(Node*& pt); // ����� �������
    void rotateRight(Node*& pt); // ������ �������
    void fixViolation(Node*& pt); // ����������� ��������� ������� ������-������� ������
    Node* BSTInsert(Node* root, Node* pt); // ������� ���� � �������� ������ ������

public:
    RedBlackTree(); // �����������
    void insert(const int& data); // ����� �������
    void inorder(); // ����� ��� ������ ������
    void inorderHelper(Node* root); // ��������������� ����� ��� ������
};

#endif // RED_BLACK_TREE_H
