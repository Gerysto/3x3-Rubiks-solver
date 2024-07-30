#include "../headers/cube.hh"

Cube::Cube(){
    this->state = State();
    this->orientation = Orientation();
}


Cube::Cube(State state, Orientation orientation){
    this->state = state;
    this->orientation = orientation;
}


vector<u_int8_t> Cube::get_corners() {
    return state.get_corners();
}


vector<u_int8_t> Cube::get_edges() {
    return state.get_edges();
}


void Cube::turn_face(u_int8_t face_color, bool clockwhise){
    state.turn_face(face_color, clockwhise);
}


void Cube::turn_side(u_int8_t side, bool clockwhise, bool double_move){
    state.turn_face(orientation.get_face(side), clockwhise);
    if(double_move) state.turn_face(orientation.get_face(side), clockwhise);
}


void Cube::execute_sequence(string seq) {
    orientation.display();
    MoveSequence my_sequence(this->orientation, seq);
    orientation.display();
    my_sequence.print();
    state.execute_sequence(my_sequence);
}


void Cube::print_state() {
    state.display();
}