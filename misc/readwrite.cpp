#include "readwrite.h"

#include <string>
#include <fstream>
#include <sstream>

#include <sys/stat.h>

bool file_exists(const std::string& filename)
{
    struct stat buf;
    if (stat(filename.c_str(), &buf) != -1)
    {
        return true;
    }
    return false;
}

std::pair<std::vector<Body>, int> read_bodies(const char * filename, MPI_Comm comm){
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    std::vector<Body> bodies;
    /* Read bodies from file */
    if(rank != 0){
        MPI_Status status;
        int x;
        MPI_Recv(&x, 1, MPI_INT, rank - 1, 0,
                MPI_COMM_WORLD, &status);
    }

    std::ifstream infile;
    infile.open(filename);

    std::string line;
    int i = 0;
    while (std::getline(infile, line)){
        std::istringstream iss(line);
        double x, y, z, vx, vy, vz, m;
        if (!(iss >> x >> y >> z >> vx >> vy >> vz >> m)) { break; } // error
        if((i % size) == rank){
            bodies.push_back(Body{{x, y, z}, {vx, vy, vz}, m, 1});
        }
        i++;
    }
    infile.close();

    if(rank != size - 1){
        int x = 1;
        MPI_Send(&x, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }

    return std::make_pair(bodies, i);
}

void write_bodies(const char * filename, const std::vector<Body> & bodies, MPI_Comm comm, bool overwrite){
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    std::ofstream myfile;
    if(rank != 0){
        MPI_Status status;
        int x;
        MPI_Recv(&x, 1, MPI_INT, rank - 1, 0,
                MPI_COMM_WORLD, &status);
        myfile.open(filename, std::ios::app);
    }else{
        if(!file_exists(filename) or overwrite){
            myfile.open(filename);
        }else{
            myfile.open(filename, std::ios::app);
        }
    }

    for(const Body & b : bodies){
        myfile << b.pos[0] << " " << b.pos[1] << " " << b.pos[2] << std::endl;
    }

    if(rank != size - 1){
        myfile.close();
        int x = 1;
        MPI_Send(&x, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
    }else{
        myfile << std::endl;
        myfile.close();
    }
}

void write_to_file(const char * filename, const double x, bool overwrite){
    std::ofstream myfile;
    if(!file_exists(filename) or overwrite){
        myfile.open(filename);
    }else{
        myfile.open(filename, std::ios::app);
    }
    myfile << x << std::endl;;
    myfile.close();
}

void write_tree(const char * filename, const Tree & tree, bool fulltree, bool overwrite){
    std::ofstream myfile;
    if(!file_exists(filename) or overwrite){
        myfile.open(filename);
    }else{
        myfile.open(filename, std::ios::app);
    }
    myfile << tree.to_string(fulltree) << std::endl;
    myfile.close();
}

void write_summary(InputParser ip, int N, int P){

    std::ofstream file;
    file.open(ip.out_sum_file());

    file << "number of processes: " << P << std::endl;
    file << "number of bodies: " << N << std::endl;
    if(ip.read_bodies()){
        file << "read bodies from file: " << ip.in_file() << std::endl;
    }
    else{
        file << "read bodies from file: none" << std::endl;
    }
    file << "barnes hut approximaiton constant (theta): " << ip.bh_approx_constant() << std::endl;
    file << "gravitational constant (G): " << ip.grav_constant() << std::endl;
    file << "number of time steps: " << ip.n_steps() << std::endl;
    file << "time step: " << ip.time_step() << std::endl;
    file << "sampling interval: " << ip.sampling_interval() << std::endl;
    if(ip.write_positions()){
        file << "output file with positions: " << ip.out_file() << std::endl;
    }
    else{
        file << "output file with positions: none" << std::endl;
    }
    if(ip.write_tree()){
        file << "output file with tree: " << ip.out_tree_file() << std::endl;
    }
    else{
        file << "output file with tree: none" << std::endl;
    }
    if(ip.clock_run()){
        file << "output file with running times: " << ip.out_time_file() << std::endl;
    }
    else{
        file << "output file with running_times: none" << std::endl;
    }

}
