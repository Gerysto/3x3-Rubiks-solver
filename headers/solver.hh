#ifndef _SOLVER_
#define _SOLVER_
#include <queue>
#include <set>
#include "state.hh"
#include "mathlib.hh"


class Solver {
    
    private:
    
    State state;

    vector<u_int8_t> edge_orientation_lookup;
    vector<vector<u_int8_t>> domino_reduction_lookup;
    vector<vector<u_int8_t>> halfturn_reduction_lookup;
    vector<vector<u_int8_t>> final_solve_lookup;

    // Returns the cube's Edge Orientation Coordinate
    int get_EO_coordinate(State& s);
    
    // Returns the cube's Domino Reduction Coordinates
    //    - first --> Corner orientation
    //    - second -> middle edge positions
    pair<int,int> get_DR_coordinate(State& s);

    // Returns the Half-turn reduction coordinate
    //    - first --> Corner permutation 
    //    - second -> Edge permutation
    pair<int,int> get_HtR_coordinate(State& s);

    // Returns the half-turn coordinate
    //    - first --> Corner permutation
    //    - second -> Edge permutation
    pair<int,int> get_final_coordinate(State& s);

    // Fills in the 'edge_orientation_lookup' table
    void fill_EO_lookup();

    // Fills in the 'domino_reduction_lookup' table
    void fill_DR_lookup();
    
    // Fills in the 'halfturn_reduction_lookup' table
    void fill_HtR_lookup();

    // Fills in the 'final_solve_lookup' table
    void fill_final_step_lookup();

    void solve_EO(State& s, MoveSequence& m);
    
    void solve_DR(State& s, MoveSequence& m);
    
    void solve_HtR(State& s, MoveSequence& m);
    
    void solve_final_step(State& s, MoveSequence& m);

    




    public:

    Solver(State state);

    MoveSequence solve();


    
};

#endif