#include "../headers/cube_controller.hh"
#include <emscripten/bind.h>

/**
 * Default constructor: Initializes the Cube to the solved state
 * It does not initialize the solver! This has to be done separately!
 */
CubeController::CubeController() {
    this->cube = Cube();
    this->solver = Solver();
}

/**
 * Performs all the precomputations requiered for solving the cube.
 * (This may take a long time, so it should be run assyncronously).
 */
void CubeController::init_solver() {
    this->solver.init();
}

/*
    * Given a move-sequence in the standard Rubik's cube notation, 
    * it performs set move-sequence to the cube. 
*/
void CubeController::execute_sequence_in_notation(const string& s) {
    cube.execute_sequence_in_notation(s);
}

/**
 * Displays the state of the cube it's un-folded net. (Orientation doesn't affect it).
*/
void CubeController::print_state() const {
    cube.print_state();
}


/**
 *  Returns the cube to the solved state and default orientation.
 */
void CubeController::reset_cube_state() {
    this->cube = Cube();
}

/**
 * Pre: Solver is already initialized
 * Post: Finds a set of moves that solves the cube and returns it in the standard
 * Rubik's Cube notation.
 */
string CubeController::find_solution() {    
    // Solver is already initialized:
    MoveSequence m = solver.find_full_solution(cube.state);
    return m.to_notation(cube.orientation);
}

/**
 * Returns the cube state in a way that makes it slightly easier to draw.
 */
vector<u_int8_t> CubeController::get_cube_state() const{
    // TODO!
    cout << "TODO!!!!" << endl;
    return {};
}


EMSCRIPTEN_BINDINGS(cube_controller) {
    emscripten::class_<CubeController>("CubeController")
        .constructor()
        .function("init_solver", &CubeController::init_solver)
        .function("execute_sequence_in_notation", &CubeController::execute_sequence_in_notation)
        .function("print_state", &CubeController::print_state)
        .function("reset_cube_state", &CubeController::reset_cube_state)
        .function("find_solution", &CubeController::find_solution)
        .function("get_cube_state", &CubeController::get_cube_state);
    }
