#ifndef _STATE_
#define _STATE_

#include <iostream>
#include <vector>
#include "cube_constants.hh"
#include "move_sequence.hh"

using namespace std;

/* 
 * The state that a rubik's cube is in, is defined to be the position
 * and orientation of each of it's corner and edge pieces.
*/
class State {
    private:

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
     * Check out the state structure reference for more details on the internal
     * representation of the cube's state.
    */
    vector<u_int8_t> corners;

    /*
     * 'edges' is an array of 12 different integers, ranging from 0 to 23
     * each of these values corresponds with a stiker in the rubik's cube's
     * edges, and each position in the array corresponds to a position an edge 
     * could be in.
     * 
     * Each edge has 2 stikers in it, which have consecutive values.
     * 
     * In the solved state, the 'edges' array contains the even numbers in 
     * increasing order. (which correspond with white, yellow, green and blue stikers).
     * 
     * Check out the state structure reference for more details on the internal
     * representation of the cube's state.
    */
    vector<u_int8_t> edges; 

    /*
     * Returns the corner stiker located in a given position of the cube.  
    */
    u_int8_t get_corner_stiker(u_int8_t position) const;

    /*
     * Returns the edge stiker located in a given position of the cube.  
    */
    u_int8_t get_edge_stiker(u_int8_t position) const;

    /*
     * Places a given corner stiker in an other's position of the cube.
    */
    void place_corner_stiker(u_int8_t stiker, u_int8_t position);

    /*
     * Places a given edge stiker in an other's position of the cube.
    */
    void place_edge_stiker(u_int8_t stiker, u_int8_t position);

    /*
     * Given an array of corner stikers, cycles the pieces containing them such that each
     * stiker goes to the position of the next (and the final one goes to the first).
    */
    void cycle_corners(const vector<u_int8_t>& stikers, bool clockwhise);

    /*
     * Given an array of edge stikers, it cycles the pieces containing them such that each
     * stiker goes to the position of the next (and the final one goes to the beginning).
    */
    void cycle_edges(const vector<u_int8_t>& stikers, bool clockwhise);

    public:

    /*
     * Default constructor. 
     * Generates the solved state of the Rubik's cube.
    */
    State();

    /*
     * Checks whether it is the solved state.
    */
    bool is_solved() const;

    /*
     * Checks whether it's a valid state (whether it can be solved with
     * normal Rubik's cube moves).
    */
    bool is_solvable() const;

    /*
     * Displays the current state of the rubik's cube as characters in the terminal.
    */
    void log_state() const;

    /*
     * Displays the current state of the rubik's cube by displaying it's un-folded net.
    */
    void display() const;

    /*
     * Given a the id of a face's color, it turns the face with set color
     * clockwhise if the boolean is true, and anticlockwhise if it's false.
     */
    void turn_face(u_int8_t face, bool clockwhise);

    /*
     * Given a MoveSequence, this method executes it on the cube.
    */
    void execute_sequence(MoveSequence seq);

    bool operator== (const State& s) const;

    bool operator< (const State& s) const;

    friend class Solver;
};

#endif