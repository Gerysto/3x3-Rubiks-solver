#include "../headers/orientation.hh"

Orientation::Orientation() {
    face_to_side = default_orientation;
    side_to_face = default_orientation;
}

void Orientation::cycle_elements(vector<u_int8_t>& vec, const vector<u_int8_t>& cycle, bool clockwhise) {
    u_int8_t aux;
    int len = cycle.size();
    if(clockwhise) {
        int first_face = vec[cycle[len-1]];

        for(int i = len-1; i > 0; --i) {
            vec[cycle[i]] = vec[cycle[i-1]];
        }
        vec[cycle[0]] = first_face;

    } else {
        int first_face = vec[cycle[0]];

        for(int i = 0; i < len-1; ++i) {
            vec[cycle[i]] = vec[cycle[i+1]];
        }
        vec[cycle[len-1]] = first_face;
    }
}

void Orientation::cycle_sides(const vector<u_int8_t>& cycle, bool clockwhise) {
    cycle_elements(side_to_face, cycle, clockwhise);
    for(int i = 0; i < 6; ++i) {
        int x = side_to_face[i];
        face_to_side[x] = i;
    }
}

void Orientation::X_rotation(bool clockwhise, bool double_move) {
    cycle_sides(X_rotation_centre_cycle, clockwhise);
    if(double_move) cycle_sides(X_rotation_centre_cycle, clockwhise);
}

void Orientation::Y_rotation(bool clockwhise, bool double_move) {
    cycle_sides(Y_rotation_centre_cycle, clockwhise);
    if(double_move) cycle_sides(Y_rotation_centre_cycle, clockwhise);
}
    
void Orientation::Z_rotation(bool clockwhise, bool double_move) {
    cycle_sides(Z_rotation_centre_cycle, clockwhise);
    if(double_move) cycle_sides(Z_rotation_centre_cycle, clockwhise);
}

u_int8_t Orientation::get_face(u_int8_t side) const {
    return side_to_face[side];
}

u_int8_t Orientation::get_side(u_int8_t face) const {
    return face_to_side[face];
}

void Orientation::display() const {
    cout << "SIDE TO FACE: ";
    for(int i = 0; i < side_to_face.size(); ++i) {
        cout << int(side_to_face[i]) << " ";
    }
    cout << endl << "FACE TO SIDE: ";
    for(int i = 0; i < face_to_side.size(); ++i) {
        cout << int(face_to_side[i]) << " ";
    }
    cout << endl;
    
}