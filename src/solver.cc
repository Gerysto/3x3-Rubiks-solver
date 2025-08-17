#include "../headers/solver.hh"

    Solver::Solver(State state) {
        this->state = state;
    }
    //MoveSequence Solver::solve() {}

    struct Node {
        int prev;       // index of the previous state
        int8_t move;    // move that was performed to get to this state
    };

    MoveSequence Solver::solve() {
        
    }

    MoveSequence Solver::solve_corners() {
        vector<vector<u_int8_t>> cycles(0,vector<u_int8_t>(0));
        vector<bool> visited_corners(8, false);
        int first_corner = 0;
        bool visited_all = false;

        cout << "Corner cycles: " << endl;
        int i = 0;
        
        while(not visited_all) {
            cycles.push_back(vector<u_int8_t>(0));
            cycles[i].push_back(first_corner);
            cout << int(first_corner) << ", ";
            u_int8_t corner = state.get_corner_stiker(first_corner);
            visited_corners[corner/3] = true;

            while (corner/3 != first_corner/3) {
                cout << int(corner) << ", ";
                cycles[i].push_back(corner);
                corner = state.get_corner_stiker(corner);
                visited_corners[corner/3] = true;
            }
            cout << int(corner) << endl;
            cycles[i].push_back(corner);

            while(visited_corners[first_corner/3]) {
                ++first_corner;
                if(first_corner > 23) visited_all = true;
            }
            ++i;
        }
        
        MoveSequence result;
        u_int8_t buffer = 0;

        vector<vector<u_int8_t>> two_cycles(0, vector<u_int8_t>(0));
        vector<vector<u_int8_t>> flips(0, vector<u_int8_t>(0));

        for (int i = 0; i < cycles.size(); ++i) {
            int len = cycles[i].size();

            int end = 0;
            buffer = cycles[i][0];
            if (len > 3) {
                // SOLVE 3-cycle
                MoveSequence m;
                for(int j = 0; j < len-3; j += 2) {
                    u_int8_t p1 = cycles[i][j+1];
                    u_int8_t p2 = cycles[i][j+2];
                    cout << "cycling pieces: " << int(buffer) << " " << int(p1) << " " << int(p2) << endl;
                    m = find_corner_3_cycle(buffer, p1, p2);
                    result = result.append(m);
                    end += 2;
                }
            }

            int pieces_left = len - end;

            if(pieces_left == 3) {
                // Add 2-cycle to the list
                two_cycles.push_back({buffer, cycles[i][end+1]});
            }
            else if (pieces_left == 2) {
                // Add flipped piece to list
                flips.push_back({buffer, cycles[i][end+1]});
            }
        }

        cout << "WORKING # 1!!" << endl;
        
        // Solve pairs of 2-cycles 
        for(int j = 0; j < int(two_cycles.size()) - 1; j+=2) {
            u_int8_t p1 = two_cycles[ j ][0];
            u_int8_t p2 = two_cycles[ j ][1];
            u_int8_t p3 = two_cycles[j+1][0];
            u_int8_t p4 = two_cycles[j+1][1];
            MoveSequence m1 = find_corner_3_cycle(p1, p2, p3);
            MoveSequence m2 = find_corner_3_cycle(p3, p2, p4);
            result = result.append(m1);
            result = result.append(m2);
        }

        cout << "WORKING # 2!!" << endl;
        // Solve pairs of flipped pieces 
        for(int j = 0; j < int(flips.size())-1; j+=2) {
            u_int8_t p1 = flips[ j ][0];
            u_int8_t p2 = flips[ j ][1];
            u_int8_t p3 = flips[j+1][0];
            u_int8_t p4 = flips[j+1][1];
            MoveSequence m = find_corner_3_cycle(p1, p2, p3);
            cout << "Flipped pieces: " << int(p1) << " and " << int(p3) << endl;
            cout << "algorithm: ";
            m.print();
            result = result.append(m);
            if (state.get_corner_stiker(p3) != p3) --j;
        }

        result.print();
        return result;

    }

    MoveSequence Solver::solve_edges() {
        vector<vector<u_int8_t>> cycles(0,vector<u_int8_t>(0));
        vector<bool> visited_edges(12, false);
        int first_edge = 0;
        bool visited_all = false;

        cout << "Edge cycles: " << endl;
        int i = 0;
        
        while(not visited_all) {
            cycles.push_back(vector<u_int8_t>(0));
            cycles[i].push_back(first_edge);
            cout << int(first_edge) << ", ";
            u_int8_t edge = state.get_edge_stiker(first_edge);
            visited_edges[edge/2] = true;

            while (edge/2 != first_edge/2) {
                cout << int(edge) << ", ";
                cycles[i].push_back(edge);
                edge = state.get_edge_stiker(edge);
                visited_edges[edge/2] = true;
            }
            cout << int(edge) << endl;
            cycles[i].push_back(edge);

            while(visited_edges[first_edge/2]) {
                ++first_edge;
                if(first_edge > 23) visited_all = true;
            }
            ++i;
        }

        // Solve 3 cycles:

        MoveSequence result;
        u_int8_t buffer = 0;
        for (int i = 0; i < cycles.size(); ++i) {
            int len = cycles[i].size();
            if (len <= 3) continue;
            buffer = cycles[i][0];
            MoveSequence m;
            for(int j = 0; j < len-3; j += 2) {
                u_int8_t p1 = cycles[i][j+1];
                u_int8_t p2 = cycles[i][j+2];
                cout << "cycling pieces: " << int(buffer) << " " << int(p1) << " " << int(p2) << endl;
                m = find_edge_3_cycle(buffer, p1, p2);
                result = result.append(m);
            }
        }
        result.print();
        return result;

        // Solve flipped pieces:



    }

    vector<int8_t> merge_and_add_negatives(vector<u_int8_t> vec1, vector<u_int8_t> vec2) {
        vector<int8_t> result;
        int k1 = 0;
        int k2 = 0;
        while(k1 < vec1.size() and k2 < vec2.size()) {
            if((vec1[k1] < vec2[k2] or k2 >= vec2.size()) and k1 < vec1.size()) {
                result.push_back( vec1[k1]);
                result.push_back(-vec1[k1]);
                ++k1;
            }
            else if ((vec1[k1] > vec2[k2] or k1 >= vec1.size()) and k2 < vec2.size()) {
                result.push_back( vec2[k2]);
                result.push_back(-vec2[k2]);
                ++k2;
            }
            else {
                result.push_back( vec1[k1]);
                result.push_back(-vec1[k1]);
                ++k1;
                ++k2;
            }
        }
        return result;
    }

    MoveSequence Solver::find_2_corner_flip(u_int8_t s1_p1, u_int8_t s2_p1, u_int8_t s1_p2) {
        int8_t LOR;
        u_int8_t aux = 24;
        MoveSequence setup = corner_setup_moves(s1_p2, s1_p1, aux, LOR);
        MoveSequence seqA = insert_corner(abs(LOR), s1_p1, s2_p1);
        MoveSequence seqB;
        setup.print();
        seqB.add_move(LOR);
        MoveSequence commutator = seqA.commutate(seqB);
        MoveSequence conjugate = commutator.conjugate(setup);
        return conjugate;
    }

    MoveSequence Solver::find_2_edge_flip(u_int8_t s1_p1, u_int8_t s2_p1, u_int8_t s1_p2) {
        int8_t LOR;
        u_int8_t aux = 24;
        u_int8_t s2 = state.get_edge_stiker(s2_p1);
        MoveSequence setup = edge_setup_moves(s1_p2, s1_p1, aux, LOR);
        cout << "Function call: " << int(s1_p1) << ", " << int(state.find_edge_stiker(s2)) << endl;
        MoveSequence seqA = insert_edge(abs(LOR), s1_p1, state.find_edge_stiker(s2));
        MoveSequence seqB;
        setup.print();
        cout << "LOR: " << int(LOR) << endl;
        seqB.add_move(LOR);
        MoveSequence commutator = seqA.commutate(seqB);
        MoveSequence conjugate = commutator.conjugate(setup);
        return seqA;
        //return conjugate;
    }

    MoveSequence Solver::find_corner_3_cycle(u_int8_t stiker_1, u_int8_t stiker_2, u_int8_t stiker_3) {
        int8_t LOR;
        MoveSequence setup = corner_setup_moves(stiker_3, stiker_2, stiker_1, LOR);
        MoveSequence seqA = insert_corner(abs(LOR), stiker_1, stiker_2);
        MoveSequence seqB;
        setup.print();
        seqB.add_move(LOR);
        MoveSequence commutator = seqA.commutate(seqB);
        MoveSequence conjugate = commutator.conjugate(setup);
        return conjugate;
    }

    MoveSequence Solver::find_edge_3_cycle(u_int8_t stiker_1, u_int8_t stiker_2, u_int8_t stiker_3){
        int8_t LOR;
        MoveSequence setup = edge_setup_moves(stiker_3, stiker_2, stiker_1, LOR);
        MoveSequence seqA = insert_edge(abs(LOR), stiker_1, stiker_2);
        MoveSequence seqB;
        seqB.add_move(LOR);
        MoveSequence commutator = seqA.commutate(seqB);
        MoveSequence conjugate = commutator.conjugate(setup);
        
        return conjugate;
    }

    MoveSequence Solver::insert_corner(u_int8_t layer, u_int8_t piece, u_int8_t position) {

        // BFS: 
        queue<State> Q = queue<State>();
        set<State> visited = set<State>();
        vector<Node> moves;

        Q.push(this->state);
        visited.insert(this->state);
        moves.push_back({-1, 0});

        // Declare the two are the pieces which have to be tracked at all time
        // piece_1 is the piece that has to be inserted
        // piece_2 is the piece initially located where piece_1 belongs
        u_int8_t piece_1, piece_2;
        piece_1 = state.get_corner_stiker(piece);
        piece_2 = state.get_corner_stiker(position);

        State goal = this->state;
        goal.place_corner_stiker(piece_1, position);

        int i = 0;
        int parent_node = 0;
        bool finished = false;
        
        while(!Q.empty() and i < 1000000 and not finished) {
            State s = Q.front();
            Q.pop();

            // Examine which moves should be available:
            vector<u_int8_t> moves_1 = layers_involving_corner[s.find_corner_stiker(piece_1)/3];
            vector<u_int8_t> moves_2 = layers_involving_corner[s.find_corner_stiker(piece_2)/3];
            
            vector<int8_t> next_moves = merge_and_add_negatives(moves_1, moves_2);

            // Explore the available edges of the graph:
            int j = 0;
            while(not finished and j < next_moves.size()) {
                // Check whether it makes sense to do this move:
                bool inverse_prev = int(next_moves[j]) == -int(moves[parent_node].move);
                bool moves_ref_layer = abs(next_moves[j]) == layer;
                
                if(inverse_prev or moves_ref_layer) {
                    ++j;
                    continue;
                }

                // Perform the move:
                MoveSequence new_move;
                new_move.add_move(next_moves[j]);

                State new_state = s;
                new_state.execute_sequence(new_move);

                // Check if we've finished
                bool achieved_goal = full_layer_match(goal, new_state, layer);
                if(achieved_goal) finished = true;
                
                // Check if it's a new node 
                bool already_visited = visited.find(new_state) != visited.end();
                if (!already_visited) {
                    Q.push(new_state);
                    visited.insert(new_state);
                    moves.push_back({parent_node, next_moves[j]});
                    ++i;
                }
                ++j;
            }
            ++parent_node;
        }
        
        //cout << "Number of explored nodes: " << i << endl;

        // Retrace the path that takes to solution:
        Node node = moves.back();
        MoveSequence result;
        while(node.prev != -1) {
            result.add_move(-node.move);
            node = moves[node.prev];
        }

        return result.inverse();
    }

    MoveSequence Solver::insert_edge(u_int8_t layer, u_int8_t piece, u_int8_t position) {

        // BFS: 
        queue<State> Q = queue<State>();
        set<State> visited = set<State>();
        vector<Node> moves;

        Q.push(this->state);
        visited.insert(this->state);
        moves.push_back({-1, 0});

        // Declare the two are the pieces which have to be tracked at all time
        // piece_1 is the piece that has to be inserted
        // piece_2 is the piece initially located where piece_1 belongs
        u_int8_t piece_1, piece_2;
        piece_1 = state.get_edge_stiker(piece);
        piece_2 = state.get_edge_stiker(position);

        State goal = this->state;
        goal.place_edge_stiker(piece_1, position);

        int i = 0;
        int parent_node = 0;
        bool finished = false;
        
        while(!Q.empty() and i < 1000000 and not finished) {
            State s = Q.front();
            Q.pop();

            // Examine which moves should be available:
            vector<u_int8_t> moves_1 = layers_involving_edge[s.find_edge_stiker(piece_1)/2];
            vector<u_int8_t> moves_2 = layers_involving_edge[s.find_edge_stiker(piece_2)/2];
            
            vector<int8_t> next_moves = merge_and_add_negatives(moves_1, moves_2);

            int j = 0;
            while(not finished and j < next_moves.size()) {
                // Check whether it makes sense to do this move:
                bool inverse_prev = int(next_moves[j]) == -int(moves[parent_node].move);
                bool moves_ref_layer = abs(next_moves[j]) == layer;
                
                if(inverse_prev or moves_ref_layer) {
                    ++j;
                    continue;
                }

                MoveSequence new_move;
                new_move.add_move(next_moves[j]);

                State new_state = s;
                new_state.execute_sequence(new_move);

                bool achieved_goal = full_layer_match(goal, new_state, layer);
                bool already_visited = visited.find(new_state) != visited.end();
                
                if(achieved_goal) finished = true;
                
                if (!already_visited) {
                    Q.push(new_state);
                    visited.insert(new_state);
                    moves.push_back({parent_node,next_moves[j]});
                    ++i;
                }
                ++j;
            }
            ++parent_node;
        }

        //cout << "Number of explored nodes: " << i << endl;

        // Retrace the path that takes to solution:
        Node node = moves.back();
        MoveSequence result;
        while(node.prev != -1) {
            result.add_move(-node.move);
            node = moves[node.prev];
        }

        return result.inverse();
    }

    // piece_0 becomes 1 move away from piece_1 (which is called LOR_move) and piece_2 isn't involved in that move.
    MoveSequence Solver::corner_setup_moves(u_int8_t& piece_0_pos, u_int8_t& piece_1_pos, u_int8_t& piece_2_pos, int8_t& LOR_move) {

        u_int8_t piece_0 = state.get_corner_stiker(piece_0_pos);
        u_int8_t piece_1 = state.get_corner_stiker(piece_1_pos);
        u_int8_t piece_2;
        if(piece_2_pos != 24) {
            piece_2 = state.get_corner_stiker(piece_2_pos);
        }

        // BFS: 
        queue<State> Q = queue<State>();
        set<State> visited = set<State>();
        vector<Node> moves;

        Q.push(this->state);
        visited.insert(this->state);
        moves.push_back({-1, 0});

        int i = 0;
        int parent_node = 0;
        bool finished = false;
        
        bool one_move_away = is_corner_one_move_away(this->state, piece_0, piece_1, LOR_move);
        if(one_move_away) {
                bool move_contains_third_corner = false;

                vector<u_int8_t> moves_containing_third =  vector<u_int8_t>();

                if(piece_2_pos != 24) {
                     moves_containing_third = layers_involving_corner[piece_2_pos/3];
                }

                for(int i = 0; i < moves_containing_third.size(); ++i) {
                    //cout << int(moves_containing_third[i]) << ", ";
                    if (moves_containing_third[i] == abs(LOR_move)) {
                        move_contains_third_corner = true;
                        break;
                    }
                }
                
                finished = !move_contains_third_corner;
        }

        while(!Q.empty() and i < 1000000 and not finished) {
            State s = Q.front();
            Q.pop();
            
            vector<int8_t> next_moves = {6, 5, 4, 3, 2, 1, -1, -2, -3, -4, -5, -6};

            // Explore the available edges of the graph:
            int j = 0;
            while(not finished and j < next_moves.size()) {
                // Check whether it makes sense to do this move:
                bool inverse_prev = int(next_moves[j]) == -int(moves[parent_node].move);
                
                if(inverse_prev) {
                    ++j;
                    continue;
                }

                // Perform the move:
                MoveSequence new_move;
                new_move.add_move(next_moves[j]);

                State new_state = s;
                new_state.execute_sequence(new_move);

                // Check if we've finished
                bool one_move_away = is_corner_one_move_away(new_state, piece_0, piece_1, LOR_move);
                
                if(one_move_away) {
                    //cout << endl;
                    bool move_contains_third_corner = false;
                    
                    if(piece_2_pos != 24) {

                        vector<u_int8_t> moves_containing_third = vector<u_int8_t>();
                        moves_containing_third = layers_involving_corner[new_state.find_corner_stiker(piece_2)/3];

                        for(int i = 0; i < moves_containing_third.size(); ++i) {
                            if (moves_containing_third[i] == abs(LOR_move)) move_contains_third_corner = true;
                        }
                    }

                    finished = !move_contains_third_corner;
                }

                if(finished) {
                    piece_0_pos = new_state.find_corner_stiker(piece_0);
                    piece_1_pos = new_state.find_corner_stiker(piece_1);
                    if(piece_2_pos != 24) {
                        piece_2_pos = new_state.find_corner_stiker(piece_2);
                    }
                }

                // Check if it's a new node.
                bool already_visited = visited.find(new_state) != visited.end();
                if (!already_visited) {
                    Q.push(new_state);
                    visited.insert(new_state);
                    moves.push_back({parent_node, next_moves[j]});
                    ++i;
                }
                ++j;
            }
            ++parent_node;
        }
        
        //cout << "Number of explored nodes: " << i << endl;

        // Retrace the path that takes to solution:
        Node node = moves.back();
        MoveSequence result;
        while(node.prev != -1) {
            result.add_move(-node.move);
            node = moves[node.prev];
        }
        
        return result.inverse();
    }

    // piece_0 becomes 1 move away from piece_1 (which is called LOR_move) and piece_2 isn't involved in that move.
    MoveSequence Solver::edge_setup_moves(u_int8_t& piece_0_pos, u_int8_t& piece_1_pos, u_int8_t& piece_2_pos, int8_t& LOR_move) {

        u_int8_t piece_0 = state.get_edge_stiker(piece_0_pos);
        u_int8_t piece_1 = state.get_edge_stiker(piece_1_pos);
        u_int8_t piece_2;
        if(piece_2_pos != 24) {
            piece_2 = state.get_edge_stiker(piece_2_pos);
        } 

        // BFS: 
        queue<State> Q = queue<State>();
        set<State> visited = set<State>();
        vector<Node> moves;

        Q.push(this->state);
        visited.insert(this->state);
        moves.push_back({-1, 0});

        int i = 0;
        int parent_node = 0;
        bool finished = false;
        
        bool one_move_away = is_edge_one_move_away(this->state, piece_0, piece_1, LOR_move);
        if(one_move_away) {
                bool move_contains_third_edge = true;
                //cout << "PIECE 2: " << int(piece_2) << endl;
                vector<u_int8_t> moves_containing_third;
                //cout << "Moves involving third: ";
                if(piece_2_pos != 24) {
                     layers_involving_edge[piece_2_pos/2];
                }
                for(int i = 0; i < moves_containing_third.size(); ++i) {
                    //cout << int(moves_containing_third[i]) << ", ";
                    if (moves_containing_third[i] == abs(LOR_move)) {
                        move_contains_third_edge = false;
                        break;
                    }
                }
                
                finished = move_contains_third_edge;
        }

        while(!Q.empty() and i < 1000000 and not finished) {
            State s = Q.front();
            Q.pop();
            
            vector<int8_t> next_moves = {9, 8, 7, 6, 5, 4, 3, 2, 1, -1, -2, -3, -4, -5, -6, -7, -8, -9};

            // Explore the available edges of the graph:
            int j = 0;
            while(not finished and j < next_moves.size()) {
                // Check whether it makes sense to do this move:
                bool inverse_prev = int(next_moves[j]) == -int(moves[parent_node].move);
                
                if(inverse_prev) {
                    ++j;
                    continue;
                }

                // Perform the move:
                MoveSequence new_move;
                new_move.add_move(next_moves[j]);

                State new_state = s;
                new_state.execute_sequence(new_move);

                // Check if we've finished
                bool one_move_away = is_edge_one_move_away(new_state, piece_0, piece_1, LOR_move);
                
                if(one_move_away) {
                    //cout << endl;
                    bool move_contains_third_edge = false;
                    if(piece_2_pos != 24) {
                        vector<u_int8_t> moves_containing_third = layers_involving_edge[new_state.find_edge_stiker(piece_2)/2];

                        for(int i = 0; i < moves_containing_third.size(); ++i) {
                            if (moves_containing_third[i] == abs(LOR_move)) move_contains_third_edge = true;
                        }
                    }
                    finished = !move_contains_third_edge;
                }

                if(finished) {
                    piece_0_pos = new_state.find_edge_stiker(piece_0);
                    piece_1_pos = new_state.find_edge_stiker(piece_1);

                    if(piece_2_pos != 24) {
                        piece_2_pos = new_state.find_edge_stiker(piece_2);
                    }
                }

                // Check if it's a new node 
                bool already_visited = visited.find(new_state) != visited.end();
                if (!already_visited) {
                    Q.push(new_state);
                    visited.insert(new_state);
                    moves.push_back({parent_node, next_moves[j]});
                    ++i;
                }
                ++j;
            }
            ++parent_node;
        }
        
        //cout << "Number of explored nodes: " << i << endl;

        // Retrace the path that takes to solution:
        Node node = moves.back();
        MoveSequence result;
        while(node.prev != -1) {
            result.add_move(-node.move);
            node = moves[node.prev];
        }
        
        return result.inverse();
    }

    bool Solver::is_corner_one_move_away(const State& s, u_int8_t piece, u_int8_t target, int8_t& move) {
        
        u_int8_t target_pos = s.find_corner_stiker(target);
        vector<int8_t> possible_moves = {6, 5, 4, 3, 2, 1, -1, -2, -3, -4, -5, -6};
        
        for(int i = 0; i < possible_moves.size(); ++i) {
            State new_s = s;
            MoveSequence m;
            m.add_move(possible_moves[i]);
            new_s.execute_sequence(m);
            if (new_s.get_corner_stiker(target_pos) == piece) {
                move = possible_moves[i];
                return true;
            }
        }
        
        return false;
    }

    bool Solver::is_edge_one_move_away(const State& s, u_int8_t piece, u_int8_t target, int8_t& move) {
        // CURRENT PROBLEM: the program thinks of slice moves as 'turning 2 sides at once' but here, it should be more like 'cycling 4 edges'.
        u_int8_t target_pos = s.find_edge_stiker(target);
        //vector<int8_t> possible_moves = {9, 8, 7, 6, 5, 4, 3, 2, 1, -1, -2, -3, -4, -5, -6, -7, -8, -9}; DOESN't WORK PROPERLY
        vector<int8_t> possible_moves = {6, 5, 4, 3, 2, 1, -1, -2, -3, -4, -5, -6};

        for(int i = 0; i < possible_moves.size(); ++i) {
            State new_s = s;
            MoveSequence m;
            new_s.cycle_edges(get_edges_in_layer(abs(possible_moves[i])), possible_moves[i] > 0);

            if (new_s.get_edge_stiker(target_pos) == piece) {
                move = possible_moves[i];
                return true;
            }
        }
        
        return false;
    }

    bool Solver::full_layer_match(State state1, State state2, u_int8_t layer) {
        vector<u_int8_t> corners = get_corners_in_layer(layer);
        vector<u_int8_t> edges = get_edges_in_layer(layer);

        bool same_corners = corner_subset_match(state1, state2, corners);
        bool same_edges   = edge_subset_match(state1, state2, edges);

        return same_corners and same_edges;
    }

    bool Solver::corner_subset_match(State state1, State state2, const vector<u_int8_t>& subset) {
        for(int i = 0; i < subset.size(); ++i) {
            int position = subset[i]/3;
            if(state1.corners[position] != state2.corners[position]) return false;
        }
        return true;
    }

    bool Solver::edge_subset_match(State state1, State state2, const vector<u_int8_t>& subset) {
        for(int i = 0; i < subset.size(); ++i) {
            int position = subset[i]/2;
            if(state1.edges[position] != state2.edges[position]) return false;
        }
        return true;
    }

    vector<u_int8_t> Solver::get_corners_in_layer(u_int8_t layer) {
        switch (layer) {
            case 1:
                return W_face_corner_cycle;
                break;
            case 2:
                return R_face_corner_cycle;
                break;
            case 3:
                return G_face_corner_cycle;
                break;
            case 4:
                return Y_face_corner_cycle;
                break;
            case 5:
                return O_face_corner_cycle;
                break;
            case 6:
                return B_face_corner_cycle;
                break;
            default:
                return vector<u_int8_t>();
                break;         
        };
    }

    vector<u_int8_t> Solver::get_edges_in_layer(u_int8_t layer) {
        switch (layer) {
            case 1:
                return W_face_edge_cycle;
                break;
            case 2:
                return R_face_edge_cycle;
                break;
            case 3:
                return G_face_edge_cycle;
                break;
            case 4:
                return Y_face_edge_cycle;
                break;
            case 5:
                return O_face_edge_cycle;
                break;
            case 6:
                return B_face_edge_cycle;
                break;
            case 7:
                return WY_slice_edge_cycle;
                break;
            case 8:
                return RO_slice_edge_cycle;
                break;
            case 9:
                return GB_slice_edge_cycle;
                break;
            case 10:
                return WY_slice_edge_cycle;
                break;
            case 11:
                return RO_slice_edge_cycle;
                break;
            case 12:
                return GB_slice_edge_cycle;
                break;
            default:
                return vector<u_int8_t>();
                break;         
        };
    }

    MoveSequence Solver::test(int i, int j, int k) {
        //return solve_corners().append(solve_edges());
        return find_corner_3_cycle(i, j, k);
    }