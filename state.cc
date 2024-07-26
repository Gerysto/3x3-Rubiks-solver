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
        
        vector<u_int8_t> corner_cycle;
        vector<u_int8_t> edge_cycle;

        if (face == 0) {
            corner_cycle = W_face_corner_cycle;
            edge_cycle   = W_face_edge_cycle;
        } 
        else if (face == 1) {
            corner_cycle = R_face_corner_cycle;
            edge_cycle   = R_face_edge_cycle;
        } 
        else if (face == 2) {
            corner_cycle = G_face_corner_cycle;
            edge_cycle   = G_face_edge_cycle;
        }
        else if (face == 3) {
            corner_cycle = Y_face_corner_cycle;
            edge_cycle   = Y_face_edge_cycle;
        }
        else if (face == 4) {
            corner_cycle = O_face_corner_cycle;
            edge_cycle   = O_face_edge_cycle;
        }
        else if (face == 5) {
            corner_cycle = B_face_corner_cycle;
            edge_cycle   = B_face_edge_cycle;
        }
        
        cycle_corners(corner_cycle, clockwhise);
        cycle_edges(edge_cycle, clockwhise);
    }

    bool State::is_solved(){
        return corners == solved_corners and edges == solved_edges;
    }

    bool State::is_solvable(){
        // TODO!
    }

    void State::display(){
        cout << "Corners: " << endl;
        for(int i = 0; i < corners.size(); ++i) {
            cout << corners[i] << " ";
        }
        for(int i = 0; i < edges.size(); ++i) {
            cout << edges[i] << " ";
        }
    }