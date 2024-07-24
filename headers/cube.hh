#include <iostream>
#include <state.hh>

using namespace std;

/*
 * The 'cube' class represents a 3x3 rubik's cube, which is defined entirely off of 
 * it's 'state' which is the position of it's pieces and it's orientation, which is 
 * used to tell what side should move when doing a move.  
*/

class Cube {
    
    public:
    
    /*
     * The state of a rubik's cube is defined by the position of each of it's pieces with respect to the center
     * by default a rubik's cube will be in it's solved state.
    */
    State state;

    /* 'orientation' is an array which stores the position of each center
     * each center color is assigned a value from 0 to 5
     * each side of the cube corresponds with an index of the array.
     * 
     * Color values:
     * 
     *      red = 0
     *      blue = 1
     *      red = 2
     *      green = 3
     *      orange = 4
     *      yellow = 5
     * 
     * Indexes of the sides:
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
    u_int8_t orientation[6];

    /*
     * Default constructor 
    */
   
    Cube();

    Cube(State state, u_int8_t orientation);

    void turn_face(u_int8_t face);

    void turn_side(u_int8_t side);
    
    void move(string move);

    void move_sequence(string sequence);
};