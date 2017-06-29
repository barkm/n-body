# n-body

Parallel Barnes-Hut Algorithm

## Description

Program for simulating N-body systems. The algorithm is a parallel implemenation of the [_Barnes-Hut algorithm_](https://www.nature.com/nature/journal/v324/n6096/abs/324446a0.html) inspired by [_Salmon, John K.  Parallel hierarchical N-body methods. Diss. California Institute of Technology, 1991_](http://thesis.library.caltech.edu/6291/). The program can run on 2<sup>d</sup> process using MPI. 

## Installation

Install a MPI library such as [OpenMPI](https://www.open-mpi.org/) or [MPICH](https://www.mpich.org/). 

```
$ brew install mpich
```

Download the git repository and compile with `make`

```
$ git clone https://github.com/pbarkm/n-body.git  
$ cd n-body  
$ make  
```
 
To check if the program runs (on 2 processes)

```
$ mpirun -np 2 ./main.out
```

The supplied python files for plotting require `matplotlib` and `numpy`.

## Running

To display the command line options run

```
$ mpirun -np 1 ./main.out -?
```

The following command runs a simulation of 1000 bodies for 10000 time steps. The sampled positions of the bodies are stored in positions.txt and the program is run with the verbose flag (-v).

```
$ mpirun -np 2 ./main.out -N 1000 -s 10000 -v -o positions.txt
```

A python script is supplied to animate the simulation.

```
$ python py/plot.py positions.txt
```



