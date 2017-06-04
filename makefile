CC = mpic++
RUN = mpirun
FLAGS := -g -Wall -pedantic -std=c++11
NP = 2
PY = python3
SUBDIRS = tree misc


ifeq ($(OPT),1)
	FLAGS = -g -Wall -pedantic -std=c++11 -O3
endif


all : makesubdirs main.out

main.out : main.o
	$(CC) $(FLAGS) -o main.out main.o misc/body.o misc/mpi_types.o misc/utils.o misc/model.cpp tree/tree.o  tree/orb.o tree/build_tree.o misc/readwrite.o misc/inputparser.o misc/gen_bodies.o

main.o : main.cpp misc/body.h misc/mpi_types.h tree/orb.h tree/build_tree.h tree/tree.h misc/readwrite.h misc/inputparser.h
	$(CC) $(FLAGS) -c main.cpp

.PHONY: makesubdirs subdirs $(SUBDIRS) clean main.out opt

makesubdirs :
	make subdirs MAKECMD=all

cleansubdirs :
	make subdirs MAKECMD=clean


clean : cleansubdirs
	rm -fr *.dSYM *.o *.out

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMD)
