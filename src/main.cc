#include <iostream>
#include "../headers/cube.hh"
#include "../headers/move_sequence.hh"
using namespace std;

const string edge_lettering_scheme =   "AQBMCIDERHTNJPLFWSVOUKXG";
const string corner_lettering_scheme = "AREBNQCJMDFIXHSWTOVPKULG";

const int corner_buffer = 2;
const int edge_buffer = 2;


int check_for_duplicates(State s) {
    for (int i = 0; i < s.edges.size(); ++i) {
        for (int j = 0; j < s.edges.size(); ++j) {
            if (i!=j and s.edges[i]/2 == s.edges[j]/2){
                cout << "ERROR!!! DUPLICATE EDGE PIECE!!";
                return -1;
            }
        }   
    }
    return 0;
}

int main() {
    Orientation default_orientation = Orientation();
    MoveSequence seq(default_orientation, string("F2 B R2 U' L2 U2 B' L' F2 U' B2 U L2 U R2 F2 L2 U' L2 F "));
    //cout << seq.to_notation(default_orientation);
    State s;
    s.execute_sequence(seq);

    string edge_letter_pairs, corner_letter_pairs;

    s.display();

    cout << "\nEdge letter pair sequence: " << endl;
    cin >> edge_letter_pairs;
    
    
    for (char c: edge_letter_pairs) {
        if (c > 'Z') c-='a'-'A';
        if (c < 'A' or c > 'X') continue;

        // Swap with buffer
        int edge_pos = edge_lettering_scheme.find(c);
        cout << edge_pos << " " << endl;

        int outer_edge = s.get_edge_stiker(edge_pos);
    
        int edge_in_buffer_pos = s.get_edge_stiker(edge_buffer);
        s.place_edge_stiker(outer_edge, edge_buffer);
        s.place_edge_stiker(edge_in_buffer_pos, edge_pos);
    }

    cout << "Corner letter pair sequence:" << endl;
    cin >> corner_letter_pairs;


    for (char c: corner_letter_pairs) {
        if (c > 'Z') c-='a'-'A';
        if (c < 'A' or c > 'X') continue;

        // Swap with buffer
        int corner_pos = corner_lettering_scheme.find(c);
        int outer_corner = s.get_corner_stiker(corner_pos);
        int corner_in_buffer_pos = s.get_corner_stiker(corner_buffer);
        s.place_corner_stiker(outer_corner, corner_buffer);
        s.place_corner_stiker(corner_in_buffer_pos, corner_pos);

    }
    cout << "\n";
    s.display();
}
