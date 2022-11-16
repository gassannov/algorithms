//
// Created by Марат Гасанов on 18.04.2022.
//
#include "iostream"
using namespace std;

//5.1

struct Visitor{
    int inTime;
    int outTime;
    size_t advertCount;
};

bool compare(Visitor first, Visitor second){
    if (first.outTime > second.outTime){
        return true;
    }
    else if(first.outTime == second.outTime){
        return first.inTime > second.inTime;
    }
    else{
        return false;
    }
}

void increaseAdvertCount(Visitor* visArr, size_t visSize, size_t timeMoment){
    for (int i = 0; i < visSize; ++i) {
        if (visArr[i].inTime <= timeMoment && visArr[i].outTime >= timeMoment){
            visArr[i].advertCount++;
        }
    }
}

template <typename T> void mergeSort(T* array, size_t arrSize, bool (*compare)(T , T )){ //
    if(arrSize <= 1){
        return;
    }
    mergeSort(array, arrSize/2, compare);
    mergeSort(&array[arrSize/2], arrSize - arrSize/2, compare);

    size_t lIterations = 0;
    size_t rIterations = 0;
    size_t lSize = arrSize/2;
    size_t rSize = arrSize - arrSize/2;
    T sortedArray[arrSize];

    for (int i = 0; i < arrSize; ++i) {
        if (!compare(array[lIterations], array[lSize + rIterations])){
            sortedArray[i] = array[lIterations];
            lIterations ++;
        }
        else{
            sortedArray[i] = array[lSize + rIterations];
            rIterations ++;
        }

        if(lIterations == lSize){
            while (rIterations < rSize){
                sortedArray[++i] = array[lSize + rIterations];
                rIterations ++;
            }
            break;
        }

        else if(rIterations == rSize){
            while (lIterations < lSize){
                sortedArray[++i] = array[lIterations];
                lIterations ++;
            }
            break;
        }
    }
    for(size_t i = 0; i < arrSize; i++) {
        array[i] = sortedArray[i];
    }
}

int main(){
    size_t visitorNumber;
    size_t advCount = 0;
    cin >> visitorNumber;
    Visitor* visArr = new Visitor[visitorNumber];
    for (int i = 0; i < visitorNumber; ++i) {
        int inTime, outTime;
        cin >> inTime >> outTime;
        Visitor vis = Visitor();
        vis.inTime = inTime;
        vis.outTime = outTime;
        vis.advertCount = 0;
        visArr[i] = vis;
    }

    mergeSort<Visitor>(visArr, visitorNumber, compare);
    for (int i = 0; i < visitorNumber; ++i) {
        if (visArr[i].advertCount == 0){
            increaseAdvertCount(visArr, visitorNumber, visArr[i].outTime - 1);
            advCount++;
        }
        if(visArr[i].advertCount == 1){
            increaseAdvertCount(visArr, visitorNumber, visArr[i].outTime);
            advCount++;
        }
    }

    cout << advCount << endl;
}

