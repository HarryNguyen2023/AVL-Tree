#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
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
    if(node == NULL)
        return NULL;
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

// Function to find the maximum element in the tree
template <typename T>
T AVL<T>::findMax(Node<T>* node)
{
    // Check if the tree is empty
    if(node->right == NULL)
        return node->data;    
    return findMax(node->right);
}

// General function to find the maximum value element in the tree
template <typename T>
T AVL<T>::findMax()
{
    return findMax(root);
}

// Function th print the shape of the tree
template <typename T>
void AVL<T>::printTree()
{
    print2D(root, 10, 0);
}

// Function to find the size of the binary tree
template <typename T>
int AVL<T>::findSize(Node<T>* node)
{
    // Check if the tree is empty
    if(node == NULL)
        return 0;
    return findSize(node->left) + 1 + findSize(node->right);
}

// General function to find the size of the tree
template <typename T>
int AVL<T>::findSize()
{
    return findSize(root);
}

// Function to print the tree in reverse order
template <typename T>
void AVL<T>::printReverse()
{
    std::queue<Node<T>*> myq;
    std::stack<T> mystack;
    Node<T>* temp;
    // Enqueue the root node into the queue
    myq.push(root);
    // Loop through the tree and push them into the queue as well as the stack
    while(! myq.empty())
    {
        temp = myq.front();
        myq.pop();
        // Push the right item into the queue first
        if(temp->right != NULL)
            myq.push(temp->right);
        if(temp->left != NULL)
            myq.push(temp->left);
        // Push the data of the node into the stack
        mystack.push(temp->data);
    }
    std::cout<<"Element in reverse order: ";
    // Print the element in reverse order from the stack
    while(! mystack.empty())
    {
        std::cout<<mystack.top()<<" ";
        mystack.pop();
    }
    std::cout<<std::endl;   
}

// Function to get the number of the level of the tree
template<typename T>
int AVL<T>::getLevel()
{
    int level = 0;
    // Initiate the queue
    std::queue<Node<T>*> myqueue;
    Node<T>* temp;
    // Push the root and the first seperated layer
    myqueue.push(root);
    myqueue.push(NULL);
    // Loop
    while(! myqueue.empty())
    {
        // Get the front of the queue
        temp = myqueue.front();
        myqueue.pop();
        // Check the seperated layer
        if(temp == NULL)
        {
            if(! myqueue.empty())
                myqueue.push(NULL);
            level++;
        }
        else
        {
            if(temp->left != NULL)
                myqueue.push(temp->left);
            if(temp->right != NULL)
                myqueue.push(temp->right);
        }
    }
    return level;
}

// Function to print the tree in zig zag order
template <typename T>
void AVL<T>::printZigZag()
{
    bool l2r = false;
    // Initiate the queue
    std::stack<Node<T>*> currentstack;
    std::stack<Node<T>*> nextstack;
    Node<T>* temp = NULL;
    // Push the root into the queue
    currentstack.push(root);
    std::cout<<"Elements of the tree in zig zag order: ";
    // Loop
    while(!currentstack.empty())
    {
        temp = currentstack.top();
        currentstack.pop();
        // Case end of one level
        if(temp != NULL)
        {
            std::cout<<temp->data<<" ";
            if(l2r)
            {
                if(temp->left != NULL) 
                    nextstack.push(temp->left);
                if(temp->right != NULL)
                    nextstack.push(temp->right);
            }
            else
            {
                if(temp->right != NULL)
                    nextstack.push(temp->right);
                if(temp->left != NULL) 
                    nextstack.push(temp->left);               
            }
        }
        // Change the order and swap the pointer position 
        if(currentstack.empty())
        {
            l2r = ~l2r;
            currentstack.swap(nextstack);
        }
    }
    std::cout<<std::endl;
}

// Function to traverse the tree in inorder
template <typename T>
void AVL<T>::inorderTraverse(Node<T>* node)
{
    if(node == NULL)
        return;
    inorderTraverse(node->left);
    std::cout<<node->data<<" ";
    inorderTraverse(node->right);
}

// Function to generally traverse the tree in inorder
template <typename T>
void AVL<T>::inorderTraverse()
{
    std::cout<<"Element in the inorder: ";
    inorderTraverse(root);
    std::cout<<std::endl;
}

// Function to traverse the tree in preorder
template <typename T>
void AVL<T>::preorderTraverse(Node<T>* node)
{
    if(node == NULL)
        return;
    std::cout<<node->data<<" ";
    inorderTraverse(node->left);
    inorderTraverse(node->right);
}

// Function to generally traverse the tree in inorder
template <typename T>
void AVL<T>::preorderTraverse()
{
    std::cout<<"Element in the preorder: ";
    preorderTraverse(root);
    std::cout<<std::endl;
}

// Function to save the tree in the inorder
template <typename T>
void AVL<T>::inorderSave(Node<T>* node, std::ofstream& infile)
{
    if(node == NULL)
        return;
    if(node->left != NULL)
        inorderSave(node->left, infile);
    infile.write((char*)&(node->data), sizeof(T));
    if(node->right != NULL)
        inorderSave(node->right, infile);
    if(! infile.good())
    {
        std::cout<<"ERROR: unable to write the inorder file"<<std::endl;
        exit(1);
    }
}

// Function to save the tree in the preorder
template <typename T>
void AVL<T>::preorderSave(Node<T>* node, std::ofstream& prefile)
{
    if(node == NULL)
        return;
    prefile.write((char*)&(node->data), sizeof(T));
    if(node->left != NULL)
        preorderSave(node->left, prefile);
    if(node->right != NULL)
        preorderSave(node->right, prefile);
    if(! prefile.good())
    {
        std::cout<<"ERROR: unable to write the preorder file"<<std::endl;
        exit(1);
    }
}

// Function to generally save the tree into the file
template <typename T>
bool AVL<T>::treeSave()
{
    // Initiate 2 files to save the tree
    std::ofstream infile("indata.dat", std::ios::out | std::ios:: binary);
    std::ofstream prefile("predata.dat", std::ios::out | std::ios::binary);
    // Check if both file is open
    if(!infile.is_open() || !prefile.is_open())
        return false;
    // Save the tree in 2 different orders
    inorderSave(root, infile);
    infile.close();
    preorderSave(root, prefile);
    prefile.close();
    return true;
}

// Function to get the size of a file
template <typename T>
size_t AVL<T>::fileSize(std::ifstream& file)
{
    file.seekg(0, std::ios::end);
    return file.tellg();
}

// Function to read the inorder file 
template <typename T>
T* AVL<T>::readInFile(std::ifstream& infile)
{
    // Get the size of the file to determine the length of the arrary
    int size = 0;
    int len = fileSize(infile)/sizeof(T);
    // Create dynamic array
    T* indat = new T[len];
    // Move the pointer to the beggining of the 2 file
    infile.seekg(0, std::ios::beg);
    // Read the inorder file
    while(infile.read((char*)(indat + size), sizeof(T)))
        size++;
    infile.close();
    return indat;
}

// Function to read the preorer file
template <typename T>
T* AVL<T>::readPreFile(std::ifstream& prefile)
{
    // Get the size of the file to determine the length of the arrary
    int size = 0;
    int len = fileSize(prefile)/sizeof(T);
    // Create dynamic array
    T* predat = new T[len];
    // Move the pointer to the beggining of the 2 file
    prefile.seekg(0, std::ios::beg);
    // Read the preorder file
    while(prefile.read((char*)(predat + size), sizeof(T)))
        size++;
    prefile.close();
    return predat;
}

// Function to rebuild the tree from the inorder and preorder array of the tree
template <typename T>
bool AVL<T>::rebuildTree()
{
    // Initiate the streams to read the saved files
    std::ifstream infile("indata.dat", std::ios::in | std::ios::binary);
    std::ifstream prefile("predata.dat", std::ios::in | std::ios::binary);
    // Check if the file is ready to be read
    if(!infile.is_open() || !prefile.is_open())
    {
        std::cout<<"ERROR: unable to read to file"<<std::endl;
        return false;
    }       
    // Initiate 2 array pointer
    T* indat = readInFile(infile);
    T* predat = readPreFile(prefile);


    // Delete 2 dynamic arrays
    delete indat;
    delete predat;
    return true;
}

int main()
{
    // Initiate the AVL tree
    AVL<int> avltree;
    int random[] = {33, 0, 5, 7 ,3 ,2, 10, 16, 13, 28, 330, 37, 65, 41, 26, 98, 100, 103, 77};
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
    // Display the maximum value in the tree
    std::cout<<"The maximum value in the tree is: "<<avltree.findMax()<<std::endl;
    std::cout<<"The size of the tree is: "<<avltree.findSize()<<std::endl;
    avltree.printReverse();
    std::cout<<"The level of the tree is: "<<avltree.getLevel()<<std::endl;
    avltree.printZigZag();
    avltree.inorderTraverse();
    avltree.preorderTraverse();
    std::cout<<"Save the tree "<<(avltree.treeSave() ? "SUCCESSED" : "FAILED")<<std::endl;
    avltree.rebuildTree();
    // String version
    // AVL<std::string> avltree;
    // //int random[] = {33, 0, 5, 7 ,3 ,2, 10, 16, 13, 28, 37, 65, 41, 26, 98, 100, 103, 77};
    // std::vector<std::string> str_vect = {"Gia", "Tran", "Phu", "Chau", "Thomas", "Kevin", "Khoa", "Nick", "Duy"};
    // // Insert node
    // for(int i = 0; i < str_vect.size(); ++i)
    //     avltree.insertNode(str_vect[i]);
    // // Print the tree
    // avltree.printTree();
    // // Search for a few node
    // std::cout<<"Node Gia is "<<(avltree.searchNode("Gia") ? "" : "not ")<<"in the tree"<<std::endl;
    // std::cout<<"Node Tran is "<<(avltree.searchNode("Tran") ? "" : "not ")<<"in the tree"<<std::endl;
    // // Delete some node
    // avltree.delNode("Kevin");
    // avltree.delNode("Nick");
    // // Display
    // avltree.printTree();

    return 0;
}