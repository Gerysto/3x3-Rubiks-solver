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
/*
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
*/

    vector<int> decode_permutations(int corners, int edges) {
        int c0 = corners%24;
        int c1 = corners/24;
        int e0 = edges%24;
        int e1 = (edges/24)%24;
        int e2 = edges/(24*24);
        
        return {c1,c0,e2,e1,e0};
    }
    

    vector<int> get_parities(int corners, int edges) {
        int c0 = even_4_element_permutations[corners%24];
        int c1 = even_4_element_permutations[corners/24];
        int e0 = even_4_element_permutations[edges%24];
        int e1 = even_4_element_permutations[(edges/24)%24];
        int e2 = even_4_element_permutations[edges/(24*24)];
        return {c1,c0,e2,e1,e0};
    }

    int main() {
        State st;
        Orientation o;
        Solver s(st);
        MoveSequence m(o, "R2 U2 F2 B2"); 
        st.execute_sequence(m);
        st.display();
        
        pair<int,int> p = s.get_final_coordinate(st);
        State decoded = s.decode_final_coordinate(p.first, p.second);
        decoded.display();

        exit(1);


        s.fill_EO_lookup();
        s.fill_DR_lookup();
        s.fill_HtR_lookup();
        s.fill_final_step_lookup();

        //cerr << "FINISHED!!" << endl;

        
        int count = 0;
        MoveSequence scramble, sol1, sol2, sol3, sol4;
        scramble.generate_random(30);

        st.execute_sequence(scramble);
        s.solve_EO(st, sol1);

        st.execute_sequence(sol1);
        s.solve_DR(st, sol2);

        st.execute_sequence(sol2);
        s.solve_HtR(st, sol3);

        st.execute_sequence(sol3);
        s.solve_final_step(st, sol4);

        cout << "Scramble: " << scramble.to_notation(Orientation()) << endl;
        cout << "Part 1 Solution: " << sol1.to_notation(Orientation()) << endl;
        cout << "Part 2 Solution: " << sol2.to_notation(Orientation()) << endl;
        cout << "Part 3 Solution: " << sol3.to_notation(Orientation()) << endl;
        cout << "Part 4 Solution: " << sol4.to_notation(Orientation()) << endl;

        //cout << "Distance from solved: " << s.lookup_state_distance(st,1) << endl;

        count = 0;
        bool print = false;
        for (int i = 0; i < s.final_solve_lookup.size(); ++i) {
            for (int j = 0; j < s.final_solve_lookup[0].size(); ++j) {
                
                vector<int> v = get_parities(i,j);
                bool A = (v[2]+v[3]+v[4])%2 == 1;
                bool B = (v[0]+v[1])%2 == 1;
                bool C = binarySearch(problematic_numbers,i);
                if (!A and !B and !C) {
                    cout << i << ", " << j << "(" << v[0] << ", " << v[1] << ")";
                    cout << "(" << v[2] << ", " << v[3] << ", " << v[4] << ")";
                    if (int(s.final_solve_lookup[i][j]) < 0) {
                        cout << "<---";
                        ++count;
                    }
                    cout << endl;
                }
            }
        }

        // count = 0;
        // bool print = false;
        // for (int i = 0; i < s.final_solve_lookup.size(); ++i) {
        //     for (int j = 0; j < s.final_solve_lookup[0].size(); ++j) {
        //         
        //         vector<int> v = get_parities(i,j);
        //         bool A = (v[2]+v[3]+v[4])%2 == 1;
        //         bool B = (v[0]+v[1])%2 == 1;
        //         bool C = binarySearch(problematic_numbers,i);
        //         if (!A and !B and !C) {
        //             cout << i << ", " << j << "(" << v[0] << ", " << v[1] << ")";
        //             cout << "(" << v[2] << ", " << v[3] << ", " << v[4] << ")";
        //             if (int(s.final_solve_lookup[i][j]) < 0) {
        //                 cout << "<---";
        //                 ++count;
        //             }
        //             cout << endl;
        //         }
        //     }
        // }

        cerr << "Recompte de -1s: " << count << endl;
    }