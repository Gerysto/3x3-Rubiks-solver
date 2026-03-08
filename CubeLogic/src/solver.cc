#include "../headers/solver.hh"

    Solver::Solver() {
        bool is_initialized = false;
    }

    // Fills all the lookup tables
    void Solver::init() {
        fill_EO_lookup();
        cerr << "Finished Step 1 table" << endl;
        fill_DR_lookup();
        cerr << "Finished Step 2 table" << endl;
        fill_HtR_lookup();
        cerr << "Finished Step 3 table" << endl;
        fill_final_step_lookup();
        cerr << "Finished Step 4 table" << endl;
        is_initialized = true;
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


    bool get_corner_permutation_parity(const State& s) {
        vector<u_int8_t> permutation(8);
        for (int i = 0; i < s.corners.size(); ++i) {
            permutation[i] = s.corners[i]/3;
        }
        vector<int> subset = {0,1,2,3,4,5,6,7};
        int rank = get_subset_permutation_rank(permutation, subset);
        return ((rank+1)/2)%2;
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

        //int c_parity = get_corner_permutation_parity(s);
        return {COPC, MSEPC};
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


    State Solver::decode_final_coordinate(int corners, int edges) {
        vector<int> c0 = permutations[corners%24];
        vector<int> c1 = permutations[corners/24];
        vector<int> e0 = permutations[edges%24];
        vector<int> e1 = permutations[(edges/24)%24];
        vector<int> e2 = permutations[edges/(24*24)];


        vector<int> WBO = {0,6,15,21}; // WBO_corner_orbit_stikers
        vector<int> WBR = {3,9,12,18}; // WBR_corner_orbit_stikers
        vector<int> M =  {0,4,16,20}; // M_slice_stikers
        vector<int> S =  {2,6,18,22}; // S_slice_stikers
        vector<int> E = {8,10,12,14}; // E_slice_stikers

        vector<vector<int>> corner_perms = {c1,c0};
        vector<vector<int>> edge_perms = {e2,e1,e0};

        vector<vector<int>> corner_orbits = {WBO, WBR};
        vector<vector<int>> edge_orbits = {S,E,M};

        State s;

        for (int i = 0; i < corner_perms.size(); ++i) {
            for(int j = 0; j < corner_perms[i].size(); ++j){
                s.corners[corner_orbits[i][j]/3] = corner_orbits[i][corner_perms[i][j]]; 
            }
        }
        
        for (int i = 0; i < edge_perms.size(); ++i) {
            vector<u_int8_t> cycle(4);
            for(int j = 0; j < edge_perms[i].size(); ++j){
                s.edges[edge_orbits[i][j]/2] = edge_orbits[i][edge_perms[i][j]]; 
            }
        }
        return s;
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
        for (string m: allowed_moves) {
            State new_s = s;
            MoveSequence new_move = MoveSequence(O,m);
            new_s.execute_sequence(new_move);
            int d1 = lookup_state_distance(new_s,step);
            if (d1 < d0) {
                sol = sol.append(new_move);
                solve_step(new_s, sol, allowed_moves, step);
                return;
            }
        }
    }

    bool Solver::isSolvableWithHalfTurns(const State& s) {
        pair<int,int> coord = get_final_coordinate(s);
        return final_solve_lookup[coord.first][coord.second] != -1;
        //return false; 
    }

    void Solver::solve_EO(const State& s, MoveSequence& sol) {
        vector<string> allowed_moves = {"R", "R'", "R2", "L", "L'", "L2", "U", "U'", "U2", "D", "D'", "D2", "F", "F'", "F2", "B", "B'", "B2"};
        solve_step(s,sol,allowed_moves,0);
    }
    
    void Solver::solve_DR(const State& s, MoveSequence& sol) {
        vector<string> allowed_moves = {"R", "R'", "R2", "L", "L'", "L2", "U", "U'", "U2", "D", "D'", "D2", "F2", "B2"};
        solve_step(s,sol,allowed_moves,1);
    }

    struct PQNode{
        State state;
        int f; // Estimated cost

        bool operator< (const PQNode other) const {
            return f > other.f;
        }
    };

    void Solver::solve_HtR(const State& start, MoveSequence& sol) {
        Orientation o;
        vector<string> allowed_moves = {"R2", "L2", "U", "U'", "U2", "D", "D'", "D2", "F2", "B2"};
        
        // A-star algorithm:
        priority_queue<PQNode> open_q;
        pair<int,int> end = get_HtR_coordinate(State());

        map<State,double> g;
        set<State> closed;
        map<State, MoveSequence> parent_move;
        
        open_q.push({start, lookup_state_distance(start, 3)});
        g[start] = 0;

        State final_state;

        while(!open_q.empty()) {
            State curr_state = open_q.top().state;
            pair<int,int> curr_state_coords = get_HtR_coordinate(curr_state);
            open_q.pop();
        
            if(closed.find(curr_state)!=closed.end()) continue;


            if (curr_state_coords == end) {
                if (isSolvableWithHalfTurns(curr_state)) {
                    closed.insert(curr_state);
                    final_state = curr_state;
                    break;
                }
                closed.insert(curr_state);
                continue;
            }
            closed.insert(curr_state);
        
            for (string m : allowed_moves) {
                State s = curr_state;
                s.execute_sequence(MoveSequence(o,m));
                pair<int,int> s_coords = get_HtR_coordinate(s);
                int new_g = g[curr_state]+1;
                if (g.find(s)==g.end() or new_g < g[s]) {
                    g[s] = new_g;
                    parent_move[s] = MoveSequence(o,m);
                    int f = new_g + halfturn_reduction_lookup[s_coords.first][s_coords.second];
                    open_q.push(PQNode{s,f});
                }
            }
        }
        cerr << endl;
        if (parent_move.find(final_state)==parent_move.end() and get_HtR_coordinate(start) != end) return;

        pair<int,int> start_coords = get_HtR_coordinate(start);

        while (get_HtR_coordinate(final_state) != start_coords){
            sol = sol.append(parent_move[final_state].inverse());
            final_state.execute_sequence(parent_move[final_state].inverse());
        }
        sol = sol.inverse();

        return;
    }
    
    void Solver::solve_final_step(const State& s, MoveSequence& sol) {
        vector<string> allowed_moves = {"R2", "L2", "U2", "D2", "F2", "B2"};
        solve_step(s,sol,allowed_moves,3);
    }

    MoveSequence Solver::find_full_solution(const State& s) {
        if (not is_initialized) {
            cerr << "Error: Solver is not initialized!" << endl;
            return {};
        }
        
        State new_s = s;
        MoveSequence sol1, sol2, sol3, sol4;
        
        // Orient edges
        solve_EO(s, sol1);
        new_s.execute_sequence(sol1);
        
        // Domino reduction
        solve_DR(new_s, sol2);
        new_s.execute_sequence(sol2);

        // Half turn reduction
        solve_HtR(new_s, sol3);
        new_s.execute_sequence(sol3);

        // Solve with only half turns
        solve_final_step(new_s, sol4);
        
        MoveSequence result = sol1.append(sol2);
        result = result.append(sol3);
        result = result.append(sol4);

        return result;
    }
