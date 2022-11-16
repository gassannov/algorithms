//
// Created by Марат Гасанов on 03.06.2022.
//

#include "Experiment.h"

Experiment::Experiment(int citiesCount, int expCount_): expCount(expCount_), points(citiesCount), citiesGraph(citiesCount){
    int edgesCount = 0;
    for(int i=0; i<citiesCount; i++){
        for (int j = i+1; j < citiesCount; ++j) {
            edgesCount++;
        }
    }

    citiesGraph.setEdgesCnt(edgesCount);

    for (int i = 0; i < citiesCount; ++i) {
        double s = 0;
        double x = 0;
        double y = 0;
        while (s > 1 || s <= 0){
            x = (double) std::rand() / RAND_MAX;
            y = (double) std::rand() / RAND_MAX;
            s = x*x + y*y;
        }
        double log = sqrt((-2*std::log(s)/s));
        points[i] = Point(x*log, y*log);
    }
    for (int i = 0; i < citiesCount; ++i) {
        for (int j = i+1; j < citiesCount; ++j) {
            citiesGraph.addEdge(i, j, points[i].getDistance(points[j]));
        }
    }
}

double Experiment::getAppr() {
    double kruskalResult = citiesGraph.kruskal();
    double rightResult = citiesGraph.bruteForce();
    return std::max(kruskalResult/rightResult, rightResult/kruskalResult);
}

double Experiment::averageAppr() {
    double avg = 0;
    for (int i = 0; i < expCount; ++i) {
        double kruskalResult = citiesGraph.kruskal();
        double rightResult = citiesGraph.bruteForce();
        avg += std::max(kruskalResult/rightResult, rightResult/kruskalResult);
    }
    return avg;
}

double Experiment::stdDeviation() {
    double avg = 0;
    double deviation = 0;
    for (int i = 0; i < expCount; ++i) {
        double kruskalResult = citiesGraph.kruskal();
        double rightResult = citiesGraph.bruteForce();
        deviation += pow((kruskalResult - rightResult), 2);
    }
    deviation = sqrt(deviation);
    return deviation;
}

std::pair<double, double > Experiment::getInfo() {
    double avg = 0;
    double deviation = 0;
    for (int i = 0; i < expCount; ++i) {
        double kruskalResult = citiesGraph.kruskal();
        double rightResult = citiesGraph.bruteForce();
        avg += std::max(double(kruskalResult/rightResult), double(rightResult/kruskalResult));
        deviation += pow((kruskalResult - rightResult), 2);
        regroupPoints();
    }
    deviation = sqrt(deviation)/(double)expCount;
    avg /= (double)expCount;
    return {avg, deviation};
}

void Experiment::regroupPoints() {
    WeightedGraph newCitiesGraph(citiesGraph.getSize(), citiesGraph.edgeCount());
    for (int i = 0; i < citiesGraph.getSize(); ++i) {
        double s = 0;
        double x = 0;
        double y = 0;
        while (s > 1 || s <= 0){
            x = (double) std::rand() / RAND_MAX;
            y = (double) std::rand() / RAND_MAX;
            s = x*x + y*y;
        }
        double log = sqrt((-2*std::log(s)/s));
        points[i] = Point(x*log, y*log);
    }

    for (int i = 0; i < newCitiesGraph.getSize(); ++i) {
        for (int j = i+1; j < newCitiesGraph.getSize(); ++j) {
            newCitiesGraph.addEdge(i, j, points[i].getDistance(points[j]));
        }
    }
    citiesGraph = newCitiesGraph;
}
