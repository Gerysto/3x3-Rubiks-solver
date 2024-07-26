#include <iostream>
#include "cube.cc"
using namespace std;

int main() {
    Cube c = Cube();
    c.turn_side(0, true, false);
    c.print_state();
}