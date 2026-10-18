#include "../headers/cube.hh"
#include <algorithm>

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
    Orientation copy = orientation;
    MoveSequence my_sequence = MoveSequence(copy, seq);
    orientation = copy;
    state.execute_sequence(my_sequence);
}

void Cube::random_scramble(int length) {
    MoveSequence rand = MoveSequence();
    rand.generate_random(length);

    state.execute_sequence(rand);
}

bool Cube::is_solvable() {
    return state.is_solvable();
}

void Cube::print_state() const {
    state.display();
}

bool cmp(MoveSequence m1, MoveSequence m2) {
    return m1.size() < m2.size();
}
