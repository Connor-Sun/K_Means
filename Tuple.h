//
// Created by Connor on 2019/10/7.
//

#ifndef K_MEANS_TUPLE_H
#define K_MEANS_TUPLE_H


class Tuple {

public:
    Tuple();
    Tuple( const double, const double);

    double getAttr1();
    double getAttr2();

    void updateLabel(const int);


private:
    double attr1;
    double attr2;
    unsigned int label = 0;

};


#endif //K_MEANS_TUPLE_H
