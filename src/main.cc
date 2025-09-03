#include <iostream>
#include "../headers/cube.hh"
#include "../headers/move_sequence.hh"
using namespace std;


int main() {

    Cube c;
    c.execute_sequence_in_notation("r U R' U' M2 U R U' R' U' M'");
    c.print_state();

    Solver s;
    MoveSequence m = s.find_full_solution(c.state);
    cout << m.to_notation(c.orientation) << endl;
}