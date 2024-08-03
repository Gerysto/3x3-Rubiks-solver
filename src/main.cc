#include <iostream>
#include "../headers/cube.hh"
#include "../headers/move_sequence.hh"
using namespace std;

int main() {
    for(int i = 0; i < 100; ++i) {
        Cube c = Cube();
        c.random_scramble(40);
        if(c.is_solvable()) cout << "THE CUBE IS SOLVABLE!" << endl;
        else cout << "THE CUBE IS UNSOLVABLE" << endl;  
    }
}