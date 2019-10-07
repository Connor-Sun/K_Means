//
// Created by Connor on 2019/10/7.
//

#include "Tuple.h"

Tuple::Tuple() {
    this -> attr1 = 0;
    this -> attr2 = 0;
}

Tuple::Tuple(const double attr1, const double attr2) {
    this -> attr1 = attr1;
    this -> attr2 = attr2;
}

double Tuple::getAttr1() {
    return attr1;
}

double Tuple::getAttr2() {
    return attr2;
}
void Tuple::updateLabel(const int label) {
    this -> label = label;
}
