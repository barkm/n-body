
#ifndef _ORB_H_N_BODY_H
#define _ORB_H_N_BODY_H

#include <mpi.h>

#include <vector>
#include <array>
#include <utility>
#include <string>

#include "../misc/body.h"

using std::vector; using std::pair;
using std::array; using std::string;

typedef vector<pair<array<double, 3>, array<double, 3> > > bound_vec;


/*
Determines if the process is above or below a bisection

@param rank : rank of process
@param n_processes : total number of processes to be placed above or below split
*/
bool is_above_split(int rank, int n_processes);

/*
Determines the communication partner on the other side of a bisection

@param rank : rank of process 
@param n_processes : total number of processes
*/

int get_partner(int rank, int n_processes);

/*
Determines which coordinate to split.

@param min : min bounds
@param max : max bounds
*/
int split_coord(const array<double, 3> & min, const array<double, 3> & max);


/*
Calculates the weight fraction which below the split

@param bodies : bodies on process
@param split : the split
@param coord : coordinate to split
@param comm : communication group
*/
double weight_frac(const std::vector<Body> & bodies, double split, int coord, const MPI_Comm & comm);


/*
Carries out the orthogonal recursive bisection algorithm

@param bodies : bodies residing on process (modified)
@param bounds : vector of min and max bounds after each split. (modified)
@param partners : communication partner at each split (modified)
@param global_min : minimum bounds for bodies on all processes
@param global_max : maximum bounds for bodies on all processes
@param rank : rank of process
@param n_processors : number of proccessors
*/
void orb(vector<Body> & bodies, bound_vec & bounds,
        bound_vec & other_bounds, vector<pair<int, bool> > & partners,
        const double * global_min, const double * global_max,
        int rank, int n_processors);


/*
Computes the min and max boundaries containing all bodies

@param bodies : bodies on process
@param min : min boundaries (modified)
@param max : max boundaries (modified)
*/
void global_minmax(const vector<Body> bodies, double * min, double * max);


#endif // _ORB_H_N_BODY_H
