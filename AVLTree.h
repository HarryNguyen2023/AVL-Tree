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
    public:        
        void printTree();            
        void insertNode(T data);
        void delNode(T data);
        bool searchNode(T data);
        T findMax();
        int findSize();
};