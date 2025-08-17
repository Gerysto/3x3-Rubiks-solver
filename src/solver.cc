#include "../headers/solver.hh"


    Solver::Solver(State state) {
        this->state = state;
    }

    // Returns the cube's Edge Orientation Coordinate
    int get_EO_coordinate(State& s) {
        int k = 1;
        int EO = 0;

        // *the orientation of the last edge is determined by the rest of edges*
        for (int i = 0; i < s.edges.size()-1; ++i) {
            EO += k*(s.edges[i]%2);
            k*=2;
        }

        return EO;
    }

    bool is_edge_from_middle_layer(int edge) {
        return (edge >= 8 and edge <= 15);
    }

    // Returns the cube's Domino Reduction Coordinates
    //    - first --> Corner orientation
    //    - second -> middle edge positions
    pair<int,int> get_DR_coordinate(State& s) {
        
        // Corner orientation:
        int k = 1;
        int CO = 0;

        // *the orientation of the last corner is determined by the rest of corners*
        for (int i = 0; i < s.corners.size()-1; ++i) {
            CO += k*(s.corners[i]%3);
            k *= 3;
        }

        // Middle layer edge positions:
        int MLEP = 0;
        int middle_edge_count = 4;
        int N = s.edges.size();
        for (int i = 0; i < N; ++i) {
            if (is_edge_from_middle_layer(s.edges[i])) {
                MLEP += choose(N-i+1, middle_edge_count);
                middle_edge_count--;
            }
        }
    }

    // Returns the Half-turn reduction coordinate
    //    - first --> Corner permutation 
    //    - second -> Edge permutation
    pair<int,int> get_HtR_coordinate(State& s);

    // Returns the half-turn coordinate
    //    - first --> Corner permutation
    //    - second -> Edge permutation
    pair<int,int> get_final_coordinate(State& s);