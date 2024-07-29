#include "orientation.hh"

void Orientation::cycle_sides(vector<u_int8_t> sides, bool clockwhise) {
    u_int8_t aux;
    int len = sides.size();

    if(clockwhise) {
        first_face = side_to_face[sides[len-1]];
        first_side = face_to_side[first_face];

        for(int i = len-1; i > 0; --i) {
            int origin = side_to_face[sides[i-1]];
            int destination = side_to_face[sides[i]];
            side_to_face[sides[i]] = side_to_face[sides[i-1]];
            face_to_side[destination] = face_to_side[origin];
        }
        int destination = side_to_face[sides[0]];
        side_to_face[sides[0]] = first_face;
        face_to_side[destination] = first_side;

    } else {
        first_face = side_to_face[sides[0]];
        first_side = face_to_side[first_face];

        for(int i = 0; i < len-1; ++i) {
            int origin = side_to_face[sides[i+1]];
            int destination = side_to_face[sides[i]];
            side_to_face[sides[i]] = side_to_face[sides[i+1]];
            face_to_side[destination] = face_to_side[origin];
        }
        int destination = side_to_face[sides[len-1]];
        side_to_face[sides[len-1]] = first_face;
        face_to_side[destination] = first_side;
    }
}

void Orientation::X_rotation(bool clockwhise) {
    cycle_sides(X_rotation_centre_cycle, clockwhise);
}

void Orientation::Y_rotation(bool clockwhise) {
    cycle_sides(Y_rotation_centre_cycle, clockwhise);
}
    
void Orientation::Z_rotation(bool clockwhise) {
    cycle_sides(Z_rotation_centre_cycle, clockwhise);
}

u_int8_t Orientation::get_face(u_int8_t side) const {
    return side_to_face[side];
}

u_int8_t Orientation::get_side(u_int8_t face) const {
    return face_to_side[face];
}