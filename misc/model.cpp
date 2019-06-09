
#include "model.h"
#include <cmath>

#include <iostream>

using std::array;

array<double, 3> eval_force(const double * r1, double m1, const double * r2, double m2){
    double M = m1 * m2;
    array<double, 3> f;
    
    double norm = 0;
    for(int c = 0; c < 3; c++){
        norm += pow(r1[c] - r2[c], 2);
    }
    
    for(int c = 0; c < 3; c++){
        f[c] = M * (r1[c] - r2[c]);
        f[c] /= pow(norm, 3.0 / 2.0);
    }
    return f;
}
