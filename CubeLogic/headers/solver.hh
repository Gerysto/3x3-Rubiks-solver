#ifndef _SOLVER_
#define _SOLVER_
#include <queue>
#include <set>
#include <map>
#include "state.hh"
#include "mathlib.hh"


class Solver {
    
    private:
    
    bool is_initialized;

    public:
    
    vector<int8_t> edge_orientation_lookup;
    vector<vector<int8_t>> domino_reduction_lookup;
    vector<vector<int8_t>> halfturn_reduction_lookup;
    vector<vector<int8_t>> final_solve_lookup;

    // Constructor:
    Solver();

    // Fills all the lookup tables
    void init();

    // Given the coordinates of a state in the last step,
    // returns the state they correspond to
    State decode_final_coordinate(int corners, int edges);

    // Returns a boolean specifying whether it can be solved using
    // only half turns (R2, U2, F2, ...)
    bool isSolvableWithHalfTurns(const State& s);

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

    // Given a state `s` and a step index `step`,
    // if s is a solution for the step (`step`-1), this method
    // finds a solution of the next step. (Doesn't always work with last step!)
    void solve_step(const State& s, MoveSequence& sol, const vector<string>& allowed_moves, int step);


    void solve_EO(const State& s, MoveSequence& m);
    
    void solve_DR(const State& s, MoveSequence& m);
    
    void solve_HtR(const State& s, MoveSequence& m);
    
    void solve_final_step(const State& s, MoveSequence& m);

    MoveSequence find_full_solution(const State& s);

};

#endif