#include <iostream>
#include "headers/cube.hh"
using namespace std;

int main() {
    for(int i = 0; i < 6; ++i) {
        string wait;
        cin >> wait;
        Cube c = Cube();
        cout << "\n\n\n";
        cout << "PERFORMING MOVE " << i << "\n\n";
        c.turn_side(i,true,false);
        c.print_state();
    }
    
}