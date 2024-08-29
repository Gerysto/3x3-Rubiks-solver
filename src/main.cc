#include <iostream>
#include "../headers/cube.hh"
#include "../headers/move_sequence.hh"
using namespace std;

int main() {
    Cube c = Cube();
    c.random_scramble(10);
    c.print_state();
    MoveSequence m = c.test_solver(1);
    c.execute_sequence(m);
    c.print_state();
}
