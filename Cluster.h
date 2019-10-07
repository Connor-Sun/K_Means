//
// Created by Connor on 2019/10/7.
//

#ifndef K_MEANS_CLUSTER_H
#define K_MEANS_CLUSTER_H

#include "Tuple.h"


class Cluster : public Tuple {

public:
    Cluster();

    double getAttr1();
    double getAttr2();

    void updateAttr(const double , const double);

private:
    double attr1;
    double attr2;
    unsigned int label;
};


#endif //K_MEANS_CLUSTER_H
