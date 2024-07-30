#include <iostream>
#include "../headers/cube.hh"
using namespace std;

int main() {
    Cube c = Cube();
    c.execute_sequence("S2 M2 E2");
    c.print_state();
}