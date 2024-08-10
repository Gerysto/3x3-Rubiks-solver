#include "../headers/solver.hh"

    Solver::Solver(State state) {
        this->state = state;
    }
    //MoveSequence Solver::solve() {}

    struct Node {
        int prev;       // index of the previous state
        int8_t move;    // move that was performed to get to this state
    };


    MoveSequence Solver::insert_corner(u_int8_t layer, u_int8_t piece, u_int8_t position) {

        // BFS: 
        queue<State> Q = queue<State>();
        set<State> visited = set<State>();
        vector<Node> moves;

        Q.push(this->state);
        visited.insert(this->state);
        moves.push_back({-1, 0});

        State goal = this->state;
        goal.place_corner_stiker(piece, position);

        int i = 0;
        int parent_node = 0;
        bool finished = false;
        
        while(!Q.empty() and i < 1000000 and not finished) {
            State s = Q.front();
            Q.pop();

            vector<int8_t> next_moves = {6, 5, 4, 3, 2, 1, -1, -2, -3, -4, -5, -6};

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
        cout << "Number of explored nodes: " << i << endl;

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

        State goal = this->state;
        goal.place_edge_stiker(piece, position);

        int i = 0;
        int parent_node = 0;
        bool finished = false;
        
        while(!Q.empty() and i < 1000000 and not finished) {
            State s = Q.front();
            Q.pop();

            vector<int8_t> next_moves = {9, 8, 7, 6, 5, 4, 3, 2, 1, -1, -2, -3, -4, -5, -6, -7, -8, -9};

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

        cout << "Number of explored nodes: " << i << endl;

        // Retrace the path that takes to solution:
        Node node = moves.back();
        MoveSequence result;
        while(node.prev != -1) {
            result.add_move(-node.move);
            node = moves[node.prev];
        }

        return result.inverse();
    }

    //MoveSequence Solver::move_corner_within_layer(u_int8_t layer, u_int8_t piece, u_int8_t position) {}

    //MoveSequence Solver::move_edge_within_layer(u_int8_t layer, u_int8_t piece, u_int8_t position) {}

    //vector<u_int8_t> Solver::get_layers_involving_corner(u_int8_t corner) {}

    //vector<u_int8_t> Solver::get_layers_involving_edge(u_int8_t edge) {}

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

    MoveSequence Solver::test(int i) {
        cout << "piece id: " << i << ", ";
        return insert_edge(4, i, 20);

    }