

#ifndef _BUILD_TREE_H_N_BODY_
#define _BUILD_TREE_H_N_BODY_

#include <vector>
#include <utility>
#include <array>

#include "../misc/body.h"
#include "tree.h"
#include "../misc/mpi_types.h"

using std::vector; using std::array;
using std::pair;


typedef vector<pair<array<double, 3>, array<double, 3> > > bound_vec;

/*
Builds to local tree consisting of the ORB splits and the Barnes-Hut tree. 

@param bodies : bodies residing on the process
@param bounds : boundaries from the ORB within which this process belong
@param other_bounds : boundaries from the ORB within this process does not belong 
@param partners : communication partners during the ORB
@param tree : the tree to build (will be modified)
@param rank : rank of the process
*/
void build_tree(const vector<Body > & bodies, const bound_vec & bounds, const bound_vec & other_bounds,
                const vector<pair<int, bool> > & partners, Tree & tree, int rank);

vector<Cell *> construct_received_trees(const vector<MPICell> & recv_cells);


#endif // _BUILD_TREE_H_N_BODY_
