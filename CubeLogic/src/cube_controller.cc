#include "../headers/cube_controller.hh"
#include <emscripten/bind.h>


/**
 * Default constructor: Initializes the Cube to the solved state
 * It does not initialize the solver! This has to be done separately!
 */
CubeController::CubeController() {
    this->cube = Cube();
}

/**
 * Performs all the precomputations requiered for solving the cube.
 * (This may take a long time, so it should be run assyncronously).
 */
void CubeController::init_solver() {
    this->solver.read_table_data();
}

void CubeController::set_state(const vector<int>& corners, const vector<int>& edges) {
    for (int i = 0; i < cube.state.corners.size(); ++i) cube.state.corners[i] = corners[i];
    for (int i = 0; i < cube.state.edges.size(); ++i) cube.state.edges[i] = edges[i];
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

vector<int> CubeController::get_state_corners() const{
    vector<int> res;
    for (const int x: cube.state.corners) {
        res.push_back((int) x);
    }
    return res;
}

vector<int> CubeController::get_state_edges() const{
    vector<int> res;
    for (const int x: cube.state.edges) {
        res.push_back((int) x);
    }
    return res;
}


string CubeController::generate_random_scramble(int length) const {
    MoveSequence m;
    m.generate_random(length);
    m.print();
    return m.to_notation(this->cube.orientation);
}  

bool CubeController::is_scramble_correct(const string& s) const {
    return MoveSequence::is_sequence_valid(s);
}

EMSCRIPTEN_BINDINGS(cube_controller) {
    emscripten::class_<CubeController>("CubeController")
        .constructor()
        .function("init_solver", &CubeController::init_solver)
        .function("set_state", &CubeController::set_state)
        .function("execute_sequence_in_notation", &CubeController::execute_sequence_in_notation)
        .function("print_state", &CubeController::print_state)
        .function("reset_cube_state", &CubeController::reset_cube_state)
        .function("find_solution", &CubeController::find_solution)
        .function("get_state_corners", &CubeController::get_state_corners)
        .function("get_state_edges", &CubeController::get_state_edges)
        .function("generate_random_scramble", &CubeController::generate_random_scramble)
        .function("is_scramble_correct", &CubeController::is_scramble_correct);

    emscripten::register_vector<int>("VectorInt");
}