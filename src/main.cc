#include <iostream>
#include "../headers/cube.hh"
#include "../headers/move_sequence.hh"
using namespace std;

int main() {
    Cube c = Cube();
    c.execute_sequence_in_notation("X R U R' U' R' F R2 U' R' U' R U R' F'");
    c.print_state();
}