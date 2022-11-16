//
// Created by Марат Гасанов on 13.05.2022.
//
#include "iostream"
#include "math.h"
using namespace std;

class AVLTree{
private:
    struct Node{
        int key;
        int height;
        Node* parent;
        Node* left;
        Node* right;
        Node(int key_): key(key_), left(nullptr), right(nullptr), parent(nullptr), height(1) {};
        int getBalance() const{
            int hLeft = this->left ? this->left->height : 0;
            int hRight = this->right ? this->right->height : 0;
            return hLeft - hRight;
        }
        void fixHeight(){
            int hLeft = this->left ? this->left->height : 0;
            int hRight = this->right ? this->right->height : 0;
            this->height = hLeft > hRight ? hLeft+1 : hRight+1;
        }
    };
    Node* root;
    void smallRight(Node* node);
    void bigRight(Node* node);
    void smallLeft(Node* node);
    void bigLeft(Node* node);
    void balance(Node* node);
public:
    explicit AVLTree(){
        root = nullptr;
    }
    void add(int t);
    bool find(int t);
    void erase(int t);
    bool next(int t);
    bool prev(int t);
};

void AVLTree::balance(AVLTree::Node *node) {
    node->fixHeight();
    if (node->getBalance() <= 2){
        if (node->right->height <= node->left->height){
            smallRight(node);
        }
        else{
            bigRight(node);
        }
    }
    else if(node->getBalance() <= -2){
        if (node->right->height <= node->left->height){
            smallLeft(node);
        }
        else{
            bigLeft(node);
        }
    }
}

void AVLTree::smallRight(Node* a) {
    Node* b = a->left;
    Node* L = b->left;
    Node* C = b->right;
    Node* R = root->right;
    root = b;
    root->right = a;
    root->left = L;
    root->right->left = C;
    root->right->right = R;
}

void AVLTree::smallLeft(Node* a) {
    Node* L = a->left;
    Node* b = a->right;
    Node* C = b->left;
    Node* R = b->right;
}

void AVLTree::bigRight(AVLTree::Node *node) {

}

void AVLTree::bigLeft(AVLTree::Node *node) {

}

void AVLTree::add(int t) {
    Node* addedNode = new Node(t);
    if (root == nullptr){
        root = addedNode;
        return;
    }
    Node* left = root->left;
    Node* right = root->right;
    Node* parent = root;
    while (true){
        if(t < parent->key){
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
    while (parent){
        parent->height++;
        balance(parent);
        parent = parent->parent;
    }
}

bool AVLTree::find(int t) {
    Node* current = root;
    while (current && current->key != t ){
        if(this->root == NULL){
            return false;
        }
        if (t < root->key){
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

void AVLTree::erase(int t) {

}

bool AVLTree::next(int t) {
    return false;
}

bool AVLTree::prev(int t) {
    return false;
}

int main(){
    int num;
    string operation;
    AVLTree avl;
    while(cin >> operation >> num){
        if(operation == "insert"){
            avl.add(num);
        }
        else if(operation == "exists"){
            if(avl.find(num)){
                cout << "true" << endl;
            }
            else{
                cout << "false" << endl;
            }
        }
        else if(operation == "delete"){
            avl.erase(num);
        }
        else if(operation == "prev"){
            cout << avl.prev(num) << endl;
        }
        else if(operation == "next"){
            cout << avl.next(num) << endl;
        }
    }
}

