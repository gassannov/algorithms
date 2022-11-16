#include <iostream>
#include <cmath>
#include "assert.h"
using namespace std;

// 2.2

size_t binarySearch(int* numbers, size_t downLimit, size_t upperLimit ){
    while( (upperLimit - downLimit) > 1 ){
        size_t middle = (upperLimit + downLimit)/2;
        if ( (numbers[middle] > numbers[middle+1]) && ( numbers[middle] > numbers[middle-1])){
            return middle;
        }

        if (numbers[middle] > numbers[middle-1]){
            downLimit = middle;
        }

        else{
            upperLimit = middle;
        }
    }
    if (downLimit == 0){
        if (numbers[upperLimit] > numbers[downLimit]){
            return upperLimit;
        }
        else{
            return downLimit;
        }
    }
    else if ( numbers[downLimit] > numbers[downLimit-1] && numbers[downLimit] > numbers[downLimit + 1] ){
        return downLimit;
    }
    else{
        return upperLimit;
    }
}

size_t two(int* numbers, size_t numbers_size){
    size_t downLimit = 0;
    size_t upperLimit = 1;
    size_t i = 1;
    //exp_search
    while((numbers[downLimit] < numbers[downLimit+1]) && (numbers[upperLimit] > numbers[upperLimit-1]) ){
        downLimit = upperLimit;
        upperLimit = pow(2, i);
        if (upperLimit >= numbers_size)
        {
            upperLimit = numbers_size - 1;
            break;
        }
        i++;
    }
    return binarySearch(numbers, downLimit, upperLimit);
}

int main(int argc, char const *argv[]){

    size_t arrSize;
    cin >> arrSize;

    int* arr = new int[arrSize];
    for (int i = 0; i < arrSize; ++i){
        int arrElem = 0;
        cin >> arrElem;
        arr[i] = arrElem;
    }

    cout << two(arr, arrSize);

    int first[] = {1, 2, 3, 2, 1};
    int second[] = {0, 1};
    int third[] = {1, 0};
    int four[] = {1, 54, 78, 100, 123, 432, 5, 4, 3, 2, 1};
    int five[] = {1, 2, 3, 4, 5, 6, 7, 6, 5, 4};

    assert(two(first, 5) == 2);
    assert(two(second, 2) == 1);
    assert(two(third, 2) == 0);
    assert(two(four, 11) == 5);
    assert(two(five, 10) == 6);

    delete[] arr;

    return 0;
}