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
     * Given a layer's ID, a piece which lies in this layer and the location where it belongs, within this layer,
     * this method will find a seqüence of moves which only modifies the layer given, such that the piece ends up
     * where it belongs.
     * 
     * This method will not work unless the piece involved can reach its position in a single or double move of the 
     * layer given.
    */
    MoveSequence move_corner_within_layer(u_int8_t layer, u_int8_t piece, u_int8_t position);

    /*
     * Given a layer's ID, a piece which lies in this layer and the location where it belongs, within this layer,
     * this method will find a seqüence of moves which only modifies the layer given, such that the piece ends up
     * where it belongs.
     * 
     * This method will not work unless the piece involved can reach its position in a single or double move of the 
     * layer given.
    */
    MoveSequence move_edge_within_layer(u_int8_t layer, u_int8_t piece, u_int8_t position);

    /*
     * Given a corner's location in the cube, this method will return a vector of the layers whose movements involve this piece.
    */
    vector<u_int8_t> get_layers_involving_corner(u_int8_t corner);

    /*
     * Given an edge's location in the cube, this method will return a vector of the layers whose movements involve this piece.
    */
    vector<u_int8_t> get_layers_involving_edge(u_int8_t edge);


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
    
    public:

    Solver(State state);

    MoveSequence solve();

    MoveSequence test(int i);
};

#endif