#include "headers/cube.hh"

Cube::Cube(){
    this->state = State();
    this->orientation = default_orientation;
}



Cube::Cube(State state, vector<u_int8_t> orientation){
    this->state = state;
    this->orientation = orientation;
}



void Cube::cycle_faces(vector<u_int8_t> faces, bool clockwhise, bool double_move) {
    u_int8_t aux;
    int len = faces.size();

    if(clockwhise) {
        aux = orientation[faces[len-1]];

        for(int i = len-1; i > 0; --i) {
            orientation[faces[i]] = orientation[faces[i-1]];
        }

        orientation[faces[0]] = aux;

    } else {
        aux = orientation[faces[0]];

        for(int i = 0; i < len-1; ++i) {
            orientation[faces[i]] = orientation[faces[i+1]];
        }

        orientation[faces[len-1]] = aux;
    }
    
    if(double_move) cycle_faces(faces, clockwhise, false);
}



void Cube::turn_face(u_int8_t face_color, bool clockwhise){
    state.turn_face(face_color, clockwhise);
}



void Cube::turn_side(u_int8_t side, bool clockwhise, bool double_move){
    state.turn_face(orientation[side], clockwhise);
}



void Cube::move(string move){
    if (move.length() == 0) return;

    bool clockwhise = true;
    bool double_move = false;

    if(move.length() == 2 and move[1] == '\'') clockwhise = false;
    if(move.length() == 2 and move[1] == '2') double_move = true;

    u_int8_t side = 6;

    // REGULAR MOVES:
    if      (move[0] == 'U') turn_side(0, clockwhise, double_move);
    else if (move[0] == 'R') turn_side(1, clockwhise, double_move);
    else if (move[0] == 'F') turn_side(2, clockwhise, double_move);
    else if (move[0] == 'D') turn_side(3, clockwhise, double_move);
    else if (move[0] == 'L') turn_side(4, clockwhise, double_move);
    else if (move[0] == 'B') turn_side(5, clockwhise, double_move);
    // CUBE ROTATIONS:
    else if (move[0] == 'X') cycle_faces(X_rotation_centre_cycle, clockwhise, double_move);
    else if (move[0] == 'Y') cycle_faces(Y_rotation_centre_cycle, clockwhise, double_move);
    else if (move[0] == 'Z') cycle_faces(Z_rotation_centre_cycle, clockwhise, double_move);
    // MIDDLE LAYER MOVES:
    else if(move[0] == 'M') { 
        turn_side(1, clockwhise, double_move);
        turn_side(4, !clockwhise, double_move);
        cycle_faces(X_rotation_centre_cycle, !clockwhise, double_move);
    }
    else if(move[0] == 'E') {
        turn_side(0, clockwhise, double_move);
        turn_side(3, !clockwhise, double_move);
        cycle_faces(Y_rotation_centre_cycle, !clockwhise, double_move);
    }
    else if(move[0] == 'S') {
        turn_side(5, clockwhise, double_move);
        turn_side(2, !clockwhise, double_move);
        cycle_faces(Z_rotation_centre_cycle, clockwhise, double_move);
    }
    // LOWER CASE MOVES:
    else if (move[0] == 'u') { // u = D + Y
        turn_side(3, clockwhise, double_move);
        cycle_faces(Y_rotation_centre_cycle, clockwhise, double_move);

    }
    else if (move[0] == 'r') { // r = L + X
        turn_side(4, clockwhise, double_move);
        cycle_faces(X_rotation_centre_cycle, clockwhise, double_move);
    }
    else if (move[0] == 'f') { // f = B + Z
        turn_side(5, clockwhise, double_move);
        cycle_faces(Z_rotation_centre_cycle, clockwhise, double_move);
    }
    else if (move[0] == 'd') { // d = U + Y'
        turn_side(0, clockwhise, double_move);
        cycle_faces(Y_rotation_centre_cycle, !clockwhise, double_move);
    }
    else if (move[0] == 'l') { // l = R + X'
        turn_side(1, clockwhise, double_move);
        cycle_faces(X_rotation_centre_cycle, !clockwhise, double_move);
    }
    else if (move[0] == 'b') { // b = F + Z'
        turn_side(2, clockwhise, double_move);
        cycle_faces(Z_rotation_centre_cycle, !clockwhise, double_move);
    }
}


void Cube::move_sequence(string sequence){
    
}