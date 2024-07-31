#include <iostream>
#include "../headers/cube.hh"
using namespace std;

int main() {
    Cube c = Cube();
    c.execute_sequence_in_notation("r U R' U' r' F R F'");
    cout << c.is_solvable();
    c.print_state();
}