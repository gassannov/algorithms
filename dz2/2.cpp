//
// Created by Марат Гасанов on 05.05.2022.
//
#include "iostream"
#include "stack"
using namespace std;

bool compare(const int& n1, const int& n2){
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
        explicit Node(int key_):key(key_), left(nullptr), right(nullptr), parent(nullptr){};
    };
    Node* root;
    bool (*compare)(const T& , const T& );
public:
    explicit BinaryTree(bool (*compareFunc)(const T& , const T& ));
    void add(int key);
};

template<class T>
BinaryTree<T>::BinaryTree(bool (*compareFunc)(const T& , const T& )) {
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
    while (true){
        if(compare(key , parent->key)){
            if (left){
                parent = left;
                left = parent->left;
                right = parent->right;
            }
            else{
                addedNode->parent = parent;
                parent->left = addedNode;
                break;
            }
        }
        else{
            if (right){
                parent = right;
                left = right->left;
                right = right->right;
            }
            else{
                addedNode->parent = parent;
                parent->right = addedNode;
                break;
            }
        }
    }
}

int main(){
    size_t numbersCnt;
    cin >> numbersCnt;
    BinaryTree<int> bTree = BinaryTree<int>(compare);
    for (int i = 0; i < numbersCnt; ++i) {
        int number;
        cin >> number;
        bTree.add(number);
    }
    bTree.out();
}





