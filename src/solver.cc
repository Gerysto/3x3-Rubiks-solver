#include "../headers/solver.hh"


    Solver::Solver(State state) {
        this->state = state;
    }




    // Returns the cube's Edge Orientation Coordinate
    int Solver::get_EO_coordinate(const State& s) {
        int k = 1;
        int EO = 0;

        // *the orientation of the last edge is determined by the rest of edges*
        for (int i = 0; i < s.edges.size()-1; ++i) {
            EO += k*(int(s.edges[i])%2);
            k*=2;
        }

        return EO;
    }

    bool is_edge_from_E_slice(int edge) {
        return (edge >= 8 and edge <= 15);
    }
    
    bool is_edge_from_S_slice(int edge) {
        int e = edge/2;
        return (e == 1 or e == 3 or e == 9 or e == 11);
    }
    
    bool is_edge_from_M_slice(int edge) {
        int e = edge/2;
        return (e == 0 or e == 2 or e == 8 or e == 10);
    }

    // Returns the cube's Domino Reduction Coordinates
    //    - first --> Corner orientation
    //    - second -> middle edge positions
    pair<int,int> Solver::get_DR_coordinate(const State& s) {
        
        // Corner orientation:
        int k = 1;
        int CO = 0;

        // *the orientation of the last corner is determined by the rest of corners*
        for (int i = 0; i < s.corners.size()-1; ++i) {
            CO += k*(s.corners[i]%3);
            k *= 3;
        }

        // S slice edge position coordinate:
        int ESEPC = 0;
        int middle_edge_count = 4;
        int N = s.edges.size();
        for (int i = 0; i < N; ++i) {
            if (is_edge_from_E_slice(s.edges[i])) {
                if (N-i != middle_edge_count) ESEPC += choose(N-i-1, middle_edge_count);
                middle_edge_count--;
            }
        }
        return {CO, ESEPC};
    }

    bool corner_belongs_in_WBO_orbit(int corner) {
        int c = corner/3;
        return (c == 0 or c == 2 or c == 5 or c == 7);
    }

    // Returns the Half-turn reduction coordinate
    //    - first --> Corner permutation 
    //    - second -> Edge permutation
    pair<int,int> Solver::get_HtR_coordinate(const State& s) {
        
        // When using double moves, there are only 2 orbits along which corners can move.
        // Each orbit has only 4 pieces. Here, we're going to measure the positions of the 
        // pieces in the same orbit as the WBO piece.
        
        // corner orbit position coordinate
        int COPC = 0;
        int orbit_corner_count = 4;
        int N = 8;
        for (int i = 0; i < s.corners.size(); ++i) {
            
            if (corner_belongs_in_WBO_orbit(s.corners[i])) {
                if (N-i != orbit_corner_count) COPC += choose(N-i-1, orbit_corner_count);
                orbit_corner_count--;
            }
        }
        
        // M slice edge position coordinate
        int MSEPC = 0;
        int middle_edge_count = 4;
        int j = 0;
        N = 8;
        for (int i = 0; i < s.edges.size(); ++i) {
            // all 4 'E' layer edges are already in place.
            if (i > 3 and i < 8) continue; 
            
            if (is_edge_from_M_slice(s.edges[i])) {
                if (N-j != middle_edge_count) MSEPC += choose(N-j-1, middle_edge_count);
                middle_edge_count--;
            }
            j++;
        }
        
        return {COPC, MSEPC};
    }

    int get_subset_permutation_rank(const vector<u_int8_t>& v, const vector<int>& subset) {
        int rank = 0;
        for (int i = 0; i < subset.size(); ++i) {
            int countSmaller = 0;
            
            for (int j = i + 1; j < subset.size(); j++) {
                if (v[subset[j]] < v[subset[i]]) countSmaller++;
            }
            rank += countSmaller * factorial(subset.size() - i - 1);
        }
        return rank;
    }

    // Returns the half-turn coordinate
    //    - first --> Corner permutation
    //    - second -> Edge permutation
    pair<int,int> Solver::get_final_coordinate(const State& s) {
        const vector<int> WBO_orbit = {0,2,5,7};
        const vector<int> WBR_orbit = {1,3,4,6};

        const vector<int> S_edge_orbit = {1,3,9,11};
        const vector<int> M_edge_orbit = {0,2,8,10};
        const vector<int> E_edge_orbit = {4,5,6,7};
        
        int WBO_coord = get_subset_permutation_rank(s.corners, WBO_orbit);
        int WBR_coord = get_subset_permutation_rank(s.corners, WBR_orbit);

        int S_edges_coord = get_subset_permutation_rank(s.edges, S_edge_orbit);
        int E_edges_coord = get_subset_permutation_rank(s.edges, E_edge_orbit);
        int M_edges_coord = get_subset_permutation_rank(s.edges, M_edge_orbit);

        return {
            WBO_coord*24+WBR_coord,
            S_edges_coord*24*24+
            E_edges_coord*24+
            M_edges_coord
        };
    }


    // Returns the distance that a state is from the provided step's solved state. 
    int Solver::lookup_state_distance(const State& s, int step) {
        int n;
        pair<int,int> p;
        switch(step) {
            case 0:
                n = get_EO_coordinate(s);
                return edge_orientation_lookup[n];
            case 1:
                p = get_DR_coordinate(s);
                return domino_reduction_lookup[p.first][p.second];
            case 2:
                p = get_HtR_coordinate(s);
                return halfturn_reduction_lookup[p.first][p.second];
            case 3:
                p = get_final_coordinate(s);
                return final_solve_lookup[p.first][p.second];
            default:
                cerr << "Invalid step! Must be between 0 and 3." << endl;
                return -1;
        }
    }


    // sets the distance of s in the lookup table from the provided step, to d.
    void Solver::set_state_distance(const State& s, int step, int d) {
        int n;
        pair<int,int> p;
        switch(step) {
            case 0:
                n = get_EO_coordinate(s);
                edge_orientation_lookup[n] = d;
                return;
            case 1:
                p = get_DR_coordinate(s);
                domino_reduction_lookup[p.first][p.second] = d;
                return;
            case 2:
                p = get_HtR_coordinate(s);
                halfturn_reduction_lookup[p.first][p.second] = d;
                return;
            case 3:
                p = get_final_coordinate(s);
                final_solve_lookup[p.first][p.second] = d;
                return;
            default:
                cerr << "Invalid step! Must be between 0 and 3." << endl;
                return;
        }
    }

    void Solver::BFS_lookup_fill(const vector<string>& allowed_moves, int step) {
        Orientation O;
        queue<State> current_states;
        queue<int> distances;
        
        State solved;
        set_state_distance(solved,step,0);
        current_states.push(solved);
        distances.push(0);
        int i = 0;
        while (not current_states.empty()) {
            //cerr << i << endl;
            ++i;
            State s = current_states.front();
            int d = distances.front();
            current_states.pop();
            distances.pop();

            for(string move : allowed_moves) {
                MoveSequence m = MoveSequence(O, move);
                State new_s = s;
                new_s.execute_sequence(m);
                if (lookup_state_distance(new_s,step) == -1) {
                    set_state_distance(new_s, step, d+1);
                    current_states.push(new_s);
                    distances.push(d+1);
                }
            }
        }
    }

    // Fills in the 'edge_orientation_lookup' table
    void Solver::fill_EO_lookup() {
        edge_orientation_lookup = vector<int8_t>(2048,-1);
        vector<string> allowed_moves = {"R", "R'", "R2", "L", "L'", "L2", "U", "U'", "U2", "D", "D'", "D2", "F", "F'", "F2", "B", "B'", "B2"};
        BFS_lookup_fill(allowed_moves,0);
    }

    // Fills in the 'domino_reduction_lookup' table
    void Solver::fill_DR_lookup() {
        domino_reduction_lookup = vector<vector<int8_t>>(2187,vector<int8_t>(495, -1));
        vector<string> allowed_moves = {"R", "R'", "R2", "L", "L'", "L2", "U", "U'", "U2", "D", "D'", "D2", "F2", "B2"};
        BFS_lookup_fill(allowed_moves,1);
    }
    
    // Fills in the 'halfturn_reduction_lookup' table
    void Solver::fill_HtR_lookup() {
        halfturn_reduction_lookup = vector<vector<int8_t>>(70,vector<int8_t>(70, -1));
        vector<string> allowed_moves = {"R2", "L2", "U", "U'", "U2", "D", "D'", "D2", "F2", "B2"};
        BFS_lookup_fill(allowed_moves,2);

    }

    // Fills in the 'final_solve_lookup' table
    void Solver::fill_final_step_lookup() {
        final_solve_lookup = vector<vector<int8_t>>(576,vector<int8_t>(13824, -1));
        vector<string> allowed_moves = {"R2", "L2", "U2", "D2", "F2", "B2"};
        BFS_lookup_fill(allowed_moves, 3);
    }

    void print_state_code(Solver& s, const State& st, int step) {
        if (step == 1) {
            pair<int,int> p = s.get_DR_coordinate(st);
            cout << p.first << ", " << p.second;
        }
    }
    
    void Solver::solve_step(const State& s, MoveSequence& sol, const vector<string>& allowed_moves, int step) {
        Orientation O;
        int d0 = lookup_state_distance(s, step);
        if (d0 == 0) return;
        cout << "d0 = " << d0 << "--> ";
        for (string m: allowed_moves) {
            State new_s = s;
            MoveSequence new_move = MoveSequence(O,m);
            new_s.execute_sequence(new_move);
            int d1 = lookup_state_distance(new_s,step);
            cout << d1 << ", ";
            //print_state_code(*this, new_s, step);
            if (d1 < d0) {
                sol = sol.append(new_move);
                cout << endl;
                solve_step(new_s, sol, allowed_moves, step);
                return;
            }
        }
        cout << endl;
    }

    void Solver::solve_EO(const State& s, MoveSequence& sol) {
        vector<string> allowed_moves = {"R", "R'", "R2", "L", "L'", "L2", "U", "U'", "U2", "D", "D'", "D2", "F", "F'", "F2", "B", "B'", "B2"};
        solve_step(s,sol,allowed_moves,0);
    }
    
    void Solver::solve_DR(const State& s, MoveSequence& sol) {
        vector<string> allowed_moves = {"R", "R'", "R2", "L", "L'", "L2", "U", "U'", "U2", "D", "D'", "D2", "F2", "B2"};
        solve_step(s,sol,allowed_moves,1);
    }
    
    void Solver::solve_HtR(const State& s, MoveSequence& sol) {
        vector<string> allowed_moves = {"R2", "L2", "U", "U'", "U2", "D", "D'", "D2", "F2", "B2"};
        solve_step(s,sol,allowed_moves,2);
    }
    
    void Solver::solve_final_step(const State& s, MoveSequence& sol) {
        vector<string> allowed_moves = {"R2", "L2", "U2", "D2", "F2", "B2"};
        solve_step(s,sol,allowed_moves,3);
    }
