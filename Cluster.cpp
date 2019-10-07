//
// Created by Connor on 2019/10/7.
//
#include <cstdlib>
#include <iostream>

#include "Cluster.h"


Cluster::Cluster() {
    attr1 = rand() % 10;
    attr2 = rand() % 10;
    std::cout << "(" << attr1 << "," << attr2 << ")" << std::endl;
}

double Cluster::getAttr1() {
    return attr1;
}

double Cluster::getAttr2() {
    return attr2;
}

void Cluster::updateAttr(const double attr1, const double attr2) {
    this -> attr1 = attr1;
    this -> attr2 = attr2;
}