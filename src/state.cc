#include "../headers/state.hh"

    State::State(){
        this->corners = solved_corners;
        this->edges = solved_edges;
    }

    u_int8_t State::get_corner_stiker(u_int8_t position) const {
        u_int8_t top_stiker = corners[position/3];
        return top_stiker - top_stiker%3 + (top_stiker + position)%3;
    }

    u_int8_t State::get_edge_stiker(u_int8_t position) const {
        u_int8_t top_stiker = edges[position/2];
        return top_stiker - top_stiker%2 + (top_stiker + position)%2;
    }

    void State::place_corner_stiker(u_int8_t stiker, u_int8_t position) {
        u_int8_t remainder_mod_3 = ((stiker - position)%3 + 3)%3;
        corners[position/3] = stiker - stiker%3 + remainder_mod_3;
    }

    void State::place_edge_stiker(u_int8_t stiker, u_int8_t position) {
        u_int8_t remainder_mod_2 = ((stiker - position)%2 + 2)%2;
        edges[position/2] = stiker - stiker%2 + remainder_mod_2;
    }

    void State::cycle_corners(const vector<u_int8_t>& stikers, bool clockwhise){
        int len = stikers.size();
        if(clockwhise) {
            u_int8_t aux = get_corner_stiker(stikers[len-1]);
            for(int i = len-1; i > 0; --i) {
                u_int8_t s = get_corner_stiker(stikers[i-1]);
                place_corner_stiker(s, stikers[i]);
            }
            place_corner_stiker(aux, stikers[0]);
        } else {

            u_int8_t aux = get_corner_stiker(stikers[0]);
            for(int i = 0; i < len-1; ++i) {
                u_int8_t s = get_corner_stiker(stikers[i+1]);
                place_corner_stiker(s, stikers[i]);
            }
            place_corner_stiker(aux, stikers[len-1]);
        }
    }

    void State::cycle_edges(const vector<u_int8_t>& stikers, bool clockwhise){
        int len = stikers.size();
        if(clockwhise) {
            u_int8_t aux = get_edge_stiker(stikers[len-1]);
            for(int i = len-1; i > 0; --i) {
                u_int8_t s = get_edge_stiker(stikers[i-1]);
                place_edge_stiker(s, stikers[i]);
            }
            place_edge_stiker(aux, stikers[0]);
        } else {

            u_int8_t aux = get_edge_stiker(stikers[0]);
            for(int i = 0; i < len-1; ++i) {
                u_int8_t s = get_edge_stiker(stikers[i+1]);
                place_edge_stiker(s, stikers[i]);
            }
            place_edge_stiker(aux, stikers[len-1]);
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

    void State::execute_sequence(MoveSequence seq) {

    for(int i = 0; i < seq.size(); ++i) {
        int8_t move = seq.get_move(i);
        bool clockwhise = move > 0;

        if(abs(move) <= 6) {
            turn_face(abs(move)-1, clockwhise);
        }
        else {
            switch(abs(move)) {
                case 7:
                    turn_face(3, !clockwhise);
                    turn_face(0, clockwhise);
                    break;
                case 8:
                    turn_face(4, !clockwhise);
                    turn_face(1, clockwhise);
                    break;
                case 9:
                    turn_face(5, clockwhise);
                    turn_face(2, !clockwhise);
                    break;
                case 10:
                    turn_face(3, clockwhise);
                    turn_face(0, !clockwhise);
                    break;
                case 11:
                    turn_face(4, clockwhise);
                    turn_face(1, !clockwhise);
                    break;
                case 12:
                    turn_face(5, !clockwhise);
                    turn_face(2, clockwhise);
                    break;
                default:
                    cerr << "Invalid move in 'execute sequence' method.";
                    break;
            };
        }
    }
}

    bool State::is_solved() const {
        return corners == solved_corners and edges == solved_edges;
    }

    bool State::is_solvable() const{
        int sum_corners = 0;
        for(int i = 0; i < corners.size(); ++i) {
            sum_corners += corners[i];
        }
        if(sum_corners%3 != 0) return false; // Wrong corner orientation.
        
        int sum_edges = 0;
        for(int i = 0; i < corners.size(); ++i) {
            sum_edges += corners[i];
        }
        if(sum_edges%2 != 0) return false; // Wrong edge orientation.

        int even_cycles_count;

        vector<bool> visited_corners(8, false);
        int first_corner = 0;
        bool visited_all = false;

        while(not visited_all) {

            int cycle_size = 0;
            u_int8_t corner = corners[first_corner]/3;
            visited_corners[corner] = true;

            while (corner != first_corner) {
                corner = corners[corner]/3;
                visited_corners[corner] = true;
                ++cycle_size;
            }

            if(cycle_size%2 == 0) ++even_cycles_count;

            while(visited_corners[first_corner]) {
                ++first_corner;
                if(first_corner >= 8) visited_all = true;
            }
        }

        vector<bool> visited_edges(12, false);
        int first_edge = 0;
        visited_all = false;

        while(not visited_all) {
            int cycle_size = 0;
            u_int8_t edge = edges[first_edge]/2;
            visited_edges[edge] = true;

            while (edge != first_edge) {
                edge = edges[edge]/2;
                visited_edges[edge] = true;
                ++cycle_size;
            }

            if(cycle_size%2 == 0) ++even_cycles_count;

            while(visited_edges[first_edge]) {
                ++first_edge;
                if(first_edge >= 8) visited_all = true;
            }
        }
        return even_cycles_count%2 == 0;
    }

    void State::log_state() const {
        cout << "Corners: ";
        for(int i = 0; i < corners.size(); ++i) {
            cout << int(corners[i]) << " ";
        }
        cout << endl << "Edges: ";
        for(int i = 0; i < edges.size(); ++i) {
            cout << int(edges[i]) << " ";
        }
        cout << endl;
    }

    void State::display() const {
        int num = 0;
        int count = 0;
        int color;
        bool paint = false;

        for(int i = 0; i < stiker_positions.length(); ++i) {
            char c = stiker_positions[i];
            if (c >= '0' and c <= '9') {
                num = 10*num + c - '0';
                ++count;
                paint = true;
            }
            else {
                if(num >= 90) {
                    color = num - 90;
                }
                else if (num >= 50) {
                    u_int8_t stiker = get_edge_stiker(num-50);
                    color = edge_stiker_colors[stiker];
                }
                else {
                    u_int8_t stiker = get_corner_stiker(num);
                    color = corner_stiker_colors[stiker];
                }
                if(count == 18) count = 0;
                num = 0;
                if (paint) cout << id_to_color[color] << id_to_color[color];
                cout << c;
                paint = false;
            }
        }
        cout << endl;
    }