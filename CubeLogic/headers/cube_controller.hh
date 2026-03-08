#ifndef CUBE_CONTROLLER
#define CUBE_CONTROLLER

#include "cube.hh"

class CubeController {
    private:
        Cube cube;
        Solver solver;
        bool solver_initialized;
    
    public:
    
    /**
     * Default constructor: Initializes the Cube to the solved state
     * It does not initialize the solver! This has to be done separately!
     */
    CubeController();

    /**
     * Performs all the precomputations requiered for solving the cube.
     * (This may take a long time, so it should be run assyncronously).
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
    vector<u_int8_t> get_cube_state() const;

};


#endif