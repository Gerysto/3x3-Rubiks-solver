#include <iostream>
#include "../headers/cube.hh"
#include "../headers/move_sequence.hh"
using namespace std;

int main() {
    Cube c = Cube();
    MoveSequence m = c.test_solver(0);
    c.execute_sequence(m);
}