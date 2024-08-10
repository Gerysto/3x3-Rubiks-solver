#ifndef _CUBE_
#define _CUBE_

#include <iostream>
#include <vector>
#include "state.hh"
#include "move_sequence.hh"
#include "orientation.hh"
#include "solver.hh"

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

    /*
     * Orientation is an object which allows the cube to know which face color should be turned when doing a certain move.
     */
    Orientation orientation;

    public:
    /*
     * Default constructor.
     * Creates a solved cube with the white top, green front orientation.
    */
    Cube();

    /*
     * Creates a cube given it's state and initial orientation.
    */
    Cube(State state, Orientation orientation);

    /*
     * Executes a sequence of moves expressed as a 'MoveSequence' object.
    */
    void execute_sequence(MoveSequence move_sequence);

    /*
     * Given a move in the standard rubik's cube notation, 
     * performs set move in the cube. 
     * 
     * (check the table of allowed moves from above)
    */
    void execute_sequence_in_notation(string seq);

    void random_scramble(int length);

    bool is_solvable();

    /*
     * Displays the state of the cube it's un-folded net. (Orientation doesn't affect it).
    */
    void print_state() const;

    MoveSequence test_solver(int i);
};

#endif