#include "orb.h"

#include <mpi.h>
#include <cmath>
#include <limits>
#include <functional>
#include <iostream>

#include "../misc/mpi_types.h"
#include "../misc/utils.h"


using std::vector; using std::pair;
using std::make_pair;
using std::function;
using std::array;

using std::cout; using std::endl;


bool is_above_split(int rank, int n_processes){
    int rel_bit = (int) log2(n_processes);
    bool above = (rank >> (rel_bit - 1)) & 1;
    /* gray code */
    //above = above ^ ((rank >> (rel_bit)) & 1); 
    return above;
}

int get_partner(int rank, int n_processes){
    int rel_bit = (int) log2(n_processes);
    int partner = rank ^ (1 << (rel_bit - 1));
    return partner; 
}

int split_coord(const array<double, 3> & min, const array<double, 3> & max){
    double max_diff = -1;
    int coord;
    for(int c = 0; c < 3; c++){
        // split along maximum dimension
        if(max[c] - min[c] > max_diff){
            coord = c;
            max_diff = max[c] - min[c];
        }
    }
    return coord;
}

double weight_frac(const std::vector<Body> & bodies, double split, int coord, const MPI_Comm & comm){
    
    int i;
    double work_above, work_below, tot_work_above, tot_work_below;

    /* Compute local contribution to work */
    work_above = work_below = 0;
    for(i = 0; i < bodies.size(); i++){
        if(bodies[i].pos[coord] > split){
            work_above += bodies[i].work; 
        } 
        else{
            work_below += bodies[i].work;
        }
    }

    /* Sum up over all processes */
    MPI_Allreduce(&work_above, &tot_work_above, 1, MPI_DOUBLE, MPI_SUM,comm);
    MPI_Allreduce(&work_below, &tot_work_below, 1, MPI_DOUBLE, MPI_SUM,comm);

    /* Return fraction of work below */
    return tot_work_below / (tot_work_above + tot_work_below);

}

void orb(vector<Body> & bodies, bound_vec & bounds,
        bound_vec & other_bounds, vector<pair<int, bool> > & partners,
        const double * global_min, const double * global_max,
        int rank, int n_processors){


    /* Declare variables */
    int coord, partner, n_recv_bodies, color, this_side_size;
    int n_splits, n_proc_left;
    bool above;
    double split; 
    vector<Body> other_side, this_side;
    function<double (double)> f;
    MPI_Status status;
    MPI_Comm subset_comm;
    array<double, 3> min_bounds, max_bounds, min, max, other_min, other_max;

    /* Copy over global min and max */
    std::copy(global_min, &global_min[3], std::begin(min));  
    std::copy(global_max, &global_max[3], std::begin(max));  

    /* ORB */
    color = 0;
    above = false;

    // split until number of processes in subset is 1
    n_splits = log2(n_processors);
    for(int i = 0; i < n_splits; i++){
        n_proc_left = n_processors / pow(2,i);

        /* Find split in current subset of processors */

        // color processors such that each subset gets unique color
        // color of processor depends on how many times it has been 'above'
        color = color << 1;
        if(above){ 
            color |= 1;
        }

        // split the world comm to processor subset
        MPI_Comm_split(MPI_COMM_WORLD, color, rank, &subset_comm);
        
        // choose cartesian coordinate to split
        coord = split_coord(min, max);

        // find split through the bisection method
        // which divides workload equally
        f = [&](double split){return weight_frac(bodies, split, coord, subset_comm) - 0.5;};
        split = bisection(min[coord], max[coord], f);

        // free comm
        MPI_Comm_free(&subset_comm);
        
        /* Decide if process is above or below split */
        above = is_above_split(rank, n_proc_left);


        /* Save bounds */
        other_min = min;
        other_max = max;
        if(above){
            min[coord] = split;
            other_max[coord] = split;
        }
        else{
            max[coord] = split;
            other_min[coord] = split;
        }
        // bounds on this side of split
        min_bounds = min;
        max_bounds = max;
        bounds.push_back(make_pair(min_bounds, max_bounds));
        
        // bounds on other side of split
        min_bounds = other_min;
        max_bounds = other_max;
        other_bounds.push_back(make_pair(min_bounds, max_bounds));

        /* Partition bodies between split */
        other_side.clear();
        this_side.clear();
        for (Body b : bodies){
            if ((b.pos[coord] - split > 0) == above){
                this_side.push_back(b);
            }
            else{
                other_side.push_back(b);
            }
        }
        this_side_size = this_side.size();
        
        /* Exchange bodies with other side */
        // get communication partner
        partner = get_partner(rank, n_proc_left);
        partners.push_back(make_pair(partner, above));

        // must separate send and recieve in order to read incoming size
        if(above){
            // probe recv size and resize vector
            MPI_Probe(partner, 0, MPI_COMM_WORLD, &status);
            MPI_Get_count(&status, mpi_body_type, &n_recv_bodies);
            this_side.resize(this_side.size() + n_recv_bodies);

            // recv bodies
            MPI_Recv(&this_side[this_side_size], n_recv_bodies, mpi_body_type,
                    partner, 0, MPI_COMM_WORLD, &status);

            // send bodies
            MPI_Send(&other_side[0], other_side.size(), mpi_body_type, partner, 0, MPI_COMM_WORLD);

        }
        else{
            // send bodies
            MPI_Send(&other_side[0], other_side.size(), mpi_body_type, partner, 0, MPI_COMM_WORLD);

            // probe recv size and resize vector
            MPI_Probe(partner, 0, MPI_COMM_WORLD, &status);
            MPI_Get_count(&status, mpi_body_type, &n_recv_bodies);
            this_side.resize(this_side.size() + n_recv_bodies);

            // recv bodies
            MPI_Recv(&this_side[this_side_size], n_recv_bodies, mpi_body_type,
                    partner, 0, MPI_COMM_WORLD, &status);
        }
        
        /* Update bodies */
        bodies = this_side;
    }

}

void global_minmax(const vector<Body> bodies, double * min, double * max){

    /* Initialize bounds to infinity */
    min[0] = min[1] = min[2] = std::numeric_limits<double>::infinity();
    max[0] = max[1] = max[2] = -std::numeric_limits<double>::infinity();
    
    /* Find local min and max bounds */
    for(const Body & b : bodies){
        for(int c = 0; c < 3; c++){
            if(b.pos[c] < min[c]){
                min[c] = b.pos[c];
            }
            if(b.pos[c] > max[c]){
                max[c] = b.pos[c];
            }
        }
    }
    
    /* Find global min and max bounds */
    for(int c = 0; c < 3; c++){
        double global_min;
        double global_max;
        MPI_Allreduce(&min[c], &global_min, 1, MPI_DOUBLE, MPI_MIN, MPI_COMM_WORLD);
        MPI_Allreduce(&max[c], &global_max, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
        min[c] = global_min;
        max[c] = global_max;
    }
}
