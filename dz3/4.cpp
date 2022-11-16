//
// Created by Марат Гасанов on 25.05.2022.
//
#include "iostream"
#include "set"

class Fifteens{
public:
    int gameMatrix[4][4];
    int zeroIndex1;
    int zeroIndex2;
    explicit Fifteens(const int* array);
    void switch_m(int index1_1, int index1_2, int index2_1, int index2_2);
    bool right();
    bool left();
    bool up();
    bool down();
    void out();

};

Fifteens::Fifteens(const int *array) {
    for (int i = 0; i < 16; ++i) {
        gameMatrix[i/4][i%4] = array[i];
        if (array[i] == 0){
            zeroIndex1 = i/4;
            zeroIndex2 = i%4;
        }
    }
}


class FifteensState{
    int getErrorRate();
}

void Fifteens::switch_m(int index1_1,int index1_2, int index2_1, int index2_2) {
    int n = gameMatrix[index1_1][index1_2];
    gameMatrix[index1_1][index1_2] = gameMatrix[index2_1][index2_2];
    gameMatrix[index2_1][index2_2] = n;
    if (index1_1 == zeroIndex1 && index1_2 == zeroIndex2){
        zeroIndex1 = index1_1;
        zeroIndex2 = index1_2;
    }
    else if(index2_1 == zeroIndex1 && index2_2 == zeroIndex2){
        zeroIndex1 = index2_1;
        zeroIndex2 = index2_2;
    }
}

void Fifteens::out() {
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            std::cout << gameMatrix[i][j] << " ";
        }
        std::cout<< std::endl;
    }
    std::cout << std::endl;
}




int main(){
    int num[16] = {11,2,12,15, 9, 7, 14, 4, 1, 6, 3, 8, 10, 5, 13, 0};
//    for (int i = 0; i < 15; ++i) {
//        std::cin >> num[i];
//    }

}