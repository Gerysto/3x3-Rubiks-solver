#include <iostream>
#include "../headers/cube.hh"
#include "../headers/move_sequence.hh"
#include <set>
using namespace std;


    int main() {
        State st;
        Orientation o;
        Solver s(st);

        s.fill_EO_lookup();
        cerr << "Finished Step 1 table";
        s.fill_DR_lookup();
        cerr << "Finished Step 2 table";
        s.fill_HtR_lookup();
        cerr << "Finished Step 3 table";
        s.fill_final_step_lookup();
        cerr << "Finished Step 4 table";
    
        srand(time(0));

        vector<string> scrambles = {};

        for (int i = 0; i < 1; ++i) {
            MoveSequence scramble, sol1, sol2, sol3, sol4;
            st = State();

            scramble = MoveSequence(o, "");
            //st.display();
            st.execute_sequence(scramble);
            State scrambled = st;
            s.solve_EO(st, sol1);

            st.execute_sequence(sol1);
            State sol1_state = st;
            s.solve_DR(st, sol2);

            st.execute_sequence(sol2);
            State sol2_state = st;
            s.solve_HtR(st, sol3);

            st.execute_sequence(sol3);
            State sol3_state = st;
            s.solve_final_step(st, sol4);

            st.execute_sequence(sol4);
            State sol4_state = st;
            



            cout << "Scramble: " << scramble.to_notation(Orientation()) << endl;
            cout << "Part 1 Solution: " << sol1.to_notation(Orientation()) << endl;
            cout << "Part 2 Solution: " << sol2.to_notation(Orientation()) << endl;
            cout << "Part 3 Solution: " << sol3.to_notation(Orientation()) << endl;
            cout << "Part 4 Solution: " << sol4.to_notation(Orientation()) << endl;
            
            cout << "------------------------------------------------------------------------------------\n";

            //scrambled.display();
            //cout << endl;
            //sol1_state.display();
            //cout << endl;
            //sol2_state.display();
            //cout << endl;
            //sol3_state.display();
            //cout << endl;
            //sol4_state.display();
            //cout << endl;
        }


    }