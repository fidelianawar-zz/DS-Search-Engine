#ifndef DSDSAVLTree_H
#define DSDSAVLTree_H
#include <stdexcept>
#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

template<class T>
class DSAVLTree{

private:

    template<class U>
    class AVLNode{
    public:
        U data;
        AVLNode * left;
        AVLNode * right;
        int height = 0;

        AVLNode(){
            left = nullptr;
            right = nullptr;
            height = 0;
        }
        AVLNode(U& newData):data(newData), left(nullptr), right(nullptr){
            height = 0;
        }
        AVLNode(U& newData,AVLNode *newLeft, AVLNode *newRight, int newHeight ){
            data = newData;
            left = newLeft;
            right = newRight;
            height = newHeight;
        }
        void operator = (AVLNode<U>& rhs) {
            data = rhs.data;
            if(rhs.left !=  nullptr){
                left = new AVLNode<U>();
                left = rhs.left;
            }
            else{
                left = nullptr;
            }
            if(rhs.right !=  nullptr){
                right = new AVLNode<U>();
                right = rhs.right;
            }
            else{
                right = nullptr;
            }
            height = rhs.height;
        }
    };

    AVLNode<T> *root;
    int totalNodes;

    int max(int, int);
    int height(AVLNode<T>*);
    void clean(AVLNode<T>*);
    void insert(T, AVLNode<T>*&);
    void printInOrder(AVLNode<T>*);
    bool contains(T, AVLNode<T>*);
    AVLNode<T>* copy(AVLNode<T>*&);
    void rotateLeftChild(AVLNode<T>*&);
    void rotateRightChild(AVLNode<T>*&);
    void doubleRotateRightChild(AVLNode<T>*&);
    void doubleRotateLeftChild( AVLNode<T>*&);
    void outputInOrder(AVLNode<T>*&, ostream&);
    T& find(T,  AVLNode<T>*);
    void countTotalNodes(AVLNode<T>* node);
    void parseInOrder(AVLNode<T>* node);
    vector<T> allNodes;
    ostream& createPersistent(AVLNode<T>* node);

public:
    DSAVLTree();
    DSAVLTree(T);
    DSAVLTree(DSAVLTree &rhs);
    ~DSAVLTree();
    DSAVLTree<T>& operator = (DSAVLTree<T>&);
    void clean();
    void insert(T);
    void printInOrder();
    void countTotalNodes();
    bool isEmpty();
    bool contains(T);
    T& find(T);
    void outputInOrder(ostream&);
    int getTotalNodes();
    void parseInOrder();
    vector<T> getAllNodes();
    void createPersistent();

};

template<class T>
void DSAVLTree<T>::createPersistent(){
    createPersistent(root);
}

template<class T>
ostream& DSAVLTree<T>::createPersistent(AVLNode<T>* node){
    ofstream output("indexCorpus.txt");

    if(!output.is_open()){
        cout << "Could Not Open Persistent Index" << endl;
    }

    if(node != nullptr){
        createPersistent(node->left);
        output << node->data<<" "<<endl;
        createPersistent(node->right);
    }

    if (isEmpty() == true) {
        cout << "tree is empty";
    }

}

template<class T>
DSAVLTree<T>::DSAVLTree(){
    root = nullptr;
}
template<class T>
void DSAVLTree<T>:: outputInOrder(ostream& output)
{
    outputInOrder(root, output);
}
template<class T>
DSAVLTree<T>::DSAVLTree(DSAVLTree<T>& rhs){
    root = nullptr;
    if(this  !=  &rhs)
    {
        clean();
        root = copy(rhs.root);
    }
}

template<class T>
DSAVLTree<T>::DSAVLTree(T data){
    root = nullptr;
    insert(data);
}

template<class T>
DSAVLTree<T>::~DSAVLTree()
{
    clean();
}

template<class T>
DSAVLTree<T>& DSAVLTree<T>::operator = (DSAVLTree<T>& rhs)
{
    if(this  !=  &rhs)
    {
        clean();
        root = copy(rhs.root);
    }
    return *this;
}

template<typename T>
typename DSAVLTree<T>::template AVLNode<T>* DSAVLTree<T>::copy(AVLNode<T>*& node)
{
    if(node!=nullptr){
        AVLNode<T>* zleft = copy( node->left );
        AVLNode<T>* zright = copy( node->right );
        return new  AVLNode<T>(node->data, zleft, zright, node->height);
    }
    else if(node==nullptr)
    {
        return nullptr;
    }
}

template<class T>
T& DSAVLTree<T>::find(T data)
{
    return find(data, root);
}

template<class T>
T& DSAVLTree<T>::find(T data, AVLNode<T>* node)
{
    while(node  !=  nullptr){
        if(data < node->data)
            node = node->left;
        else if(node->data < data)
            node = node->right;
        else
            return node->data;
    }
    throw out_of_range("Element requested is not in Tree");
}

template<class T>
void DSAVLTree<T>::clean()
{
    clean(root);
}

template<class T>
void DSAVLTree<T>::clean(AVLNode<T>* node)
{

    if(node  !=  nullptr)
    {
        AVLNode<T> * cur;
        if(node->left  !=  nullptr){
            clean(node->left);
        }
        if(node->right  !=  nullptr){
            clean(node->right);
        }
        cur = node;
        delete node;
    }
    node = nullptr;
}
template<class T>
bool DSAVLTree<T>::isEmpty()
{
    if(root == nullptr)
    {
        return true;
    }
    else
        return false;
}

template<class T>
void DSAVLTree<T>::insert(T x)
{
    totalNodes++;
    insert(x,root);
}

template<class T>
bool DSAVLTree<T>::contains(T data)
{
    return contains(data, root);
}

template<class T>
bool DSAVLTree<T>::contains(T data, AVLNode<T>* node)
{
    while(node  !=  nullptr)
        if(data < node->data)
            node = node->left;
        else if(node->data < data)
            node = node->right;
        else
            return true;
    return false;
}

template<class T>
int DSAVLTree<T>::height(AVLNode<T> *node)
{
    return node == nullptr? -1 : node->height;
}

template<class T>
int DSAVLTree<T>::max(int leftSide, int rightSide)
{
    return leftSide > rightSide? leftSide : rightSide;
}

template<class T>
void DSAVLTree<T>::printInOrder()
{
    printInOrder(root);
}
template<class T>
void DSAVLTree<T>::printInOrder(AVLNode<T>* node)
{
    if(node != nullptr){
        printInOrder(node->left);
        cout<<node->data<<" "<<endl;
        printInOrder(node->right);
    }

    if (isEmpty() == true) {
        cout << "tree is empty";
    }
}
template<class T>
void DSAVLTree<T>::parseInOrder()
{
    parseInOrder(root);
}
template<class T>
vector<T> DSAVLTree<T>::getAllNodes()
{
    return allNodes;
}
template<class T>
void DSAVLTree<T>::parseInOrder(AVLNode<T>* node)
{
    if(node != nullptr){
        parseInOrder(node->left);
        //cout<<node->data<<" "<<endl;
        allNodes.push_back(node->data);
        parseInOrder(node->right);
    }

    if (isEmpty() == true) {
        cout << "tree is empty";
    }
}
template<class T>
void DSAVLTree<T>::countTotalNodes()
{
    countTotalNodes(root);
}
template<class T>
void DSAVLTree<T>::countTotalNodes(AVLNode<T>* node)
{
    AVLNode<T>* temp = node;
//    if(node != nullptr){
//        countTotalNodes(node->left,totalNodes++);
//        countTotalNodes(node->right,totalNodes++);
//    }
    while(node != nullptr){
        node = node->left;
        totalNodes++;
    }
    while(temp != nullptr){
        temp = temp->right;
        totalNodes++;
    }

    if (isEmpty() == true) {
        cout << "tree is empty";
    }
}
template<class T>
int DSAVLTree<T>::getTotalNodes()
{
    return totalNodes;
}
template<class T>
void DSAVLTree<T>:: outputInOrder(AVLNode<T>*& node, ostream& output)
{
    if(node != nullptr){
        outputInOrder(node->left, output);
        output<<node->data;
        outputInOrder(node->right, output);
    }
}


template<class T>
void DSAVLTree<T>::insert(T newData, AVLNode<T>*& node)
{

    if( node == nullptr ){
        node = new AVLNode<T>(newData);
    }
    else if(newData < node->data)
    {
        insert(newData, node->left);

        if( height(node->left) - height(node->right) == 2 ){
            if(newData < node->left->data){
                rotateLeftChild(node);
            }
            else
                doubleRotateLeftChild(node);
        }
    }

    else if(node->data < newData)
    {
        insert(newData, node->right);
        if( height(node->right) - height(node->left) == 2 ){
            if(node->right->data < newData){
                rotateRightChild(node);
            }
            else
                doubleRotateRightChild(node);
        }
    }
    node->height = max( height( node->left ), height( node->right ) ) + 1;
}


template<class T>
void DSAVLTree<T>::rotateLeftChild(AVLNode<T>*& node1)
{
    AVLNode<T> *node2 = node1->left;

    node1->left = node2->right;
    node2->right = node1;

    node1->height = max(height( node1->left), height(node1->right)) + 1;
    node2->height = max(height( node2->left), node1->height) + 1;

    node1 = node2;
}

template<class T>
void DSAVLTree<T>::rotateRightChild(AVLNode<T>*& node1)
{
    AVLNode<T> *node2 = node1->right;

    node1->right = node2->left;
    node2->left = node1;

    node1->height = max(height(node1->left), height( node1->right)) + 1;
    node2->height = max(height(node2->right), node1->height) + 1;

    node1 = node2;
}

template<class T>
void DSAVLTree<T>::doubleRotateRightChild(AVLNode<T>*& node1)
{
    rotateLeftChild( node1->right );
    rotateRightChild( node1 );
}

template<class T>
void DSAVLTree<T>::doubleRotateLeftChild( AVLNode<T>*& node2 )
{
    rotateRightChild(node2->left);
    rotateLeftChild(node2);
}

#endif // DSDSAVLTree_H
