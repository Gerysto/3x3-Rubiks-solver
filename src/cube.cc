#include "../headers/cube.hh"
#include "cube.hh"

Cube::Cube(){
    this->state = State();
    this->orientation = Orientation();
}


Cube::Cube(State state, Orientation orientation){
    this->state = state;
    this->orientation = orientation;
}

void Cube::execute_sequence(MoveSequence move_sequence) {
    state.execute_sequence(move_sequence);
}

void Cube::execute_sequence_in_notation(string seq) {
    orientation.display();
    MoveSequence my_sequence(this->orientation, seq);
    orientation.display();
    my_sequence.print();
    state.execute_sequence(my_sequence);
}

bool Cube::is_solvable() {
    return state.is_solvable();
}

void Cube::print_state() const {
    state.display();
}