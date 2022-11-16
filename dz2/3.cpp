//
// Created by Марат Гасанов on 13.05.2022.
//
#include "iostream"
#include "math.h"
#include "vector"
using namespace std;

bool compare(const int& n1, const int& n2){
    return n1 < n2;
};

template <class T>
class BTree{
private:
    int degree;
    struct Node{
        vector<T> keys;
        vector<Node*> descendants;
        Node* parent;
        bool isLeaf;
        bool isRoot;
        bool (*compare)(const T&, const T&);

        Node(bool (*compare)(const T&, const T&)):isRoot(true), isLeaf(true), compare(compare), keys({}), descendants({}){};
        int findPlace(T t, int begin, int end){
             int middle = (begin + end) / 2;
             if (abs(end - begin) <= 1){
                 if (end == begin){
                     return end;
                 }
                 if (compare(keys[begin], t)){
                     return end;
                 }
                 else{
                     return begin;
                 }
             }
             if (compare(t, keys[middle])){
                 return findPlace(t, begin, middle);
             }
             else{
                 return findPlace(t, middle, end);
             }
        };

        int addToNode(T t){
            //cout << findPlace(t, 0, keys.size()) << endl;
            int index = findPlace(t, 0, keys.size());
            //cout << index << endl;
            keys.insert(keys.begin() + index, t);
            return index;
        }

        Node* partition(){
            int middle = keys.size()/2;
            vector<T> leftKeys(keys.begin(), keys.begin() + middle);
            vector<T> rightKeys(keys.begin() + middle+1, keys.begin() + keys.size());

            Node* node1 = new Node(compare);
            node1->keys = leftKeys;
            node1->isRoot = false;
            node1->isLeaf = this->isLeaf;

            Node* node2 = new Node(compare);
            node2->keys = rightKeys;
            node2->isRoot = false;
            node2->isLeaf = this->isLeaf;

            if (descendants.size() >= middle){
                vector<Node*> leftDescendants(descendants.begin(), descendants.begin() + middle+1);
                vector<Node*> rightDescendatnts(descendants.begin() + middle+1,descendants.begin()+ descendants.size());
                node1->descendants = leftDescendants;
                node2->descendants = rightDescendatnts;
                for(Node* descendant: leftDescendants){
                    descendant->parent = node1;
                }
                for(Node* descendant: rightDescendatnts){
                    descendant->parent = node2;
                }
            }
            else{
                node1->descendants = descendants;
                for(Node* descendant: descendants){
                    descendant->parent = node1;
                }
            }

            if (parent){
                int index = parent->addToNode(keys[middle]);
                parent->descendants.erase(parent->descendants.begin() + index);
                parent->descendants.insert(parent->descendants.begin() + index, node1);
                parent->descendants.insert(parent->descendants.begin()+index+1, node2);
                node1->parent = parent;
                node2->parent = parent;
            }
            else{
                Node* nodeParent = new Node(compare);
                nodeParent->isRoot = true;
                nodeParent->isLeaf = false;
                nodeParent->keys = {keys[middle]};
                nodeParent->descendants = {node1, node2};
                nodeParent->isRoot = true;
                node1->parent = nodeParent;
                node2->parent = nodeParent;
            }
            Node* parent_ = node1->parent;
            delete this;
            return parent_;
        }
        bool isFull(int degre){
            if (keys.size() >= degre*2-1){
                return true;
            }
            return false;
        }
    };
    Node* root;
    bool (*compare)(const T&, const T&);
    void out(vector<Node*> level);
public:
    BTree(bool (*compareFunc)(const T&, const T&), int degree);
    bool find(T t);
    bool insert(T t);
    void out();
};

template<class T>
bool BTree<T>::find(T t) {
    Node* current = root;
    while (current) {
        for (int i = 0; i < current->keys.size(); i++) {
            if (compare(t, current->keys[i])){
                for (int j = 0; j < current->descendants[i]->keys.size(); ++j) {
                    if (current->descendants[i]->keys[j] == t){
                        return true;
                    }
                }
                current = current->descendants[i];
            }
            else if(t == current->keys[i]){
                return true;
            }
        }
        for (int j = 0; j < current->descendants[current->keys.size()+1]->keys.size(); ++j) {
            if (current->descendants[current->keys.size()+1]->keys[j] == t){
                return true;
            }
        }
        current = current->descendants[current->keys.size()+1];
    }
    return false;
}

template<class T>
bool BTree<T>::insert(T t) {
    Node* current = root;
    while(current){
        if (current->isFull(degree)){
            current = current->partition();
            if (current->isRoot){
                root = current;
            }
        }
        if (current->isLeaf){
            current->addToNode(t);
            return true;
        }
        int index = current->findPlace(t, 0, current->keys.size());
        current = current->descendants[index];
    }
    return false;
}

template<class T>
BTree<T>::BTree(bool (*compareFunc)(const T&, const T&), int degree) {
    this->compare = compareFunc;
    this->degree = degree;
    root = new Node(compare);
}

int main(){
    int degree, num;
    cin >> degree;
    BTree<int> btree = BTree<int>(compare, degree);

    while(cin >> num){
        btree.insert(num);
    }

    return 0;
}