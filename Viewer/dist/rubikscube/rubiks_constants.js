// In the Corner and Edge cycles, each number refers to a 'stiker' in a piece.
// 
//  - For corners: dividing by 3 gives the 'piece index' and taking mod 3 gives the 'piece orientation'
//  - For edges: dividing by 2 gives the 'piece index' and taking mod 2 gives the 'piece orientation'
/**
 *  Corners involved in each turn (clockwhise)
 */
export const CORNER_CYCLE = {
    W_FACE: [0, 3, 6, 9],
    B_FACE: [5, 1, 14, 16],
    R_FACE: [8, 4, 17, 19],
    G_FACE: [11, 7, 20, 22],
    O_FACE: [2, 10, 23, 13],
    Y_FACE: [12, 21, 18, 15]
};
/**
 *  Edges involved in each turn (clockwhise)
 */
export const EDGE_CYCLE = {
    // Regular face turns
    W_FACE: [0, 2, 4, 6],
    B_FACE: [1, 8, 17, 10],
    R_FACE: [3, 11, 19, 13],
    G_FACE: [5, 12, 21, 14],
    O_FACE: [7, 15, 23, 9],
    Y_FACE: [22, 20, 18, 16],
    // Slice turns (middle layers)
    WY_SLICE: [8, 11, 12, 15],
    RO_SLICE: [4, 1, 16, 20],
    GB_SLICE: [7, 2, 19, 22]
};
export const SOLVED = {
    CORNERS: [0, 3, 6, 9, 12, 15, 18, 21],
    EDGES: [0, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22]
};
/**
 *  Edges involved in each turn (clockwhise)
 */
export const CENTERS_INVOLVED = {
    W_FACE: [0],
    R_FACE: [1],
    G_FACE: [2],
    Y_FACE: [3],
    O_FACE: [4],
    B_FACE: [5],
    WY_SLICE: [1, 2, 4, 5],
    RO_SLICE: [0, 2, 3, 5],
    GB_SLICE: [0, 1, 3, 4]
};
/**
 * ASSUMTION: No cube rotations or slice moves have been performed!!!
 *
 *   - TODO: Get rid of this assumtion
 */
export const PIECES_INVOLVED = new Map;
PIECES_INVOLVED.set("U", [CORNER_CYCLE.W_FACE, EDGE_CYCLE.W_FACE, CENTERS_INVOLVED.W_FACE]);
PIECES_INVOLVED.set("R", [CORNER_CYCLE.R_FACE, EDGE_CYCLE.R_FACE, CENTERS_INVOLVED.R_FACE]);
PIECES_INVOLVED.set("F", [CORNER_CYCLE.G_FACE, EDGE_CYCLE.G_FACE, CENTERS_INVOLVED.G_FACE]);
PIECES_INVOLVED.set("D", [CORNER_CYCLE.Y_FACE, EDGE_CYCLE.Y_FACE, CENTERS_INVOLVED.Y_FACE]);
PIECES_INVOLVED.set("L", [CORNER_CYCLE.O_FACE, EDGE_CYCLE.O_FACE, CENTERS_INVOLVED.O_FACE]);
PIECES_INVOLVED.set("B", [CORNER_CYCLE.B_FACE, EDGE_CYCLE.B_FACE, CENTERS_INVOLVED.B_FACE]);
export const AXIS_OF_ROTATION = new Map;
AXIS_OF_ROTATION.set("R", [1, 0, 0]);
AXIS_OF_ROTATION.set("U", [0, 1, 0]);
AXIS_OF_ROTATION.set("F", [0, 0, 1]);
AXIS_OF_ROTATION.set("L", [-1, 0, 0]);
AXIS_OF_ROTATION.set("D", [0, -1, 0]);
AXIS_OF_ROTATION.set("B", [0, 0, -1]);
