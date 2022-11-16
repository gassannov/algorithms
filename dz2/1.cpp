#include <iostream>
#include <vector>
#include "string"
#define XVALUE 11;

using namespace std;

int gorner(const string& str){
    int hash = 0;
    for (char c: str) {
        hash = 17*hash + c;
    }
    return hash;
}

template<class T>
class HashTable{
private:
    struct Cell{
        T value;
        bool isDeleted;
        bool isNull;
        Cell(const T& value_): value(value_), isDeleted(false), isNull(false){};
        Cell():isNull(true), isDeleted(false){};
    };
    double rehashKoeff;
    vector<Cell> table;
    int arrSize;
    int realTableSize;
    void rehash();

public:
    explicit HashTable(double rehashKoef, int tableSize);
    bool add(const T& value);
    bool find(T value);
    bool del(T value);
};

template<class T>
HashTable<T>::HashTable(double rehashKoef, int tableSize): table(tableSize), realTableSize(0), arrSize(tableSize), rehashKoeff(rehashKoef){
}

template<class T>
bool HashTable<T>::add(const T& value) {
    if (realTableSize >= rehashKoeff*arrSize){
        rehash();
    }
    int index = (gorner(value)) % arrSize;
    for (int i = 0; i < arrSize; ++i){
        index = (index + i) % arrSize;
        if(!table[index].isDeleted && !table[index].isNull && table[index].value == value){
            return false;
        }
        else if (table[index].isDeleted || table[index].isNull){
            table[index].value = value;
            table[index].isNull = false;
            table[index].isDeleted = false;
            realTableSize++;
            return true;
        }
    }
    return false;
}

template<class T>
bool HashTable<T>::find(T value) {
    int index = (gorner(value) % arrSize);
    for(int i = 0;; i++){
        index = (index + i) % arrSize;
        if (table[index].isNull){
            return false;
        }
        if (!table[index].isNull && !table[index].isDeleted && table[index].value == value){
            return true;
        }
    }
    return false;
}

template<class T>
bool HashTable<T>::del(T value) {
    int index = (gorner(value) % arrSize);
    for(int i = 0; ; i++){
        index = (index + i) % arrSize;
        if (table[index].isNull){
            return false;
        }
        if (!table[index].isNull && !table[index].isDeleted && (table[index].value == value)){
            table[index].isDeleted = true;
            realTableSize--;
            return true;
        }
    }
    return false;
}

template<class T>
void HashTable<T>::rehash() {
    int newArrSize = arrSize*2;
    realTableSize = 0;
    vector<Cell> newArr(newArrSize);
    for (int i = 0; i < arrSize; ++i){
        if (!table[i].isDeleted && !table[i].isNull) {
            int index = gorner(table[i].value) % newArrSize;
            for (int j = 0;; ++j) {
                index = (index + j) % newArrSize;
                if (newArr[index].isNull || newArr[index].isDeleted) {
                    ++realTableSize;
                    newArr[index] = move(table[i]);
                    break;
                }
            }
        }
    }
    arrSize = newArrSize;
    table = move(newArr);
}

int main() {
    HashTable<string> hTable = HashTable<string>(0.75, 8);
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