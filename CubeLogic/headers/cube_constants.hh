#ifndef _CONSTS_
#define _CONSTS_

#include <iostream>
#include <vector>

using namespace std;
typedef unsigned char u_int8_t;

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

const vector<vector<u_int8_t>> layers_involving_corner = {
    {1, 5, 6}, // moves which involve the WBO corner
    {1, 2, 6}, // moves which involve the WRB corner
    {1, 2, 3}, // moves which involve the WGR corner
    {1, 3, 5}, // moves which involve the WOG corner
    {4, 5, 6}, // moves which involve the YOB corner
    {4, 2, 6}, // moves which involve the YBR corner
    {4, 2, 3}, // moves which involve the YRG corner
    {4, 3, 5}, // moves which involve the YGO corner
};

const vector<vector<u_int8_t>> layers_involving_edge = {
    {1, 6, 8}, // moves which involve the WB edge 
    {1, 2, 9}, // moves which involve the WR edge
    {1, 3, 8}, // moves which involve the WG edge
    {1, 5, 9}, // moves which involve the WO edge
    {5, 6, 7}, // moves which involve the BO edge
    {2, 6, 7}, // moves which involve the BR edge
    {2, 3, 7}, // moves which involve the GR edge
    {3, 5, 7}, // moves which involve the GO edge
    {4, 6, 8}, // moves which involve the YB edge
    {2, 4, 9}, // moves which involve the YR edge
    {3, 4, 8}, // moves which involve the YG edge
    {4, 5, 9}, // moves which involve the YO edge
    
};

const vector<char> id_to_color = {'W', 'R', 'G', 'Y', 'O', 'B'};

const std::string stiker_positions = "           | 00 50 03 |\n           | 56 90 52 |\n           | 09 54 06 |\n           - -------- -\n| 02 57 10 | 11 55 07 | 08 53 04 |\n| 59 94 65 | 64 92 62 | 63 91 61 |\n| 13 73 23 | 22 71 20 | 19 69 17 |\n           - -------- -\n           | 21 70 18 |\n           | 72 93 68 |\n           | 12 66 15 |\n           - -------- -\n           | 14 67 16 |\n           | 58 95 60 |\n           | 01 51 05 |";
/*
const std::vector<int> problematic_corner_permutations = {3, 4, 8, 11, 12, 15, 19, 20, 26, 29, 33, 34, 37, 38, 42, 45, 49, 53, 54, 57, 62, 65, 66, 70, 72, 76,
    79, 80, 87, 88, 91, 95, 96, 99, 103, 107, 108, 112, 116, 119, 121, 122, 126, 130, 133, 137, 141, 142, 146, 149, 153, 154, 157, 158, 162, 165, 171,
    172, 176, 179, 180, 183, 187, 188, 192, 195, 199, 203, 204, 208, 212, 215, 217, 218, 222, 226, 229, 233, 237, 238, 241, 245, 246, 249, 254, 257,
    258, 262, 264, 268, 271, 272, 279, 280, 283, 287, 288, 292, 295, 296, 303, 304, 307, 311, 313, 317, 318, 321, 326, 329, 330, 334, 337, 338, 342,
    346, 349, 353, 357, 358, 360, 363, 367, 371, 372, 376, 380, 383, 387, 388, 392, 395, 396, 399, 403, 404, 410, 413, 417, 418, 421, 422, 426, 429,
    433, 434, 438, 442, 445, 449, 453, 454, 456, 459, 463, 467, 468, 472, 476, 479, 480, 484, 487, 488, 495, 496, 499, 503, 505, 509, 510, 513, 518,
    521, 522, 526, 530, 533, 537, 538, 541, 542, 546, 549, 555, 556, 560, 563, 564, 567, 571, 572};
*/

const vector<vector<int>> permutations = {{0, 1, 2, 3}
,{0, 1, 3, 2}
,{0, 2, 1, 3}
,{0, 2, 3, 1}
,{0, 3, 1, 2}
,{0, 3, 2, 1}
,{1, 0, 2, 3}
,{1, 0, 3, 2}
,{1, 2, 0, 3}
,{1, 2, 3, 0}
,{1, 3, 0, 2}
,{1, 3, 2, 0}
,{2, 0, 1, 3}
,{2, 0, 3, 1}
,{2, 1, 0, 3}
,{2, 1, 3, 0}
,{2, 3, 0, 1}
,{2, 3, 1, 0}
,{3, 0, 1, 2}
,{3, 0, 2, 1}
,{3, 1, 0, 2}
,{3, 1, 2, 0}
,{3, 2, 0, 1}
,{3, 2, 1, 0}};

#endif