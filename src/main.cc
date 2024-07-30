#include <iostream>
#include "../headers/cube.hh"
using namespace std;

int main() {
    Cube c = Cube();
    c.execute_sequence("r U R' U' r' F R F'");
    c.print_state();
}