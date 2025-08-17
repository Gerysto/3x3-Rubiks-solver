#ifndef _SOLVER_
#define _SOLVER_
#include <queue>
#include <set>
#include "state.hh"


class Solver {
    
    private:
        State state;

    /*
     * Given a layer's ID, this function returns the corners and edges involved when turning that layer.
    */
    void get_pieces_in_layer(u_int8_t layer, vector<u_int8_t>& corners, vector<u_int8_t>& edges);

    MoveSequence find_2_corner_flip(u_int8_t s1_p1, u_int8_t s2_p1, u_int8_t s1_p2);

    MoveSequence find_2_edge_flip(u_int8_t s1_p1, u_int8_t s2_p1, u_int8_t s1_p2);

    MoveSequence find_corner_3_cycle(u_int8_t stiker_1, u_int8_t stiker_2, u_int8_t stiker_3);
    
    
    MoveSequence find_edge_3_cycle(u_int8_t stiker_1, u_int8_t stiker_2, u_int8_t stiker_3);

    /*
     * Given a layer's ID, a piece, which isn't located in this layer and the position where in the layer
     * where the piece belongs, this method will find a sequence of moves which will insert the piece to its position.
    */
    MoveSequence insert_corner(u_int8_t layer, u_int8_t piece, u_int8_t position);

    /*
     * Given a layer's ID, an edge, which isn't located in this layer and the position where in the layer
     * where the piece belongs, this method will find a sequence of moves which will insert the edge to its position.
    */
    MoveSequence insert_edge(u_int8_t layer, u_int8_t piece, u_int8_t position);

    /*
     * Finds a set of moves which will position the pieces 0, 1, and 2 such that it's easier to find a commutator
     * that will cycle them.
     * 
     * Returns the final postions of this pieces as references.
     * also returns a second move sequence which only involves one layer (called the layer of reference LOR), and will be the second part of the commutator.
    */
    MoveSequence corner_setup_moves(u_int8_t& piece_0_pos, u_int8_t& piece_1_pos, u_int8_t& piece_2_pos, int8_t& LOR_move);

    MoveSequence edge_setup_moves(u_int8_t& piece_0_pos, u_int8_t& piece_1_pos, u_int8_t& piece_2_pos, int8_t& LOR_move);

    bool is_corner_one_move_away(const State& s, u_int8_t piece, u_int8_t position, int8_t& move);

    bool is_edge_one_move_away(const State& s, u_int8_t piece, u_int8_t target, int8_t& move);

    bool full_layer_match(State state1, State state2, u_int8_t layer);

    /*
     * Given a state, and a subset of corners positions on the cube, returns a boolean which indicates whether
     * all the corner positions in the subset hold the same pieces in the given state and in the implicit parameter.
    */
    static bool corner_subset_match(State state1, State state2, const vector<u_int8_t>& subset);

    /*
     * Given a state, and a subset of edge positions on the cube, returns a boolean which indicates whether
     * all the edge positions in the subset hold the same pieces in the given state and in the implicit parameter.
    */
    static bool edge_subset_match(State state1, State state2, const vector<u_int8_t>& subset);

    /*
     * Returns a vector containing a corner stiker id from each corner in the layer given.
     */
    static vector<u_int8_t> get_corners_in_layer(u_int8_t layer);

    /*
     * Returns a vector containing an edge stiker id from each edge in the layer given.
     */
    static vector<u_int8_t> get_edges_in_layer(u_int8_t layer);

    MoveSequence solve_corners();

    MoveSequence solve_edges();

    
    public:

    Solver(State state);

    MoveSequence solve();

    MoveSequence test(int i, int j, int k);
};

#endif