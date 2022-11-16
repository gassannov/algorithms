//
// Created by Марат Гасанов on 29.05.2022.
//
#include "WeightedGraph.h"
#include "iostream"
#include "Experiment.h"
using namespace std;

int main(){
    for (int i = 2; i < 11; ++i) {
        Experiment experiment(i, 10);
        std::pair<double, double> result = experiment.getInfo();
        cout << "avg appr: " << result.first << "\nstandart deviation " << result.second << endl;
    }
}
