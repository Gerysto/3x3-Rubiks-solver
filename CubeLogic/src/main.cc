#include <iostream>
#include "../headers/cube.hh"
#include "../headers/move_sequence.hh"
using namespace std;


int main() {
    Orientation o;
    MoveSequence m;

    m.generate_random(20);
    m.print();
    cout << m.to_notation(o);
}