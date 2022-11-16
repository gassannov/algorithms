#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <string.h>
using namespace std;


template <typename T> class Heap{
    T* array;
    size_t heapSize;
    size_t arrSize;

    void sifftDown(size_t index){
        size_t left = 2*index + 1;
        size_t right = 2*index +2;
        size_t small = index;

        if (left < heapSize && array[left] < array[index]){
            if (array[left] < array[right]){
                small = left;
            }
            else{
                small = right;
            }
        }

        if (right < heapSize && array[right] < array[index]){
            if (array[right] < array[left]){
                small = right;
            }
            else{
                small = left;
            }
        }

        if (small != index){
            swap(array[index], array[small]);
            sifftDown(small);
        }
    }

    void sifftUp(size_t index) {
        if (index > 0) {
            size_t parent = (index - 1) / 2;
            if (array[index] < array[parent]) {
                swap(array[index], array[parent]);
                sifftUp(parent);
            }
        }
    }

    void reallocArray(){
        arrSize *= 2;
        T* newArr = new T[arrSize];
        memcpy(newArr, array, sizeof(T) * arrSize);
        delete[] array;
        array = newArr;
    }

public:
    Heap(){
        heapSize = 0;
        arrSize = 2;
        array = new T[2];
    }

    T pop(){
        heapSize--;
        T proc = array[0];
        array[0] = array[heapSize];
        sifftDown(0);
        return proc;
    }

    void push(T t){
        if (!heapSize){
            array[0] = t;
            heapSize++;
            return;
        }
        if (heapSize == arrSize){
            reallocArray();
        }
        array[heapSize] = t;
        sifftUp(heapSize);
        heapSize++;
    };

    void out(){
        cout << array[0]  << " ";
        for (int i = 1; i < heapSize; i++) {
            cout << array[i] << " ";
        }
        cout << endl;
    }
};

int main(int argc, char const *argv[])
{
    Heap<int> heap;
    size_t procCount;
    cin >> procCount;
    for (int i = 0; i < procCount; ++i) {
        int num;
        cin >> num;
        heap.push(num);
    }

    heap.out();
    cout << heap.pop() << endl;
    heap.out();

    return 0;
}
