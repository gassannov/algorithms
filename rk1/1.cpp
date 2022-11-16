#include <iostream>

using namespace std;

unsigned binarySearch(const int *arr, unsigned leftBorder, unsigned rightBorder) {
    unsigned index = (rightBorder + leftBorder) >> 1;
    while (rightBorder > leftBorder) {
        if ((arr[index + 1] < arr [index]) && (arr[index - 1] <= arr [index])) {
            return index;
        }
        if (arr[index - 1] <= arr [index]) {
            leftBorder = index;
        } else {
            rightBorder = index;
        }
        index = (rightBorder + leftBorder) >> 1;
    }
    if ((arr[index + 1] < arr [index]) && (arr[index - 1] <= arr [index])) {
        return rightBorder;
    } else return leftBorder;
}

unsigned doLogic(int *arr, unsigned size) {
    if (size == 1) { return 0;}
    unsigned index = 1;
    while (index < size) {
        if (arr[index] < arr[index >> 1]) {
            return binarySearch(arr, index >> 1, index);
        }
        index = index << 1;
    }
    index = size - 1;
    if (arr[index] < arr[index >> 1]) {
        return binarySearch(arr, index >> 1, index);
    } else {
        return size;
    }
}

int main() {
    unsigned size;
    int *arr;
    cin >> size;
    arr = (int *) malloc(sizeof(int) * size);
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }
    cout << doLogic(arr, size)+1 << endl;
}