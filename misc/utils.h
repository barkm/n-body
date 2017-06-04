
#ifndef _UTILS_H_N_BODY_
#define _UTILS_H_N_BODY_

#include <functional>

double secant(double a, double b, std::function<double (double)> f, double tol=1e-10, int max_iter=200);

double bisection(double a, double b, std::function<double (double)> f, double tol=1e-10, int max_iter=200);

double dist_aabb(const double * a_min, const double * a_max, const double * b_min, const double * b_max);

#endif // _UTILS_H_N_BODY_
