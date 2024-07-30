#ifndef _SEQUENCE_
#define _SEQUENCE_

#include <iostream>
#include <vector>
#include "orientation.hh"

using namespace std;

class MoveSequence {
    private:
    
    /*
     * A sequence of moves is a vector of integers which codifiy the faces to turn using the following
     * chart:
     * 
     *  1 -> white face turn
     *  2 -> red face turn
     *  3 -> green face turn
     *  4 -> yellow face turn
     *  5 -> orange face turn
     *  6 -> blue face turn
     *  7 -> yellow-white slice move (clockwhise as seen from yellow)
     *  8 -> orange-red   slice move (clockwhise as seen from orange)
     *  9 -> green-blue   slice move (clockwhise as seen from green)
     * 
     * positive = clockwhise
     * negative = counter-clockwhise
     * 
     * (Notice that double moves as encoded as 2 different moves).
    */
    vector<int8_t> move_sequence;

    MoveSequence translate_single_move(Orientation& orientation, const string& move) const;

    public: 

    MoveSequence();

    MoveSequence(Orientation& orientation, const string& move_sequence);

    /*
     * Returns the inverse of the this sequence.
    */
    MoveSequence inverse() const;

    string to_notation(Orientation orientation) const;

    void add_move(int8_t move);

    int size();

    int8_t get_move(int position);

    MoveSequence append(const MoveSequence& seq) const;

    MoveSequence commutate(const MoveSequence& seq) const;

    MoveSequence conjugate(const MoveSequence& setup_moves) const;

    void print();
};

#endif