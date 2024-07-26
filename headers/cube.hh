#include <iostream>
#include <vector>
#include "state.hh"

using namespace std;

/*
 * The 'cube' class represents a 3x3 rubik's cube, which is defined entirely off of 
 * it's 'state' which is the position of it's pieces and it's orientation, which is 
 * used to tell what side should move when doing a move. 
 * 
 * Allowed moves: 
 *
 *      (Clockwhise)
 * 
 *      R, L, U, D, F, B
 *      r, l, u, d, f, b
 *      M, E, S, X, Y, Z 
 *      
 *      (Counter-clockwhise)
 * 
 *      R', L', U', D', F', B'
 *      r', l', u', d', f', b'
 *      M', E', S', X', Y', Z'
 * 
 *      (Double move)
 * 
 *      R2, L2, U2, D2, F2, B2
 *      r2, l2, u2, d2, f2, b2
 *      M2, E2, S2, X2, Y2, Z2
*/

class Cube {
    
    private:
    
    /*
     * The state of a rubik's cube is defined by the position of each of it's pieces with respect to the center
     * by default a rubik's cube will be in it's solved state.
    */
    State state;

    /* 'orientation' is an array which stores the position of each center
     * each center color is assigned a value from 0 to 5
     * each side of the cube corresponds with an index of the array.
     * 
     * Color IDs:
     * 
     *      red = 0
     *      blue = 1
     *      red = 2
     *      green = 3
     *      orange = 4
     *      yellow = 5
     * 
     * Side IDs:
     *      
     *      top = 0
     *      back = 1
     *      right = 2
     *      front = 3
     *      left = 4
     *      bottom = 5
     * 
     * The default orientation is white top, green front. Which is represented
     * by the array being in increasing order.
     */
    vector<u_int8_t> orientation;


    /*
     * Changes the orientation of the cube by cycling the face's positions with respect to the user.
    */
    void cycle_faces(vector<u_int8_t> faces, bool clockwhise, bool double_move);

    public:
    /*
     * Default constructor.
     * Creates a solved cube with the white top, green front orientation.
    */
    Cube();

    /*
     * Creates a cube given it's state and initial orientation.
    */
    Cube(State state, vector<u_int8_t> orientation);

    /*
     * Turns a face, given the id of it's center color.
     * (e.g. allows you to turn the white face)
     * 
     * Check the 'Color IDs' table above.
    */
    void turn_face(u_int8_t face_color, bool clockwhise);

    /*
     * Turns a side given the id of it's relative position.
      (e.g. allows you to turn the front side)

      Check the 'Side IDs' table above.
    */
    void turn_side(u_int8_t side, bool clockwhise, bool double_move);

    /*
     * Given a move in the standard rubik's cube notation, 
     * performs set move in the cube. 
     * 
     * (check the table of allowed moves from above)
    */
    void move(string move);

    /*
     * Given a string containing a sequence of moves separated with spaces,
     * it performs the sequence set sequence on the cube.
     */
    void move_sequence(string sequence);


    void print_state();
};