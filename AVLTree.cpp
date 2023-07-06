#include <iostream>
#include "AVLTree.h"

// Function to create the new node in the tree
template <typename T>
Node<T>* AVL<T>::newNode(T data)
{
    Node<T>* newnode = new Node<T>();
    newnode->data = data;
    newnode->heigth = 1;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
}

// Function to search for a specific node in the tree
template <typename T>
Node<T>* AVL<T>::searchNode(Node<T>* node, T data)
{
    if(node == NULL)
        return NULL;
    else if(node->data == data)
        return node;
    else if(data < node->data)
        return searchNode(node->left, data);
    else
        return searchNode(node->right, data);
}

// Function to generally search for a node 
template <typename T>
bool AVL<T>::searchNode(T data)
{
    return (searchNode(root, data) == NULL) ? false : true;
}

// Function to left rotate a node if the tree is skew
template <typename T>
Node<T>* AVL<T>::leftRotate(Node<T>* x)
{
    // Check if the node is valid
    if(x == NULL)
        return NULL;

    Node<T>* y = x->right;
    // Assign x as the parent of the left child of y   
    x->right = y->left;
    y->left = x;

    // Update the height of the nodes
    x->heigth = max(getHeight(x->left), getHeight(x->right) + 1);
    y->heigth = max(getHeight(y->left), getHeight(y->right) + 1);
    return y;
}

// Function to right rotate the tree if it is skew
template <typename T>
Node<T>* AVL<T>::rightRotate(Node<T>* y)
{
    // Check if the node is valid
    if(y == NULL)
        return NULL;

    Node<T>* x = y->left;
    // Assign y as the parent of the right child of x
    y->left = x->right;
    x->right = y;

    // Update the hieght of the nodes
    y->heigth = max(getHeight(y->left), getHeight(y->right) + 1);
    x->heigth = max(getHeight(x->left), getHeight(x->right) + 1);
    return x;
}

// Function to return the larger value between 2 integers
template <typename T>
int AVL<T>::max(int a, int b)
{
    return (a > b) ? a : b;
}

// Function to get the height of the node
template <typename T>
int AVL<T>::getHeight(Node<T>* node)
{
    if(node == NULL)
        return 0;
    return node->heigth;
}

// Function to calculate the balance factor of a specific node
template <typename T>
int AVL<T>::balanceFactor(Node<T>* node)
{
    if(node == NULL)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// Function to insert new node into the tree
template <typename T>
Node<T>* AVL<T>::insertNode(Node<T>* node, T data)
{
    // If the tree is empty
    if(node == NULL)
        return newNode(data);
    // Insert the node to the tree in the correct order
    if(data < node->data)
        node->left = insertNode(node->left, data);
    else if(data > node->data)
        node->right = insertNode(node->right, data);
    else
        return node;

    // Update the height of the new node
    node->heigth = 1 + max(getHeight(node->left), getHeight(node->right));
    // Check the balance factor and reanrrange the tree if necessary
    int bfactor = balanceFactor(node);
    // Case more left skewed
    if(bfactor > 1)
    {
        if(data < node->left->data)
            return rightRotate(node);
        else if(data > node->left->data)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    // Case the tree is more right skewed
    if(bfactor < -1)
    {
        if(data > node->right->data)
            return leftRotate(node);
        else if(data < node->right->data)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

// Function to fully add the new node to the tree root
template <typename T>
void AVL<T>::insertNode(T data)
{
    root = insertNode(root, data);
}

// Function to get the inorder successor of the node
template <typename T>
Node<T>* AVL<T>::minSuccessor(Node<T>* node)
{
    if(node == NULL)
        return NULL;
    Node<T>* temp = node->right;
    while(temp->left != NULL)
        temp = temp->left;
    return temp;
}

// Function to delete the node in the tree
template <typename T>
Node<T>* AVL<T>::delNode(Node<T>* node, T data)
{
    // Check if the tree is empty
    if(node == NULL)
        return NULL;
    // Traverse to the node need to be deleted
    if(data < node->data)
        node->left = delNode(node->left, data);
    else if(data > node->data)
        node->right = delNode(node->right, data);
    else
    {
        // Check if the node is a leaf
        if(node->left == NULL || node->right == NULL)
        {
            Node<T>* temp = (node->left) ? node->left : node->right;
            if(temp == NULL)
            {
                temp = node;
                node = NULL;
            }else
                *node = *temp;
            delete temp;
        }
        else
        {
            Node<T>* temp = minSuccessor(node);
            node->data = temp->data;
            node->right = delNode(node->right, data);
        }
    }
    // Update the height of the node
    node->heigth = 1 + max(getHeight(node->left), getHeight(node->right));
    // Check the balance factor of the node and rearrange the key if necessary
    int bfactor = balanceFactor(node);
    // Case the tree is more right skewed
    if(bfactor > 1)
    {
        if(balanceFactor(node->left) >= 0)
            return rightRotate(node);
        else
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
    }
    // Case the tree is more left skewed
    else if(bfactor < -1)
    {
        if(balanceFactor(node->right) <= 0)
            return leftRotate(node);
        else 
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
    }
    return node;
}

// Function to fully delete the node from the root of the tree
template <typename T>
void AVL<T>::delNode(T data)
{
    root = delNode(root, data);
}

// Function to print the 2D shape of the tree
template <typename T>
void AVL<T>::print2D(Node<T>* node, int COUNT, int space)
{
    // Base case
    if (node == NULL)
        return;
    // Increase distance between levels
    space += COUNT;
    // Process right child first
    print2D(node->right, COUNT, space);
    // Print current node after space
    std::cout << std::endl;
    for (int i = COUNT; i < space; i++)
        std::cout << " ";
    std::cout << node->data << "\n";
    // Process left child
    print2D(node->left, COUNT, space);    
}

// Function th print the shape of the tree
template <typename T>
void AVL<T>::printTree()
{
    print2D(root, 10, 0);
}

// Function to get the node of the tree
template <typename T>
Node<T>* AVL<T>::getRoot()
{
    return root;
}

int main()
{
    // Initiate the AVL tree
    AVL<int> avltree;
    int random[] = {33, 0, 5, 7 ,3 ,2, 10, 16, 13, 28, 37, 65, 41, 26, 98, 100, 103, 77};
    // Insert node
    for(int i = 0; i < sizeof(random)/4; ++i)
        avltree.insertNode(random[i]);
    // Print the tree
    avltree.printTree();
    // Search for a few node
    std::cout<<"Node 13 is "<<(avltree.searchNode(13) ? "" : "not ")<<"in the tree"<<std::endl;
    std::cout<<"Node 20 is "<<(avltree.searchNode(20) ? "" : "not ")<<"in the tree"<<std::endl;
    // Delete some node
    avltree.delNode(98);
    avltree.delNode(65);
    // Display
    avltree.printTree();
    return 0;
}