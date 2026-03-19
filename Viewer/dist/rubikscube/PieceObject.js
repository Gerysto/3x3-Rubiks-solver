import { MeshObject } from "../engine/MeshObject.js";
export class PieceObject extends MeshObject {
    constructor(type, id) {
        super();
        this.piece_type = type;
        this.piece_id = id;
    }
    send_uniforms(gl, program) {
        super.send_uniforms(gl, program);
        gl.uniform1i(program.pieceTypeLoc, this.piece_type);
        gl.uniform1i(program.pieceIdLoc, this.piece_id);
    }
}
PieceObject.CORNER_PIECE = 0;
PieceObject.EDGE_PIECE = 1;
PieceObject.CENTER_PIECE = 2;
