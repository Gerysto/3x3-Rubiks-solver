#ifndef _SOLVER_
#define _SOLVER_
#include <queue>
#include <set>
#include "state.hh"
#include "mathlib.hh"


class Solver {
    
    public:
    
    State state;

    vector<int8_t> edge_orientation_lookup;
    vector<vector<int8_t>> domino_reduction_lookup;
    vector<vector<int8_t>> halfturn_reduction_lookup;
    vector<vector<int8_t>> final_solve_lookup;



    // Returns the cube's Edge Orientation Coordinate
    int get_EO_coordinate(const State& s);
    
    // Returns the cube's Domino Reduction Coordinates
    //    - first --> Corner orientation
    //    - second -> middle edge positions
    pair<int,int> get_DR_coordinate(const State& s);

    // Returns the Half-turn reduction coordinate
    //    - first --> Corner permutation 
    //    - second -> Edge permutation
    pair<int,int> get_HtR_coordinate(const State& s);

    // Returns the half-turn coordinate
    //    - first --> Corner permutation
    //    - second -> Edge permutation
    pair<int,int> get_final_coordinate(const State& s);


    // Returns the distance that a state is from the provided step's solved state. 
    int lookup_state_distance(const State& s, int step);

    // sets the distance of s in the lookup table from the provided step, to d.
    void set_state_distance(const State& s, int step, int d);

    void BFS_lookup_fill(const vector<string>& allowed_moves, int step);

    // Fills in the 'edge_orientation_lookup' table
    void fill_EO_lookup();

    // Fills in the 'domino_reduction_lookup' table
    void fill_DR_lookup();
    
    // Fills in the 'halfturn_reduction_lookup' table
    void fill_HtR_lookup();

    // Fills in the 'final_solve_lookup' table
    void fill_final_step_lookup();

    void solve_step(const State& s, MoveSequence& sol, const vector<string>& allowed_moves, int step);

    void solve_EO(const State& s, MoveSequence& m);
    
    void solve_DR(const State& s, MoveSequence& m);
    
    void solve_HtR(const State& s, MoveSequence& m);
    
    void solve_final_step(const State& s, MoveSequence& m);

    





    Solver(State state);

    MoveSequence solve();


    
};

#endif