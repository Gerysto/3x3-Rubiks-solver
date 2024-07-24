#include <iostream>

const u_int8_t solved_corners[8] = {0, 3, 6, 8, 12, 15, 18, 21};
const u_int8_t solved_edges[12] =  {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22};

const u_int8_t default_orientation[6] = {0, 1, 2, 3, 4, 5};

const u_int8_t W_face_corner_cycle[4] = {0, 3, 6, 9};
const u_int8_t B_face_corner_cycle[4] = {5, 1, 14, 16};
const u_int8_t R_face_corner_cycle[4] = {8, 4, 17, 19};
const u_int8_t G_face_corner_cycle[4] = {11, 7, 20, 22};
const u_int8_t O_face_corner_cycle[4] = {2, 10, 23, 13};
const u_int8_t Y_face_corner_cycle[4] = {12, 21, 18, 15};
		
const u_int8_t W_face_edge_cycle[4] = {0, 2, 4, 6};
const u_int8_t B_face_edge_cycle[4] = {1, 8, 17, 10};
const u_int8_t R_face_edge_cycle[4] = {3, 11, 19, 13};
const u_int8_t G_face_edge_cycle[4] = {5, 12, 21, 14};
const u_int8_t O_face_edge_cycle[4] = {7, 15, 23, 9};
const u_int8_t Y_face_edge_cycle[4] = {22, 20, 18, 16};

const u_int8_t X_rotation_centre_cycle[4] = {0, 1, 5, 3};
const u_int8_t Y_rotation_centre_cycle[4] = {1, 2, 3, 4};
const u_int8_t Z_rotation_centre_cycle[4] = {0, 2, 5, 4};







		