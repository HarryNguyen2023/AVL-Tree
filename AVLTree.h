#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <fstream>
#include <string>

// Define s custom structure type
typedef struct Infor
{
    std::string name;
    std::string pass;
    int grade;

    public:
    // Function to overwrite the operator equal == for structure use
    bool operator==(const Infor& other)
    {
        return name == other.name && pass == other.pass && grade == other.grade;
    }

    // Function to overwrite the operator > for structure use
    bool operator>(const Infor& other)
    {
        return name > other.name;
    }

    // Function to overwrite the operator < for structure use
    bool operator<(const Infor& other)
    {
        return name < other.name;
    }
}Infor;

// Define the class for a node in the tree
template <class T>
class Node
{
    public:
    T data;
    int heigth;
    Node* left;
    Node* right;
};

// Define the general class of the AVL tree
template <class T>
class AVL:public Node<T>
{
    private:
        Node<T>* root = NULL;
        void print2D(Node<T>* node, int COUNT, int space);
        int balanceFactor(Node<T>* node);
        int max(int a, int b);
        int getHeight(Node<T>* node);
        Node<T>* minSuccessor(Node<T>* node);
        Node<T>* delNode(Node<T>* node, T data);
        Node<T>* leftRotate(Node<T>* node);
        Node<T>* rightRotate(Node<T>* node);
        Node<T>* newNode(T data);
        Node<T>* insertNode(Node<T>* node, T data);
        Node<T>* searchNode(Node<T>* node, T data);
        T findMax(Node<T>* node);
        int findSize(Node<T>* node);
        void inorderTraverse(Node<T>* node);
        void inorderSave(Node<T>* node, std::ofstream& infile);
        void preorderTraverse(Node<T>* node);
        void preorderSave(Node<T>* node, std::ofstream& prefile); 
        size_t fileSize(std::ifstream& file);
        T* readInFile(std::ifstream& infile);
        T* readPreFile(std::ifstream& prefile);
        int inorderIndex(T* indat, int start, int end, T data);
        Node<T>* rebuildTree(T* indat, T* predat, int start, int end);
    public:        
        void printTree();            
        void insertNode(T data);
        void delNode(T data);
        bool searchNode(T data);
        T findMax();
        int findSize();
        void printReverse();
        int getLevel();
        void printZigZag();
        void inorderTraverse();
        void preorderTraverse();
        bool treeSave();
        bool rebuildTree();
};

#endif