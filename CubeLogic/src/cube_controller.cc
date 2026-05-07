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

void CubeController::set_state(const vector<int>& corners, const vector<int>& edges, const vector<int>& orientation) {
    for (int i = 0; i < cube.state.corners.size(); ++i) cube.state.corners[i] = corners[i];
    for (int i = 0; i < cube.state.edges.size(); ++i) cube.state.edges[i] = edges[i];
    vector<u_int8_t> orientation_uint8(6);
    for (int i = 0; i < orientation.size(); ++i) orientation_uint8[i] = orientation[i];
    cube.orientation.set_side_to_face(orientation_uint8);
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

vector<int> CubeController::get_cube_orientation() const{
    vector<int> res;
    vector<uint8_t> o = cube.orientation.get_side_to_face();
    for (const int x: o) {
        res.push_back(x);
    }
    cout << endl;
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

/**
 * Given a move sequence `seq` and two orientations `O_origin`, `O_dest`, i
 * t aplies the move sequence to a cube in the `O_origin` orientation
 * and returns the equivalent move sequence in the `O_dest` orientation.
 */
string CubeController::translate_move_sequence_from_default_to_orientation(const string& seq, const vector<int>& O_origin, const vector<int>& O_dest) {
    Orientation O1, O2;

    O1.set_side_to_face(vector<u_int8_t>(O_origin.begin(), O_origin.end()));
    O2.set_side_to_face(vector<u_int8_t>(O_dest.begin(), O_dest.end()));

    MoveSequence m = MoveSequence(O1, seq);
    cout << "WE'RE ENTERING THE TRANSLATE FUNCTION!!!" << seq << endl;
    return m.to_notation(O2);
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
        .function("get_cube_orientation", &CubeController::get_cube_orientation)
        .function("generate_random_scramble", &CubeController::generate_random_scramble)
        .class_function("translate_move_sequence_from_default_to_orientation", &CubeController::translate_move_sequence_from_default_to_orientation)
        .function("is_scramble_correct", &CubeController::is_scramble_correct);

    emscripten::register_vector<int>("VectorInt");
}