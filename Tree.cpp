/*
 * Implements the Tree.h functions to create a balanced binary tree from
 * numbers found in scores.txt and whatever new score has been added
 */

/* 
 * File:   Tree.cpp
 * Author: Drew
 *
 * Created on December 16, 2017, 12:00 PM
 */

#include "Tree.h" 

//constructor takes all score saved in a file and stores them in tree then adds
//the new score to the tree
//and calls the print function to print using an inorder traversal of the tree
Tree::Tree(int key)
{
    int temp;
    fstream file;
    file.open("scores.txt", ios::out | ios::app);
    file << key << " ";
    file.close();
    file.open("scores.txt", ios::in);
    while(!file.eof()) 
    {
        file >> key;
        root = insert(root, key);
    }
    print();
}

//destructor does nothing
Tree::~Tree() 
{
    
}

//prints the values in the tree from lowest to highest using an inorder
//traversal
void Tree::print() 
{
    cout << "Your saved turn numbers are:\n";
    inOrder(root);
}

//prints values lowest to highest
void Tree::inOrder(Node* root) 
{
    if(root != NULL)
    {
        inOrder(root->left);
        cout << root->key << endl;
        inOrder(root->right);
    }
}

// A utility function to get height of the tree
int Tree::height(Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}
 
// A utility function to get maximum of two integers
int Tree::max(int a, int b)
{
    return (a > b)? a : b;
}
 
/* Helper function that allocates a new node with the given key and
    NULL left and right pointers. */
struct Tree::Node* Tree::newNode(int key)
{
    Node* node = (Node*)
                        malloc(sizeof(Node));
    node->key   = key;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1;  // new node is initially added at leaf
    return(node);
}
 
// A utility function to right rotate subtree rooted with y
// See the diagram given above.
struct Tree::Node* Tree::rightRotate(Node *y)
{
    Node *x = y->left;
    Node *T2 = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = T2;
 
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    // Return new root
    return x;
}
 
// A utility function to left rotate subtree rooted with x
// See the diagram given above.
struct Tree::Node* Tree::leftRotate(Node *x)
{
    Node *y = x->right;
    Node *T2 = y->left;
 
    // Perform rotation
    y->left = x;
    x->right = T2;
 
    //  Update heights
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
 
    // Return new root
    return y;
}
 
// Get Balance factor of node N
int Tree::getBalance(Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}
 
// Recursive function to insert key in subtree rooted
// with node and returns new root of subtree.
struct Tree::Node* Tree::insert(Node* node, int key)
{
    /* 1.  Perform the normal BST insertion */
    if (node == NULL)
        return(newNode(key));
 
    if (key < node->key)
        node->left  = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys are not allowed in BST
        return node;
 
    /* 2. Update height of this ancestor node */
    node->height = 1 + max(height(node->left),
                           height(node->right));
 
    /* 3. Get the balance factor of this ancestor
          node to check whether this node became
          unbalanced */
    int balance = getBalance(node);
 
    // If this node becomes unbalanced, then
    // there are 4 cases
 
    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
 
    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
 
    // Left Right Case
    if (balance > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
    // Right Left Case
    if (balance < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
}