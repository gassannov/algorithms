//
// Created by Марат Гасанов on 18.04.2022.
//
#include "iostream"
#include "assert.h"
using namespace std;

//7.2

unsigned int getByte(unsigned long long number, int byteNumber){
    return (number >> 8*byteNumber) & (255);
}

void cntSort(unsigned long long* array, int arraySize, int byte){
    int * cntArray = new int[256];
    unsigned long long* destArray = new unsigned long long[arraySize];

    for (int j = 0; j < 256; ++j) {
        cntArray[byte] = 0;
    }
    for (int j = 0; j < arraySize; ++j) {
        cntArray[getByte(array[j],byte)]++;
        //cout << "Значение байта: " << getByte(array[j], byte)  <<" Число: " << array[j] << " Номер байта: " << byte  << endl;
    }
    for (int j = 1; j < 256; ++j) {
        cntArray[j] += cntArray[j-1];
    }
    for(int j = arraySize - 1; ; j--) {
        destArray[--cntArray[getByte(array[j], byte)]] = array[j];
        if(j == 0)
            break;
    }

    for (int j = 0; j < arraySize; ++j) {
        array[j] = destArray[j];
    }

    delete[] destArray;
}

void LSDSort(unsigned long long* array, int arraySize){
    for (int i = 0; i < 8; ++i) {
        cntSort(array, arraySize, i);
    }
}

int main(){
    int arraySize;
    cin >> arraySize;
    unsigned long long* array = new unsigned long long[arraySize];

    for (int i = 0; i < arraySize; ++i) {
        unsigned long long num;
        cin >> num;
        array[i] = num;
    }

    if (arraySize != 0) {
        LSDSort(array, arraySize);
        for (int i = 0; i < arraySize; ++i) {
            cout << array[i] << " ";
        }
        cout << endl;
    }

    unsigned long long testArr[3] = {4, 1000000, 7};
    LSDSort(testArr, 3);
    assert(testArr[0] == 4);
    assert(testArr[1] == 7);
    assert(testArr[2] == 1000000);

    delete[] array;

    return 0;
}

