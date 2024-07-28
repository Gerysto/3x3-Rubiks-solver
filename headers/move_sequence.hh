#include <iostream>
#include <vector>
using namespace std;

class MoveSequence {
    private:
    
    /*
     * A sequence of moves is a vector of integers which codifiy the faces to turn using the following
     * chart:
     * 
     * - 0 -> white face turn
     * - 2 -> red face turn
     * - 4 -> green face turn
     * - 6 -> yellow face turn
     * - 8 -> orange face turn
     * - 10 -> blue face turn
     * - 12 -> white-yellow slice move (clockwhise as seen from white)
     * - 14 -> red-orange   slice move (clockwhise as seen from red)
     * - 16 -> green-blue   slice move (clockwhise as seen from green)
     * 
     * Even = clockwhise
     * Odd  = counter-clockwhise
     * 
     * (Notice that double moves as encoded as 2 different moves).
    */
    vector<u_int8_t> move_sequence;

    MoveSequence();

    MoveSequence(vector<u_int8_t> orientation, string move_sequence);

    /*
     * Returns the inverse of the this sequence.
    */
    MoveSequence inverse();

    /*

    */
    string get_notation(vector<u_int8_t> orientation);


}