
#ifndef _INPUTPARSER_H_NBODY_
#define _INPUTPARSER_H_NBODY_

#include <unistd.h>  /* getopt */
#include <string>

class InputParser{
public:
    bool parse(int argc, char** argv); 

    double grav_constant();

    double bh_approx_constant();

    bool read_bodies();
    std::string in_file();

    int n_bodies();

    int n_steps();

    double time_step();

    bool verbose();

    bool write_positions();
    std::string out_file();

    bool write_tree();
    std::string out_tree_file();

    bool write_tree_size();
    std::string out_tree_size_file();

    int sampling_interval();

    std::string out_time_file();
    bool clock_run();

    bool write_summary();
    std::string out_sum_file();

private:
    // number of time steps
    int steps = 100;

    // time step
    double dt = 1;

    // barnes hut approximation constant
    double theta = 1;

    // gravitational constant
    double g = 1;

    // load bodies from file
    bool readfile = false;
    std::string in_fn;

    // output file
    bool save_positions = false;
    std::string out_fn = "positions.txt";

    // tree output file
    bool save_tree = false;
    std::string out_tree_fn = "tree.txt";

    bool save_tree_size = false;
    std::string out_tree_size_fn = "tree_size.txt";

    // sampling interval
    int si = 10;

    // number of bodies if not load from file
    int n = 100;

    // verbose
    bool verb = false;

    // clock the run
    std::string out_time_fn = "time.txt";
    bool clock = false;

    // summary
    bool summarize = false;
    std::string summary_fn;
};

void print_usage(int argc, char** argv);

#endif // _INPUTPARSER_H_NBODY_
