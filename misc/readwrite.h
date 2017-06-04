
#ifndef _READWRITE_H_NBODY_
#define _READWRITE_H_NBODY_

#include <mpi.h>
#include <vector>

#include "../tree/tree.h"
#include "body.h"
#include "inputparser.h"


std::pair<std::vector<Body>, int> read_bodies(const char * filename, MPI_Comm comm);

void write_bodies(const char * filename, const std::vector<Body> & bodies, MPI_Comm comm, bool overwrite);

void write_tree(const char * filename, const Tree & tree, bool fulltree, bool overwrite);

void write_to_file(const char * filename, const double x, bool overwrite);

void write_summary(InputParser ip, int N, int P);

#endif // _READWRITE_H_NBODY_
