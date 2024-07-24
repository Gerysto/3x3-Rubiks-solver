#include <iostream>
#include <vector>

using namespace std;

const vector<u_int8_t> solved_corners = {0, 3, 6, 8, 12, 15, 18, 21};
const vector<u_int8_t> solved_edges =  {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22};

const vector<u_int8_t> default_orientation = {0, 1, 2, 3, 4, 5};

const vector<u_int8_t> W_face_corner_cycle = {0, 3, 6, 9};
const vector<u_int8_t> B_face_corner_cycle = {5, 1, 14, 16};
const vector<u_int8_t> R_face_corner_cycle = {8, 4, 17, 19};
const vector<u_int8_t> G_face_corner_cycle = {11, 7, 20, 22};
const vector<u_int8_t> O_face_corner_cycle = {2, 10, 23, 13};
const vector<u_int8_t> Y_face_corner_cycle = {12, 21, 18, 15};
		
const vector<u_int8_t> W_face_edge_cycle = {0, 2, 4, 6};
const vector<u_int8_t> B_face_edge_cycle = {1, 8, 17, 10};
const vector<u_int8_t> R_face_edge_cycle = {3, 11, 19, 13};
const vector<u_int8_t> G_face_edge_cycle = {5, 12, 21, 14};
const vector<u_int8_t> O_face_edge_cycle = {7, 15, 23, 9};
const vector<u_int8_t> Y_face_edge_cycle = {22, 20, 18, 16};

const vector<u_int8_t> X_rotation_centre_cycle = {0, 5, 3, 2};
const vector<u_int8_t> Y_rotation_centre_cycle = {1, 2, 4, 5};
const vector<u_int8_t> Z_rotation_centre_cycle = {0, 1, 3, 4};









		