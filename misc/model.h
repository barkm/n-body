
#ifndef MODEL_H_N_BODY
#define MODEL_H_N_BODY

#include <array>

using std::array;

array<double, 3> eval_force(const double * r1, double m1, const double * r2, double m2);

#endif // MODEL_H_N_BODY
