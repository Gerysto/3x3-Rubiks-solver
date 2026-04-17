#ifndef CUBE_CONTROLLER
#define CUBE_CONTROLLER

#include "cube.hh"

class CubeController {
    private:
        Cube cube;
        Solver solver;
    
    public:
    
    /**
     * Default constructor: Initializes the Cube to the solved state
     * It does not initialize the solver! This has to be done separately!
     */
    CubeController();

    /**
     * Fills all the heuristic tables requiered for solving the cube
     * by reading the tables stored in the precomputed tables it requieres.
    */ 
    void init_solver();

    /*
     * Given a move-sequence in the standard Rubik's cube notation, 
     * it performs set move-sequence to the cube. 
    */
    void execute_sequence_in_notation(const string& s);

    /**
     * Displays the state of the cube it's un-folded net. (Orientation doesn't affect it).
    */
    void print_state() const;


    /**
     *  Returns the cube to the solved state and default orientation.
     */
    void reset_cube_state(); 

    /**
     * Pre: Solver is already initialized
     * Post: Finds a set of moves that solves the cube and returns it in the standard
     * Rubik's Cube notation.
     */
    string find_solution();

    /**
     * Returns the cube state in a way that makes it slightly easier to draw.
     */
    vector<int> get_state_corners() const;

    vector<int> get_state_edges() const;

    string generate_random_scramble(int length) const; 

    bool is_scramble_correct(const string& s) const;
};


#endif