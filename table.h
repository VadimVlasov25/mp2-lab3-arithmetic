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
    // ���������� �� ������ �������
};

class RBT : public Table {
    // ����������� ����
    Node::Node(int data) : data(data), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}

    // ����������� ������-������� ������
    RedBlackTree::RedBlackTree() : root(nullptr) {}

    // ����� �������
    void RedBlackTree::rotateLeft(Node*& pt) {
        Node* pt_y = pt->right; // ����, ������� ������ ����� ������ ���������
        pt->right = pt_y->left; // ��������� ����� ��������� pt_y � ������� ��������� pt

        if (pt_y->left != nullptr)
            pt_y->left->parent = pt;

        pt_y->parent = pt->parent;

        if (pt->parent == nullptr)
            root = pt_y; // ���� pt ��� ������, ��������� ������
        else if (pt == pt->parent->left)
            pt->parent->left = pt_y; // ���� pt ��� ����� �������� �����
        else
            pt->parent->right = pt_y; // ���� pt ��� ������ �������� �����

        pt_y->left = pt; // ���������� pt � ����� ��������� pt_y
        pt->parent = pt_y; // ��������� �������� pt
    }

    // ������ �������
    void RedBlackTree::rotateRight(Node*& pt) {
        Node* pt_y = pt->left; // ����, ������� ������ ����� ������ ���������
        pt->left = pt_y->right; // ��������� ������ ��������� pt_y � ������ ��������� pt

        if (pt_y->right != nullptr)
            pt_y->right->parent = pt;

        pt_y->parent = pt->parent;

        if (pt->parent == nullptr)
            root = pt_y; // ���� pt ��� ������, ��������� ������
        else if (pt == pt->parent->left)
            pt->parent->left = pt_y; // ���� pt ��� ����� �������� �����
        else
            pt->parent->right = pt_y; // ���� pt ��� ������ �������� �����

        pt_y->right = pt; // ���������� pt � ������ ��������� pt_y
        pt->parent = pt_y; // ��������� �������� pt
    }

    // ����������� ��������� ������� ������-������� ������
    void RedBlackTree::fixViolation(Node*& pt) {
        Node* parent_pt = nullptr;
        Node* grandparent_pt = nullptr;

        // ���� ������� ���� �� ������ � �������� �������
        while ((pt != root) && (pt->color == RED) && (pt->parent->color == RED)) {
            parent_pt = pt->parent;
            grandparent_pt = pt->parent->parent;

            // ������ A: �������� pt - ����� ������� ���� pt
            if (parent_pt == grandparent_pt->left) {
                Node* uncle_pt = grandparent_pt->right;

                // ������ 1: ���� pt ���� �������, ������ ��������������
                if (uncle_pt != nullptr && uncle_pt->color == RED) {
                    grandparent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grandparent_pt; // ��������� ����
                }
                else {
                    // ������ 2: pt - ������ ������� ������ ��������
                    if (pt == parent_pt->right) {
                        rotateLeft(parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    // ������ 3: pt - ����� ������� ������ ��������
                    rotateRight(grandparent_pt);
                    std::swap(parent_pt->color, grandparent_pt->color);
                    pt = parent_pt;
                }
            }
            else { // ������ B: �������� pt - ������ ������� ���� pt
                Node* uncle_pt = grandparent_pt->left;

                // ������ 1: ���� pt ���� �������, ������ ��������������
                if ((uncle_pt != nullptr) && (uncle_pt->color == RED)) {
                    grandparent_pt->color = RED;
                    parent_pt->color = BLACK;
                    uncle_pt->color = BLACK;
                    pt = grandparent_pt; // ��������� ����
                }
                else {
                    // ������ 2: pt - ����� ������� ������ ��������
                    if (pt == parent_pt->left) {
                        rotateRight(parent_pt);
                        pt = parent_pt;
                        parent_pt = pt->parent;
                    }

                    // ������ 3: pt - ������ ������� ������ ��������
                    rotateLeft(grandparent_pt);
                    std::swap(parent_pt->color, grandparent_pt->color);
                    pt = parent_pt;
                }
            }
        }
        root->color = BLACK; // ��������, ��� ������ ������
    }

    // ������� ������ ����
    Node* RedBlackTree::BSTInsert(Node* root, Node* pt) {
        // ���� ������ ������, ���������� ����� ����
        if (root == nullptr) {
            return pt;
        }

        // ��������� ���� � ��������������� ����� � ������
        if (pt->data < root->data) {
            root->left = BSTInsert(root->left, pt);
            root->left->parent = root;
        }
        else if (pt->data > root->data) {
            root->right;
            root->right = BSTInsert(root->right, pt);
            root->right->parent = root;
        }

        return root; // ���������� (������������) ���������
    }

    // ������� ������ ����
    void RedBlackTree::insert(const int& data) {
        Node* pt = new Node(data); // ������� ����� ����
        root = BSTInsert(root, pt); // ��������� ���� � �������� ������ ������
        fixViolation(pt); // ���������� ��������� ������� ������-������� ������
    }

    // ����� ������ � ������� �����������
    void RedBlackTree::inorderHelper(Node* root) {
        if (root == nullptr) return;

        inorderHelper(root->left); // ������� ����� ���������
        std::cout << root->data << " "; // ������� �������� ����
        inorderHelper(root->right); // ������� ������ ���������
    }

    // ����� ��� ������ ������
    void RedBlackTree::inorder() {
        inorderHelper(root); // �������� ����� � �����
    }

};

class HashT : public Table {
    // ���������� �� ������ ���-�������
};

#endif // TABLE_H
