#include "gen_bodies.h"

#include <stdlib.h> 

double f_rand(double f_min, double f_max)
{
    double f = (double)rand() / RAND_MAX;
    return f_min + f * (f_max - f_min);
}

std::vector<Body> generate_bodies(int n, std::array<double, 3> min, std::array<double, 3> max, int rank){
    srand(100*rank);
    std::vector<Body> bodies(n);
    for(int i = 0; i < n; i++){
        double x = f_rand(min[0], max[0]);
        double y = f_rand(min[1], max[1]);
        double z = f_rand(min[2], max[2]);
        double m = f_rand(0.5, 1);
        bodies[i] = {{x, y, z}, {0, 0, 0}, m, 1};
    }
    return bodies;
}
