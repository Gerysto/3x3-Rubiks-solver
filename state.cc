#include "headers/state.hh"

    State::State(){
        corners = solved_corners;
        edges = solved_edges;
    }

    void State::cycle_corners(vector<u_int8_t> stikers, bool clockwhise){
        int len = stikers.size();

        if(clockwhise) {

            for(int i = len-1; i > 0; --i) {
                u_int8_t A, B, C, D;
                A = corners[stikers[i-1]/3];
                B = stikers[i-1];
                C = stikers[i];
                D = A - A%3 + ((A%3 + B%3 - C%3)%3 + 3)%3;
                corners[C/3] = D;
            }

        } else {

            for(int i = 0; i < len-1; ++i) {
                u_int8_t A, B, C, D;
                A = corners[stikers[i+1]/3];
                B = stikers[i+1];
                C = stikers[i];
                D = A - A%3 + ((A%3 + B%3 - C%3)%3 + 3)%3;
                corners[C/3] = D;
            }
        }
    }

    void State::cycle_edges(vector<u_int8_t> stikers, bool clockwhise){
        int len = stikers.size();

        if(clockwhise) {

            for(int i = len-1; i > 0; --i) {
                u_int8_t A, B, C, D;
                A = corners[stikers[i-1]/2];
                B = stikers[i-1];
                C = stikers[i];
                D = A - A%2 + ((A%2 + B%2 - C%2)%2 + 2)%2;
                corners[C/2] = D;
            }

        } else {

            for(int i = 0; i < len-1; ++i) {
                u_int8_t A, B, C, D;
                A = corners[stikers[i+1]/2];
                B = stikers[i+1];
                C = stikers[i];
                D = A - A%2 + ((A%2 + B%2 - C%2)%2 + 2)%2;
                corners[C/2] = D;
            }
        }
    }

    void State::turn_face(u_int8_t face, bool clockwhise){
    }

    bool State::is_solved(){
    }

    bool State::is_solvable(){
    }

    void State::display(){
    }