
#ifndef _MPI_TYPES_N_BODY_H
#define _MPI_TYPES_N_BODY_H

#include <mpi.h>

extern MPI_Datatype mpi_body_type;
extern MPI_Datatype mpi_cell_type;

struct MPICell{
    double min_bounds[3];
    double max_bounds[3];
    double m;   // mass 
    double rm[3]; // center of mass
    int parent_idx;
};


void create_mpi_body();

void create_mpi_cell();

void init_mpi_types();

void free_mpi_types();

#endif // _MPI_TYPES_N_BODY_H
