#pragma once

#include <iostream>
#include <queue>

enum Color {
    Red, Black
};

struct Node {
    Node* left = nullptr;
    Node* right = nullptr;
    Node* parent = nullptr;
    int val;
    Color color = Black;

    Node() {}
    Node(const int& value) : val(value) {}
    ~Node() {}
};

class RedBlackTree {
public:    
    RedBlackTree();
    ~RedBlackTree();

    void insert(const int& val);
    void deleteNode(const int& val);
    bool search(const int& val);
    void printTree();

private:
    void levelOrder(Node* node);
    void rightRotation(Node* node);
    void leftRotation(Node* node);
    void insertFixup(Node* node);
    void clearTree(Node* node);
    Node* getMin(Node* node);
    void transplant(Node* u, Node* v);
    void deleteFixUp(Node* node);
    Node* searchHelper(Node* node, const int& val);
private:
    Node* nil = new Node();
    Node* root = nil;
};