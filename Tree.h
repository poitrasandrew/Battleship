/*
 * Tree.h file specifies the Tree class and implements balanced binary tree
 * through use of private functions
 */

/* 
 * File:   Tree.h
 * Author: Drew
 *
 * Created on December 16, 2017, 12:00 PM
 */
#include <fstream>
#include <iostream>

using namespace std;

#ifndef TREE_H
#define TREE_H

class Tree {
private:
    struct Node
    {
        int key;//holds value for node
        struct Node *left;//holds left node
        struct Node *right;//holds right node
        int height;//used to find height of tree for balancing
    };
    Node* root = NULL;//holds the root of the tree
    int height(Node *N);
    int max(int a, int b);
    struct Node* newNode(int);
    struct Node* rightRotate(Node*);
    struct Node* leftRotate(Node*);
    int getBalance(Node*);
    struct Node* insert(Node*, int);
public:
    Tree(int);
    ~Tree();
    void print();
    void inOrder(Node*);
};

#endif /* TREE_H */