#ifndef _SEQUENCE_
#define _SEQUENCE_

#include <iostream>
#include <vector>
#include <exception>
#include "orientation.hh"

using namespace std;

class InvalidSequenceException: public exception {
    virtual const char* what() const throw();
};

class MoveSequence {
    private:
    
    /*
     * A sequence of moves is a vector of integers which codifiy the faces to turn using the following
     * chart:
     * 
     *  1  -> white face turn
     *  2  -> red face turn
     *  3  -> green face turn
     *  4  -> yellow face turn
     *  5  -> orange face turn
     *  6  -> blue face turn
     *  7  -> white-yellow slice move (clockwhise as seen from white)
     *  8  -> red-orange   slice move (clockwhise as seen from red)
     *  9  -> green-blue   slice move (clockwhise as seen from green)
     *  10 -> yellow-white slice move (clockwhise as seen from yellow)
     *  11 -> orange-red   slice move (clockwhise as seen from orange)
     *  12 -> blue-green   slice move (clockwhise as seen from blue)
     * 
     * positive = clockwhise
     * negative = counter-clockwhise
     * 
     * (Notice that double moves are encoded as 2 different moves).
    */
    vector<int8_t> move_sequence;

    /*
     * Given a move in standard cubing notation, this creates a MoveSequance object using it.
     * (and updates the orientaion of the cube acordingly).
    */
    MoveSequence translate_single_move(Orientation& orientation, const string& move) const;

    public: 

    /*
     * Default constructor.
     * Creates an empty move sequence.
    */
    MoveSequence();

    /*
     * Creates a MoveSequence object using the cube's initial orientation and a move sequence in
     * standard cubing notation.
    */
    MoveSequence(Orientation& orientation, const string& move_sequence);


    static bool is_move_valid(const string& move);
    static bool is_sequence_valid(const string& seq);

    /*
     * Generates a random sequence of moves with the length given.
    */
    void generate_random(int length);

    /*
     * Adds a new move to the end of the sequence.
    */
    void add_move(int8_t move);

    /*
     * Returns the inverse of the this sequence.
    */
    MoveSequence inverse() const;

    /*
     * Translates the move sequence in standard cubing notation.
    */
    string to_notation(Orientation orientation) const;

    /*
     * Given a new sequence, this method attatches it to the end of the current one.
    */
    MoveSequence append(const MoveSequence& seq) const;

    /*
     * Given a new sequence, this method returns the commutator: [*this; seq]
     * (in general, the commutator [A; B] is A B A' B').
    */
    MoveSequence commutate(const MoveSequence& seq) const;

    /*
     * Given a new sequence, this method conjugates it with the implicit object.
     * That is, it returns: A B A' where A represents the setup_moves and B is the implicit sequence.
    */
    MoveSequence conjugate(const MoveSequence& setup_moves) const;

    /*
     * Returns the move in a given position of the sequence. (indexed starting from 0)
    */
    int8_t get_move(int position) const;

    /*
     * Returns the ammount of moves in the sequence.
    */
    int size() const;

    /*
     * Displays the raw sequence in the terminal. 
    */
    void print() const;

    static MoveSequence compress(const MoveSequence &m); 
};

#endif