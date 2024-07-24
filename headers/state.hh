#include <iostream>
#include <cube_constants.hh>

/* 
 * The state that a rubik's cube is in, is defined to be the position
 * and orientation of each of it's corner and edge pieces.
*/
class State {
    public:

    /*
     * 'corners' is an array of 8 different integers, ranging from 0 to 23
     * each of these values corresponds with a stiker in the rubik's cube's
     * corners, and each position in the array corresponds to a position a 
     * corner could be in.
     * 
     * Each corner has 3 stikers in it, which have consecutive values.
     * 
     * In the solved state, the 'corners' array contains the multiples of three in 
     * increasing order. (which correspond with white and yellow stikers).
     * 
     * Check out the google sheets provided for the choices of pieces.
    */

    u_int8_t corners[8];

    /*
     * Bla Bla Bla for the edges as well.
    */

    u_int8_t edges[12]; 

    State();

    void cycle_corners(u_int8_t stikers[], int size, bool clockwhise);

    void cycle_edges(u_int8_t stikers[], int size, bool clockwhise);

    public:

    void turn_face(u_int8_t face_color_id, bool clockwhise);

    bool is_solved();

    bool is_solvable();

    void display();
};