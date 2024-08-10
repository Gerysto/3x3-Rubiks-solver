#include <iostream>
#include "../headers/cube.hh"
#include "../headers/move_sequence.hh"
using namespace std;

int main() {
    for(int i = 0; i < 16; ++i) {
        Cube c = Cube();
        MoveSequence m = c.test_solver(i);
        c.execute_sequence(m);
    }
    
}