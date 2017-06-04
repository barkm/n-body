

#ifndef _GEN_BODIES_H_NBODY_
#define _GEN_BODIES_H_NBODY_

#include <vector>
#include <array>
#include "body.h"

std::vector<Body> generate_bodies(int n, std::array<double, 3> min, std::array<double, 3> max, int rank);

#endif // _GEN_BODIES_H_NBODY_
