CC = mpic++
RUN = mpirun
FLAGS = -g -Wall -pedantic -std=c++11
NP = 2
PY = python3
OPT = 0

ifeq ($(OPT),1)
	FLAGS = -g -Wall -pedantic -std=c++11 -O3
endif

all : orb.o tree.o build_tree.o

orb.o : orb.cpp orb.h ../misc/utils.h ../misc/mpi_types.h ../misc/body.h
	$(CC) $(FLAGS) -c orb.cpp

tree.o : tree.cpp tree.h ../misc/utils.h ../misc/model.h
	$(CC) $(FLAGS) -c tree.cpp

build_tree.o : build_tree.cpp build_tree.h ../misc/body.h ../misc/utils.h tree.h
	$(CC) $(FLAGS) -c build_tree.cpp

clean : 
	rm -fr *.dSYM *.o *.out
