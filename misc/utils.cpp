#include "utils.h"

#include <math.h>
#include <iostream>
using std::cout; using std::endl;

double secant(double a, double b, std::function<double (double)> f, double tol, int max_iter){

    double x, y, fa, fb;
    int n_iter;

    n_iter = 0;
    fa = f(a); fb = f(b);

    while(fabs(b-a) > tol && fa != fb && n_iter < max_iter){
        x = a - (b - a) * fa / (fb - fa);
        y = f(x);
        b = a; a = x;
        fb = fa; fa = y;
        n_iter++;
    }
    return a;
}


double bisection(double a, double b, std::function<double (double)> f, double tol, int max_iter){

    double c, fa, fb, fc;
    int n_iter;

    fa = f(a); fb = f(b);

    n_iter = 0;
    while(fabs(b-a) > tol && fa != fb && n_iter < max_iter){
        c = (a + b) / 2;
        fc = f(c);


        if(fc == 0){
            return c; 
        }
        else if(fa * fc > 0){
            a = c;
        }
        else{
            b = c;
        }
        n_iter++;
    }

    return (a + b) / 2;
}

double dist_aabb(const double * a_min, const double * a_max, const double * b_min, const double * b_max){
    double dist = 0;
    double delta;
    for(int c = 0; c < 3; c++){
    
        if(a_min[c] > b_max[c]){
               delta = a_min[c] - b_max[c];
               dist += delta * delta;
        }
        else if(b_min[c] > a_max[c]){
               delta = b_min[c] - a_max[c];
               dist += delta * delta;
        }
    }
    return dist;
}
