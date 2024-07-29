#include "cube.hh"

class Solver {
    void solve();
    
    /*
     * Given a layer's ID, a piece, which isn't located in this layer and the position where in the layer
     * where the piece belongs, this method will find a sequence of moves which will insert the piece to its position.
    */
    void insert_corner(u_int8_t layer, u_int8_t piece, u_int8_t position);

    /*
     * Given a layer's ID, a piece which lies in this layer and the location where it belongs, within this layer,
     * this method will find a seqüence of moves which only modifies the layer given, such that the piece ends up
     * where it belongs.
     * 
     * This method will not work unless the piece involved can reach its position in a single or double move of the 
     * layer given.
    */
    void move_corner_within_layer(u_int8_t layer, u_int8_t piece, u_int8_t position);


    /*
     * Given a corner's location in the cube, this method will a vector of the layers whose movements involve this piece.
    */
    vector<u_int8_t> get_layers_involving_corner(u_int8_t corner);

    bool corner_subset_match(State state, vector<u_int8_t> subset);
    /*
     * Given a layer's ID, an edge, which isn't located in this layer and the position where in the layer
     * where the piece belongs, this method will find a sequence of moves which will insert the edge to its position.
    */
    void insert_edge(u_int8_t layer, u_int8_t piece, u_int8_t position);

    /*
     * Given a layer's ID, a piece which lies in this layer and the location where it belongs, within this layer,
     * this method will find a seqüence of moves which only modifies the layer given, such that the piece ends up
     * where it belongs.
     * 
     * This method will not work unless the piece involved can reach its position in a single or double move of the 
     * layer given.
    */
    void move_corner_within_layer(u_int8_t layer, u_int8_t piece, u_int8_t position);

    /*
     * Given an edge's location in the cube, this method will a vector of the layers whose movements involve this piece.
    */
    vector<u_int8_t> get_layers_involving_edge(u_int8_t edge);

    bool edge_subset_match(State state, vector<u_int8_t> subset);
};