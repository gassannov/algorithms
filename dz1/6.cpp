//
// Created by Марат Гасанов on 18.04.2022.
//
#include "iostream"
#include "random"
using namespace std;

//6.3

bool compare(int n1, int n2){
    return n1 > n2;
}


template<typename T> size_t partition(T* array, size_t leftBorder,size_t rightBorder, bool (*compare)(T , T )){
    size_t pivot = rand() % (rightBorder+1 - leftBorder) + leftBorder;
    swap(array[rightBorder], array[pivot]);
    pivot = rightBorder;
    size_t i = leftBorder;
    size_t j = leftBorder;
    while (j < rightBorder){
        if (compare(array[j], array[pivot])){
            j++;
        }
        else{
            swap(array[j], array[i]);
            j++;
            i++;
        }
    }
    swap(array[j], array[i]);

    return i;
}

template<typename T> int findKStat(T* array, size_t arraySize, size_t k, bool (*compare)(T , T )){
    size_t leftBorder = 0;
    size_t rightBorder = arraySize - 1;
    size_t index = arraySize+1;
    size_t i = 0;
    while (index != k){
        index = partition(array,leftBorder, rightBorder, compare);
        if (index < k){
            leftBorder = index;
        }
        else{
            rightBorder = index-1;
        }
        i++;
    }
    return array[index];
}

int main(){
    size_t arraySize;
    cin >> arraySize;
    int* array = new int[arraySize];

    for (int i = 0; i < arraySize; ++i) {
        int num;
        cin >> num;
        array[i] = num;
    }
    cout << findKStat(array, arraySize, arraySize/10, compare) << endl;
    cout << findKStat(array, arraySize, arraySize/2, compare) << endl;
    cout << findKStat(array, arraySize, arraySize*9/10, compare) << endl;
    delete[] array;
}

