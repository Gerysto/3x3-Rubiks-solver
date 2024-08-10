#ifndef _CONSTS_
#define _CONSTS_

#include <iostream>
#include <vector>


using namespace std;

const vector<u_int8_t> solved_corners = {0, 3, 6, 9, 12, 15, 18, 21};
const vector<u_int8_t> corner_stiker_colors = {0,5,4,0,1,5,0,2,1,0,4,2,3,4,5,3,5,1,3,1,2,3,2,4};
const vector<u_int8_t> solved_edges =  {0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22};
const vector<u_int8_t> edge_stiker_colors =   {0,5,0,1,0,2,0,4,5,4,5,1,2,1,2,4,3,5,3,1,3,2,3,4};

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

const vector<u_int8_t> WY_slice_edge_cycle = {8, 11, 12, 15};
const vector<u_int8_t> RO_slice_edge_cycle = {4, 1, 16, 20};
const vector<u_int8_t> GB_slice_edge_cycle = {7, 2, 19, 22};

const vector<u_int8_t> X_rotation_centre_cycle = {0, 5, 3, 2};
const vector<u_int8_t> Y_rotation_centre_cycle = {1, 2, 4, 5};
const vector<u_int8_t> Z_rotation_centre_cycle = {0, 1, 3, 4};

const vector<char> id_to_color = {'W', 'R', 'G', 'Y', 'O', 'B'};

const std::string stiker_positions = "           | 00 50 03 |\n           | 56 90 52 |\n           | 09 54 06 |\n           - -------- -\n| 02 57 10 | 11 55 07 | 08 53 04 |\n| 59 94 65 | 64 92 62 | 63 91 61 |\n| 13 73 23 | 22 71 20 | 19 69 17 |\n           - -------- -\n           | 21 70 18 |\n           | 72 93 68 |\n           | 12 66 15 |\n           - -------- -\n           | 14 67 16 |\n           | 58 95 60 |\n           | 01 51 05 |";





#endif