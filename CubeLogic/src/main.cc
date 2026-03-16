#include <iostream>
#include "../headers/cube.hh"
#include "../headers/move_sequence.hh"
using namespace std;


int main() {
    Solver s;
    Cube c;

    Orientation o;
    MoveSequence m;

    //s.compute_and_store_table_data();
    s.read_table_data();

    for (int i = 0; i < 10; ++i) {
        m.generate_random(100);
        c.execute_sequence(m);
        MoveSequence mp = s.find_full_solution(c.state);
        cout << mp.to_notation(o) << endl;
        c.execute_sequence(mp);
        auto dr = s.get_DR_coordinate(c.state);
        auto htr = s.get_HtR_coordinate(c.state);
        auto fin = s.get_final_coordinate(c.state);
        cout << "DR coord: " << dr.first << ", " << dr.second << endl;
        cout << "HtR coord: " << htr.first << ", " << htr.second << endl;
        cout << "final coord: " << fin.first << ", " << htr.second << endl;

        c.state.display();
    }
    
}