#include "../headers/move_sequence.hh"


MoveSequence::MoveSequence() {
    move_sequence = vector<int8_t>(0);
}


MoveSequence::MoveSequence(Orientation orientation, const string& move_sequence) {
    string my_move = "";
    for(int i = 0; i < move_sequence.length(); ++i) {
        char c = move_sequence[i];
        if(c != ' ') my_move.push_back(c);

        else {
            cout << my_move << endl;
            if(my_move != "") this->append(translate_single_move(orientation, my_move));
            my_move = "";
        }
    }
    this->append(translate_single_move(orientation, my_move));
}


MoveSequence MoveSequence::translate_single_move(Orientation& orientation, const string& move) const {
    MoveSequence result;

    if (move.length() == 0) return;

    int sign = 1;
    bool clockwhise = true; 
    bool double_move = false;

    if(move.length() == 2 and move[1] == '\'') {
        clockwhise = false;
        sign = -1;
    }
    if(move.length() == 2 and move[1] == '2') double_move = true;

    // REGULAR MOVES:
    
    if      (move[0] == 'U') result.add_move(1*sign);
    else if (move[0] == 'R') result.add_move(2*sign);
    else if (move[0] == 'F') result.add_move(3*sign);
    else if (move[0] == 'D') result.add_move(4*sign);
    else if (move[0] == 'L') result.add_move(5*sign);
    else if (move[0] == 'B') result.add_move(6*sign);

    // CUBE ROTATIONS:
    
    else if (move[0] == 'X') orientation.X_rotation(clockwhise);
    else if (move[0] == 'Y') orientation.Y_rotation(clockwhise);
    else if (move[0] == 'Z') orientation.Z_rotation(clockwhise);
    
    // MIDDLE LAYER MOVES:
    
    else if(move[0] == 'M') { 
        result.add_move(8*sign);
        orientation.X_rotation(!clockwhise);
    }
    else if(move[0] == 'E') {
        result.add_move(7*sign);
        orientation.Y_rotation(!clockwhise);
    }
    else if(move[0] == 'S') {
        result.add_move(9*sign);
        orientation.Z_rotation(clockwhise);
    }

    // LOWER CASE MOVES:
    
    else if (move[0] == 'u') { // u = D + Y
        result.add_move(4*sign);
        orientation.Y_rotation(clockwhise);

    }
    else if (move[0] == 'r') { // r = L + X
        result.add_move(5*sign);
        orientation.X_rotation(clockwhise);
    }
    else if (move[0] == 'f') { // f = B + Z
        result.add_move(6*sign);
        orientation.Z_rotation(clockwhise);
    }
    else if (move[0] == 'd') { // d = U + Y'
        result.add_move(1*sign);
        orientation.Y_rotation(!clockwhise);
    }
    else if (move[0] == 'l') { // l = R + X'
        result.add_move(2*sign);
        orientation.X_rotation(!clockwhise);
    }
    else if (move[0] == 'b') { // b = F + Z'
        result.add_move(3*sign);
        orientation.Z_rotation(!clockwhise);
    }

    if(double_move) return result.append(result);
    else return result;
}


MoveSequence MoveSequence::inverse() const {
    MoveSequence seq;
    int len = move_sequence.size();
    for(int i = 0; i < len; ++i) {
        seq.move_sequence.push_back(-move_sequence[len-i-1]);
    }
}


string MoveSequence::to_notation(Orientation orientation) {
    int len = move_sequence.size();
    string result = "";
    for(int i = 0; i < len; ++i) {
        char c;
        int8_t face_move = move_sequence[i];
        bool clockwhise = face_move > 0;
        if(abs(face_move) < 6) {
            switch (orientation.get_side(abs(face_move) - 1)) {
            case 0:
                c = 'U';
                break;
            case 1:
                c = 'R';
                break;
            case 2:
                c = 'F';
                break;
            case 3:
                c = 'D';
                break;
            case 4:
                c = 'L';
                break;
            case 5:
                c = 'B';
                break;
            default:
                cerr << "invalid id in 'to_notation' function" << endl;
                break;
            };
        } else {
            switch (orientation.get_side(abs(face_move) - 7)) {
            case 0:
                c = 'E';
                orientation.Y_rotation(!clockwhise);
                break;
            case 1:
                orientation.X_rotation(!clockwhise);
                c = 'M';
                break;
            case 2:
                orientation.Z_rotation(clockwhise);
                c = 'S';
                break;
            default:
                cerr << "Invalid id in 'to_notation' function" << endl;
                break;
            };
        }
        result.push_back(c);
        if(!clockwhise) result.push_back('\'');
        if(i != len-1) result.push_back(' ');
    }
    return result;
}


void MoveSequence::add_move(int8_t move) {
    move_sequence.push_back(move);
}


MoveSequence MoveSequence::append(const MoveSequence& seq) const {
    MoveSequence result = *this;
    int len = seq.move_sequence.size();
    for(int i = 0; i < len; ++i) {
        result.move_sequence.push_back(seq.move_sequence[i]);
    }
    return result;
}


MoveSequence MoveSequence::commutate(const MoveSequence& seq) const {
    MoveSequence inv = this->inverse();
    return this->append(seq).append(inv).append(seq.inverse());
}


MoveSequence MoveSequence::conjugate(const MoveSequence& setup_moves) const {
    MoveSequence inv = setup_moves.inverse();
    return setup_moves.append(*this).append(inv);
}