#ifndef _TREE_H_N_BODY_
#define _TREE_H_N_BODY_

#include <string>
#include <vector>
#include <array>

#include "../misc/body.h"

using std::vector; using std::array;

struct Cell {
    double min_bounds[3];
    double max_bounds[3];
    double m = 0;   // mass 
    double rm[3]; // center of mass
    Cell * subcells[8]; // eight subcells maximum
    bool inserted = false;
    const Body * b = nullptr;
    bool send_as_leaf = false;
    int list_idx = -1; 
    int parent_idx = -1;
};

class Tree {
public:
    /*
    constructs the tree

    @param min_bounds : minimum bounds of root cell
    @param max_bounds : maximum bounds of root cell
    */
    Tree(const double * min_bounds, const double * max_bounds, double theta);

    /*
    deletes the tree
    */
    ~Tree();

    /*
    inserts a body into the tree (expands it)

    @param pos : position of body
    @param m : mass of body
    */
    void insert_body(const double * pos, double m);
    
    /*
    inserts a body into the tree (expands it)
    */
    void insert_body(const Body * b);

    /*
    inserts an empty cell into the tree

    @param min_bounds : minimum bounds of cell
    @param max_bounds : maximum bounds of cell
    */
    void insert_emptycell(const double * min_bounds, const double * max_bounds);

    /*
    inserts a cell into the tree

    @param min_bounds : minimum bounds of cell
    @param max_bounds : maximum bounds of cell
    @param m : mass of cell
    @param rm : center of mass of cell
    */
    void insert_cell(const double * min_bounds, const double * max_bounds, double m, const double * rm);

    void insert_cell(Cell * cell);

    /*
    Traverse tree and find cells to send

    @param cell : root cell of subtree
    @param min_bounds : minimum bounds of cell to insert
    @param max_bounds : maximum bounds of cell to insert
    @param cells : cells to send (will be modified)
    */
    void cells_to_send(const double * min_bounds, const double * max_bounds,
                    int min_depth, vector<Cell*> & cells);

    /*
    Prunes the tree of subtrees which are not needed for evalutaing the force of
    a body in a given domain

    @param min_bounds : minimum bounds of domain
    @param max_bounds : maximum bounds of domain
    */
    void prune_tree(const double * min_bounds, const double * max_bounds);

    /*
    computes the force on a body

    @param pos : position of body
    @param m : mass of body
    */
    array<double, 3> compute_force(const Body * b);

    /*
    constructs string representation of tree
    */
    std::string to_string(bool fulltree=true) const;

    /*
    Mass of tree
    */
    double mass();

    /*
    Size of tree
    */
    int size(bool complete_tree=true);

    /* delete copy constructor */
    Tree(const Tree &) = delete;

    /* delete copy assignment */
    void operator = (const Tree &) = delete;

    /* delete move constructor */
    Tree(Tree &&) = delete;
    

private:
    /*
    insert body into subtree
    
    @param c : root cell of the tree
    @param pos : position of body
    @param m : mass of body
    */
    void insert_body(Cell * cell, const double * pos, double m);
    
    /*
    inserts a body into the tree (expands it)
    */
    void insert_body(Cell * c, const Body * b);
    
    /*
    inserts an empty cell into the tree

    @param cell : root cell of the subtree
    @param min_bounds : minimum bounds of cell
    @param max_bounds : maximum bounds of cell
    */
    void insert_emptycell(Cell * cell, const double * min_bounds, const double * max_bounds);
    
    /*
    inserts a cell into the tree

    @param cell : root cell of the tree
    @param min_bounds : minimum bounds of cell
    @param max_bounds : maximum bounds of cell
    @param m : mass of cell
    @param rm : center of mass of cell
    */
    void insert_cell(Cell * cell, const double * min_bounds, const double * max_bounds, double m, const double * rm);


    void insert_cell(Cell * cell, Cell * cell_to_insert);
    
    /*
    Opening criterion for a cell

    @param cell : cell to open or not
    @param min_bounds : minimum bounds of comparing domain
    @param max_bounds : maximum bounds of copmaring domain
    */
    bool opening_criterion(const Cell * cell, const double * min_bounds, const double * max_bounds);


    /*
    Traverse tree and find cells to send

    @param cell : root cell of subtree
    @param min_bounds : minimum bounds of cell to insert
    @param max_bounds : maximum bounds of cell to insert
    @param cells : cells to send (will be modified)
    */
    void cells_to_send(Cell * cell, Cell * parent, const double * min_bounds, const double * max_bounds, int min_depth, int depth, vector<Cell*> & cells);

    /*
    Prunes the tree of subtrees which are not needed for evalutaing the force of
    a body in a given domain

    @param cell : root cell of subtree
    @param min_bounds : minimum bounds of domain
    @param max_bounds : maximum bounds of domain
    */
    void prune_tree(Cell * cell, const double * min_bounds, const double * max_bounds);
    
    /*
    Delete descendants of a cell. Equivalent to calling delete_subtree
    on all a cells children.

    @param cell : cell which descendants shall be deleted
    */
    void delete_descendants(Cell * cell);

    /*
    Delete a subtree

    @param c : root cell of subtree
    */
    void delete_subtree(Cell * c);
    
    /*
    Computes the force on a body

    @param pos : position of body
    @param m : mass of body
    */
    array<double, 3> compute_force(const Cell * cell, const Body * b);

    /*
    Constructs string representation of subtree
    
    @param c : root cell of subtree
    */
    std::string subtree_str(Cell * c, bool fulltree) const;

    int size(Cell * c, bool complete_tree);

    /*
    root of the tree
    */
    Cell * root;

    /*
    parameter for opening criterion
    */
    double m_theta;

};

/*
Determines whether a coordinate is inside a cell

@param cell : cell to check
@param pos : position coordinate
*/
bool coord_in_cell(Cell * cell, const double * pos);

/*
Compares boundaries to a cell's boundaries

@param cell : cell to compare with
@param min_bounds : minimum boundaries
@param max_boudns : maximum boundaries
*/
bool same_cell(Cell * cell, const double * min_bounds, const double * max_bounds);

/*
Computes the volume of a cell

@param cell : cell to compute volume of
*/
double cell_volume(const Cell * cell);

/*
Determines if a domain is inside a cell

@param cell : cell to check
@param min_bounds : minimum bounds of the domain
@param max_bounds : maximum bounds of the domain
*/
bool bounds_in_cell(Cell * cell, const double * min_bounds, const double * max_bounds);

#endif // _TREE_H_N_BODY_
