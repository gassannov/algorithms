//
// Created by Марат Гасанов on 03.06.2022.
//

#ifndef DZ3_EXPERIMENT_H
#define DZ3_EXPERIMENT_H
#include "iostream"
#include "vector"
#include "cmath"
#include "WeightedGraph.h"

struct Point{
    double x;
    double y;
    double getDistance(Point point){return sqrt(pow((x-point.x),2) + pow((y-point.y),2));}
    Point(double x_, double y_): x(x_), y(y_){};
    Point(){x=y=0;};
};

class Experiment {
    WeightedGraph citiesGraph;
    std::vector<Point> points;
    int expCount;
public:
    Experiment(int citiesCount, int expCount_);
    double getAppr();
    double averageAppr();
    double stdDeviation();
    std::pair<double, double> getInfo();
    void regroupPoints();
};


#endif //DZ3_EXPERIMENT_H
