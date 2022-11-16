//
// Created by Марат Гасанов on 05.05.2022.
//
#include "iostream"
#include "stack"
using namespace std;

bool compare(int n1, int n2){
    return n1 < n2;
};

template<class T>
class BinaryTree{
private:
    struct Node{
        T key;
        Node* left;
        Node* right;
        Node* parent;
        int height;
        bool isLeaf;
        explicit Node(T key_):key(key_), left(nullptr), right(nullptr), parent(nullptr), height(1), isLeaf(true){};
    };
    Node* root;
    void nodeOut(Node* node);
    bool (*compare)(T , T );
    int minHeight(Node* node, int minHeigh);
    int minH;
public:
    explicit BinaryTree(bool (*compareFunc)(T , T ));
    void out();
    void add(int key);
    bool find(T t);
    int minHeight();
};

template<class T>
int BinaryTree<T>::minHeight(){
    if(root) {
        return minHeight(root, minH);
    }
    return 0;
}

template<class T>
int BinaryTree<T>::minHeight(Node* node, int minHeigh){
    if (node) {
        if (node->isLeaf && node->height < minHeigh) {
            minH = node->height;
        }
    }
    if (node->left) {
        return minHeight(node->left, minHeigh);
    }
    if (node->right) {
        return minHeight(node->right, minHeigh);
    }
    return minH;
}

template<class T>
void BinaryTree<T>::nodeOut(Node *node) {
    if (node == nullptr){
        return;
    }
    nodeOut(node->left);
    cout << node->key << " ";
    nodeOut(node->right);
}

template<class T>
void BinaryTree<T>::out() {
    nodeOut(root);
}

template<class T>
BinaryTree<T>::BinaryTree(bool (*compareFunc)(T , T )) {
    root = nullptr;
    compare = compareFunc;
}

template<class T>
void BinaryTree<T>::add(int key) {
    Node* addedNode = new Node(key);
    if (root == nullptr){
        root = addedNode;
        return;
    }
    Node* left = root->left;
    Node* right = root->right;
    Node* parent = root;
    int height = 1;
    while (true){
        if(compare(key , parent->key)){
            if (left){
                parent = left;
                left = parent->left;
                right = parent->right;
                height++;
            }
            else{
                addedNode->parent = parent;
                addedNode->height = ++height;
                parent->left = addedNode;
                parent->isLeaf = false;
                minH = height;
                break;
            }
        }
        else{
            if (right){
                parent = right;
                left = right->left;
                right = right->right;
                height++;
            }
            else{
                addedNode->parent = parent;
                addedNode->height = ++height;
                parent->right = addedNode;
                parent->isLeaf = false;
                minH = height;
                break;
            }
        }
    }
}

template<class T>
bool BinaryTree<T>::find(T t) {
    Node* current = root;
    while (current && current->key != t ){
        if(this->root == NULL){
            return false;
        }
        if (compare(t, root->key)){
            current = current->left;
        }
        else{
            current = current->right;
        }
    }
    if (current){
        return true;
    }
    return false;
}

int main(){
    int number;
    BinaryTree<int> bTree = BinaryTree<int>(compare);
    while (cin >> number){
        bTree.add(number);
    }
    cout << bTree.minHeight() << endl;
}




