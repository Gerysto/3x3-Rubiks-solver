#include "../headers/move_sequence.hh"
#include <math.h>
#include <algorithm>

MoveSequence::MoveSequence() {
    move_sequence = vector<int8_t>(0);
}

MoveSequence::MoveSequence(Orientation& orientation, const string& move_sequence) {
    string my_move = "";
    for(int i = 0; i < move_sequence.length(); ++i) {
        char c = move_sequence[i];
        if(c != ' ') my_move.push_back(c);

        else {
            if(my_move != "") *this = this->append(translate_single_move(orientation, my_move));
            my_move = "";
        }
    }
    *this = this->append(translate_single_move(orientation, my_move));
}


void MoveSequence::generate_random(int length) {
    MoveSequence m = MoveSequence();
    while(m.size() < length) {
        int move = (rand()%6 + 1)*(2*(rand()%2) - 1);
        m.add_move(move);
        m = MoveSequence::compress(m);
    }
    *this = m;
}


MoveSequence MoveSequence::translate_single_move(Orientation& orientation, const string& move) const {
    MoveSequence result;

    if (move.length() == 0) return MoveSequence();

    int sign = 1;
    bool clockwhise = true;
    bool double_move = false;

    if(move.length() == 2 and move[1] == '\'') {
        clockwhise = false;
        sign = -1;
    }
    if(move.length() == 2 and move[1] == '2') double_move = true;

    // REGULAR MOVES:
    
    if      (move[0] == 'U') result.add_move((orientation.get_face(0)+1)*sign);
    else if (move[0] == 'R') result.add_move((orientation.get_face(1)+1)*sign);
    else if (move[0] == 'F') result.add_move((orientation.get_face(2)+1)*sign);
    else if (move[0] == 'D') result.add_move((orientation.get_face(3)+1)*sign);
    else if (move[0] == 'L') result.add_move((orientation.get_face(4)+1)*sign);
    else if (move[0] == 'B') result.add_move((orientation.get_face(5)+1)*sign);

    // CUBE ROTATIONS:
    
    else if (move[0] == 'X') orientation.X_rotation(clockwhise, double_move);
    else if (move[0] == 'Y') orientation.Y_rotation(clockwhise, double_move);
    else if (move[0] == 'Z') orientation.Z_rotation(clockwhise, double_move);
    
    // MIDDLE LAYER MOVES:
    
    else if(move[0] == 'M') { // in the L direction
        result.add_move((orientation.get_face(4)+7)*sign);
        orientation.X_rotation(!clockwhise, double_move);
    }
    else if(move[0] == 'E') { // in the D direction
        result.add_move((orientation.get_face(3)+7)*sign);
        orientation.Y_rotation(!clockwhise, double_move);
    }
    else if(move[0] == 'S') { // in the F direction
        result.add_move((orientation.get_face(2)+7)*sign);
        orientation.Z_rotation(clockwhise, double_move);
    }

    // LOWER CASE MOVES:
    
    else if (move[0] == 'u') { // u = D + Y
        result.add_move((orientation.get_face(3)+1)*sign);
        orientation.Y_rotation(clockwhise, double_move);

    }
    else if (move[0] == 'r') { // r = L + X
    result.add_move((orientation.get_face(4)+1)*sign);
        orientation.X_rotation(clockwhise, double_move);
    }
    else if (move[0] == 'f') { // f = B + Z
        result.add_move((orientation.get_face(5)+1)*sign);
        orientation.Z_rotation(clockwhise, double_move);
    }
    else if (move[0] == 'd') { // d = U + Y'
        result.add_move((orientation.get_face(0)+1)*sign);
        orientation.Y_rotation(!clockwhise, double_move);
    }
    else if (move[0] == 'l') { // l = R + X'
        result.add_move((orientation.get_face(1)+1)*sign);
        orientation.X_rotation(!clockwhise, double_move);
    }
    else if (move[0] == 'b') { // b = F + Z'
        result.add_move((orientation.get_face(2)+1)*sign);
        orientation.Z_rotation(!clockwhise, double_move);
    }

    if(double_move) return result.append(result);
    else return result;
}

bool MoveSequence::is_move_valid(const string& move) {
    if(move.length() == 2 and move[1] == '\'');
    else if(move.length() == 2 and move[1] == '2');
    else if (move.length() >= 2) return false;

    vector<char> ok_moves = {'U','R','F','D','L','B','X','Y','Z','M','E','S','u','r','f','d','l','b'};

    return find(ok_moves.begin(), ok_moves.end(), move[0]) != ok_moves.end();
}

bool MoveSequence::is_sequence_valid(const string& seq) {
    string my_move = "";
    for(int i = 0; i < seq.length(); ++i) {
        char c = seq[i];
        if(c != ' ') my_move.push_back(c);
        else {
            if(my_move != "" && !is_move_valid(my_move)) return false;
            my_move = "";
        }
    }
    return my_move == "" || is_move_valid(my_move);
}

MoveSequence MoveSequence::inverse() const {
    MoveSequence seq;
    int len = move_sequence.size();
    for(int i = 0; i < len; ++i) {
        seq.move_sequence.push_back(-move_sequence[len-i-1]);
    }
    return seq;
}


string MoveSequence::to_notation(Orientation orientation) const {
    int len = move_sequence.size();
    string result = "";
    for(int i = 0; i < len; ++i) {
        char c;
        int8_t face_move = move_sequence[i];
        bool clockwhise = face_move > 0;
        if(abs(face_move) <= 6) {
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
                orientation.Y_rotation(clockwhise, false);
                clockwhise = !clockwhise;
                break;
            case 1:
                c = 'M';
                orientation.X_rotation(clockwhise, false);
                clockwhise = !clockwhise; 
                break;
            case 2:
                c = 'S';
                orientation.Z_rotation(clockwhise, false);
                break;
            case 3:
                c = 'E';
                orientation.Y_rotation(!clockwhise, false);
                break;
            case 4:
                c = 'M';
                orientation.X_rotation(!clockwhise, false);
                break;
            case 5:
                c = 'S';
                orientation.Z_rotation(!clockwhise, false);
                clockwhise = !clockwhise;
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


int8_t MoveSequence::get_move(int position) const {
    return move_sequence[position];
}


int MoveSequence::size() const {
    return move_sequence.size();
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

MoveSequence MoveSequence::compress(const MoveSequence &m) {
    MoveSequence res;
    if(m.size() == 0) return m;
    int last_move = abs(m.get_move(0));
    int count = 1;
    for (int i = 1; i < m.move_sequence.size(); ++i) {
        int new_move = m.move_sequence[i];
        if (last_move == new_move || last_move == -new_move) {
            // Count is increased by the sign of the new move.
            count += new_move/abs(new_move);
        }
        else {
            switch((count%4+4)%4){
                case 0: 
                    break;
                case 1:    
                    res.add_move(last_move);
                    break;
                case 2:
                    res.add_move(last_move);
                    res.add_move(last_move);
                    break;
                case 3:
                    res.add_move(-last_move);
                    break;
            }

            last_move = new_move;
            count = 1;
        }
    }
    switch((count%4+4)%4){
        case 0: 
            break;
        case 1:    
            res.add_move(last_move);
            break;
        case 2:
            res.add_move(last_move);
            res.add_move(last_move);
            break;
        case 3:
            res.add_move(-last_move);
            break;
    }
    return res;
}

void MoveSequence::print() const {
    cout << "sequence: [";
    int len = move_sequence.size();
    for (int i = 0; i < len; ++i) {
        cout << int(move_sequence[i]);
        if(i != len-1) cout << ", "; 
    }
    cout << "]" << endl;
}