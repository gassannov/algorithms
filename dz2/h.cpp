//
// Created by Марат Гасанов on 20.05.2022.
//
#include <iostream>
#include <vector>

using namespace std;

const size_t INITIAL_CAPACITY = 8;
const double RESIZECOEF = 0.75;


int gorner(const string& str){
    int hash = 0;
    for (char c: str) {
        hash = 71*hash + c;
    }
    return hash;
}

template<class T>
class HashTable {
private:
    size_t realTableSize;
    vector<T *> table;

    void rehash();

public:
    bool add(T key);
    bool remove(T value);
    bool search(T value);
    HashTable(size_t initial_capacity = INITIAL_CAPACITY) : table(initial_capacity, nullptr), realTableSize(0) {}
};

template<class T>
void HashTable<T>::rehash() {
    vector<T *> newTable(table.size() * 2);
    size_t newSize = 0;
    for (int i = 0; i < table.size(); ++i)
        if ((table[i] != nullptr) && (*table[i] != "DELETED")) {
            size_t hash = gorner(*table[i]) % newTable.size();
            for (int j = 0;; ++j) {
                hash = (hash + j) % newTable.size();
                if (newTable[hash] == nullptr) {
                    ++newSize;
                    newTable[hash] = table[i];
                    break;
                }
            }
        }
    table = newTable;
    realTableSize = newSize;
}

template<class T>
bool HashTable<T>::search(T value) {
    size_t hash = gorner(value) % table.size();
    for (int i = 0;; ++i) {
        hash = (hash + i) % table.size();
        if (table[hash] == nullptr)
            return false;
        if (*table[hash] == value) {
            return true;
        }
    }
}

template<class T>
bool HashTable<T>::remove(T value) {
    size_t hash = gorner(value) % table.size();
    for (int i = 0;; ++i) {
        hash = (hash + i) % table.size();
        if (table[hash] == nullptr)
            return false;
        if (*table[hash] == value) {
            *table[hash] = "DELETED";
            return true;
        }
    }
}

template<class T>
bool HashTable<T>::add(T value) {
    if (realTableSize >= table.size() * RESIZECOEF) {
        rehash();
    }
    size_t hash = gorner(value) % table.size();
    for (int i = 0; i < table.size(); ++i) {
        hash = (hash + i) % table.size();
        if (table[hash] == nullptr) {
            table[hash] = new string(value);
            break;
        }
        if (*table[hash] == value)
            return false;
    }
    ++realTableSize;
    return true;
}

int main(int argc, const char *argv[]) {
    HashTable<string> table;
    char action;
    std::string key;
    bool isTrue;
    while (cin >> action >> key) {
        switch (action) {
            case '+': {
                isTrue = table.add(key);
                break;
            }
            case '-': {
                isTrue = table.remove(key);
                break;
            }
            case '?': {
                isTrue = table.search(key);
                break;
            }
        }
        if (isTrue){
            cout << "OK" << endl;
        }
        else{
            cout << "FAIL" << endl;
        }
    }
    return 0;
}

