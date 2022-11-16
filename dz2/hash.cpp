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
    struct Cell{
        T value;
        bool isDeleted;
        bool isNull;
        Cell(const T& value_): value(value_), isDeleted(false), isNull(false){};
        Cell():isDeleted(false), isNull(true){};
    };
    size_t realTableSize;
    vector<Cell> table;

    void rehash();

public:
    bool add(T key);
    bool del(T value);
    bool find(T value);
    HashTable(size_t initial_capacity = INITIAL_CAPACITY) : table(initial_capacity, Cell()), realTableSize(0) {}
    ~HashTable();
};

template<class T>
void HashTable<T>::rehash() {
    vector<Cell> newTable(table.size() * 2, Cell());
    size_t newSize = 0;
    for (int i = 0; i < table.size(); ++i)
        if ((table[i].isNull) && (!table[i].isDeleted)) {
            size_t hash = gorner(table[i].value) % newTable.size();
            for (int j = 0;; ++j) {
                hash = (hash + j) % newTable.size();
                if (newTable[hash].isNull) {
                    ++newSize;
                    newTable[hash] = move(table[i]);
                    break;
                }
            }
        }
    table = move(newTable);
    realTableSize = newSize;
}

template<class T>
bool HashTable<T>::find(T value) {
    size_t hash = gorner(value) % table.size();
    for (int i = 0;; ++i) {
        hash = (hash + i) % table.size();
        if (table[hash].isNull)
            return false;
        if (table[hash].value == value && !table[hash].isDeleted) {
            return true;
        }
    }
}

template<class T>
bool HashTable<T>::del(T value) {
    size_t hash = gorner(value) % table.size();
    for (int i = 0;; ++i) {
        hash = (hash + i) % table.size();
        if (table[hash].isNull)
            return false;
        if (table[hash].value == value && !table[hash].isDeleted) {
            table[hash].isDeleted = true;
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
        if (table[hash].isNull ) {
            table[hash] = Cell(value);
            break;
        }
        else if(table[hash].isDeleted){
            table[hash].value = value;
            table[hash].isDeleted = false;
        }
        else if (table[hash].value == value)
            return false;
    }
    ++realTableSize;
    return true;
}

template<class T>
HashTable<T>::~HashTable() {
    table.clear();
    table.shrink_to_fit();
}

int main(int argc, const char *argv[]) {
    HashTable<string> hTable = HashTable<string>();
    char operationType;
    string str;
    bool isOk;
    while(cin >> operationType >> str){
        switch (operationType) {
            case '+':
                isOk = hTable.add(str);
                break;
            case '-':
                isOk = hTable.del(str);
                break;
            case '?':
                isOk = hTable.find(str);
                break;
            default:
                isOk = false;
        }
        if(isOk)
            cout << "OK" << endl;
        else
            cout << "FAIL" << endl;
    }
    return 0;
}


