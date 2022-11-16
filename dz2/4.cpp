//
// Created by Марат Гасанов on 13.05.2022.
//
#include "iostream"
using namespace std;
#include "vector"
#include <cassert>

struct Node{
    /*T*/int key;
    int height;
    int size;
    Node* left;
    Node* right;
    explicit Node(/*T*/ int key_): key(key_), left(nullptr), right(nullptr), height(1), size(1) {};

    static int getSize(Node* node){
        int size = (node? node->size : 0);
        return size;
    }

    static int fixHeight(Node* node){
        int hLeft = (node->left ? fixHeight(node->left) : 0);
        int hRight = (node->right ? fixHeight(node->right) : 0);
        int height = (hLeft > hRight ? hLeft : hRight)+1;
        node->height = height;
        return height;
    }

    static int fixSize(Node* node){
        int sLeft = (node->left ? fixSize(node->left) : 0);
        int sRight = (node->right ? fixSize(node->right) : 0);
        int size = (sLeft + sRight)+1;
        node->size = size;
        return size;
    }

    static int fixNode(Node* node){
        fixHeight(node);
        fixSize(node);
    }

    int getBalance() const{
        int hLeft = this->left ? this->left->height : 0;
        int hRight = this->right ? this->right->height : 0;
        return hRight - hLeft;
    }
};

class AVLTree{
private:
    Node* root;
    //bool (*compare)(T , T );
    Node* rightRotate(Node* node);
    Node* leftRotate(Node* a);
    Node* balance(Node *node);
    Node* removeMin(Node *node);
    Node* erase(Node* root, int key);
    Node* add(Node* root, int key);
    int indexOf(Node *node, int key, int kth) const;
public:
    explicit AVLTree(){
        root = nullptr;
    }
    int add(int key);
    Node* erase(int index);
    int indexOf(int key);
};

Node* AVLTree::balance(Node *node) {
    Node::fixNode(node);
    switch (node->getBalance()){
        case 2:
            if (node->right->getBalance() < 0)
                node->right = rightRotate(node->right);
            return leftRotate(node);

        case -2:
            if (node->left->getBalance() > 0)
                node->left = leftRotate(node->left);
            return rightRotate(node);

        default:
            return node;
    }
}

Node* AVLTree::rightRotate(Node *node) {
    Node* tmp = node->left;
    node->left = tmp->right;
    tmp->right = node;
    Node::fixNode(node);
    Node::fixNode(tmp);
    return tmp;
}

Node* AVLTree::leftRotate(Node *node) {
    Node* tmp = node->right;
    node->right = tmp->left;
    tmp->left = node;
    Node::fixNode(node);
    Node::fixNode(tmp);
    return tmp;
}

int AVLTree::add(int key) {
    root = add(root, key);
}

Node* AVLTree::add(Node* root, int key) {
    if (!root){
        Node* node = new Node(key);
        return node;
    }
    else if (root->key > key){
        //index += Node::getSize(root->left->right);
        root->left = add(root->left, key);
    }
    else{
        //index = Node::getSize(root->right->right);
        root->right = add(root->right, key);
    }
    return balance(root);
}

Node *AVLTree::erase(int index) {
    root = erase(root, index);
}

Node* AVLTree::erase(Node* node, int index) {
    if (!node)
        return nullptr;
    int rSize = Node::getSize(node->right);
    int delta = index - rSize;
    if(delta == 0) {
        Node *left = node->left;
        Node *right = node->right;
        delete node;
        if (!right)
            return left;
        Node* rightMin = right;
        while (rightMin->left){rightMin = rightMin->left;}

        rightMin->right = removeMin(right);
        rightMin->left = left;
        return balance(rightMin);
        //return node;
    }
    else if(delta < 0) {
        node->right = erase(node->right, index);
        //return elementAt(node->right, index);
    }
    else{
        node->left = erase(node->left, delta - 1);
//        return elementAt(node->right, delta -1);
    }
    return balance(node);
}

Node* AVLTree::removeMin(Node *node) {
    if (!node->left)
        return node->right;
    node->left = removeMin(node->left);
    return balance(node);
}

int AVLTree::indexOf(int key) {
    //Node* node = _find(root, key);
    return indexOf(root, key, 0);
}

int AVLTree::indexOf(Node* node, int key, int index) const {
    if ( !node ){
        return 0;
    }
    if (node->key > key){
        index += Node::getSize(node->right);
        return indexOf(node->left, key, ++index);
    }
    else if (node->key < key){
        return indexOf(node->right, key, index);
    }
    index += Node::getSize(node->right);
    return index;
}

void test(AVLTree avl){
    int num, type, answer;
    vector<int> types =  {1,   1,  1,  2, 1,  1,   2, 1,  1,  2, 1};
    vector<int> nums =   {100, 23, 76, 2, 45, 190, 3, 22, 98, 1, 45};
    vector<int> answers= {0,   1,  1, -1, 2,  0,  -1, 3,  2, -1, 3};
    for (int i = 0; i < types.size(); ++i) {
        type = types[i];
        num = nums[i];
        answer = answers[i];
        if (type == 1){
            //cout << "Size " << types.size() << " " << i << " - " << num;
            avl.add(num);
            int index = avl.indexOf(num);
            assert(index == answer);
            //cout << " -- correct; " << index << " == " << answer << endl;
        }
        else if(type == 2){
            avl.erase(num);
        }
    }
}

int main(){
    AVLTree avl = AVLTree();
    int numOfCommands, num, type;
    cin >> numOfCommands;
    for (int i = 0; i < numOfCommands; ++i) {
        cin >>type >> num;
        if (type == 1){
            avl.add(num);
            cout << avl.indexOf(num) << endl;
        }
        else if(type == 2){
            avl.erase(num);
        }
    }
    return 0;
    test(avl);
}

