#include <iostream>
#include "headers/cube.hh"
using namespace std;

int main() {
    Cube c = Cube();
    c.move_sequence("M2 U' M2 U2 M2 U' M2");
    c.print_state();
}