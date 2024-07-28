#include <iostream>
#include <vector>
using namespace std;

class Orientation {
    private:

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

    /*
     * Array where the slots correspond with sides (Top, Right, Front, Bottom, Left, Back)
     * and theyr values correspond with faces (White, Red, Green, Yellow, Orange, Blue) 
    */
    vector<u_int8_t> side_to_face;

    /*
     * Array where the slots correspond with faces (White, Red, Green, Yellow, Orange, Blue)
     * and theyr values correspond with sides (Top, Right, Front, Bottom, Left, Back) 
    */
    vector<u_int8_t> face_to_side;


    void cycle_sides(vector<u_int8_t> sides, bool clockwhise, bool double_move);

    public:

    u_int8_t get_face(u_int8_t side) const;

    u_int8_t get_side(u_int8_t face) const;

    
}