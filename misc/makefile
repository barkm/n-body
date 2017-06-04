CC = mpic++
RUN = mpirun
FLAGS = -g -Wall -pedantic -std=c++11
NP = 2
PY = python3

ifeq ($(OPT),1)
	FLAGS = -g -Wall -pedantic -std=c++11 -O3
endif

all : body.o mpi_types.o utils.o model.o readwrite.o inputparser.o gen_bodies.o

body.o : body.cpp body.h
	$(CC) $(FLAGS) -c body.cpp

mpi_types.o : mpi_types.cpp mpi_types.h
	$(CC) $(FLAGS) -c mpi_types.cpp

utils.o : utils.cpp utils.h
	$(CC) $(FLAGS) -c utils.cpp

model.o : model.cpp model.h
	$(CC) $(FLAGS) -c model.cpp

readwrite.o : readwrite.cpp readwrite.h body.h inputparser.h
	$(CC) $(FLAGS) -c readwrite.cpp

inputparser.o : inputparser.cpp inputparser.h ../tree/tree.h
	$(CC) $(FLAGS) -c inputparser.cpp

gen_bodies.o : gen_bodies.cpp gen_bodies.h body.h
	$(CC) $(FLAGS) -c gen_bodies.cpp

clean : 
	rm -fr *.dSYM *.o *.out
