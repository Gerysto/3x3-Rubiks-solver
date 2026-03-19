import { MeshObject } from "../engine/MeshObject";
import { ShaderProgram } from "../shaders/ShaderProgram";

export class PieceObject extends MeshObject {

    static readonly CORNER_PIECE = 0;
    static readonly EDGE_PIECE   = 1;
    static readonly CENTER_PIECE = 2;

    piece_type : number;
    piece_id : number;

    constructor(type: number, id: number) {
        super();
        this.piece_type = type;
        this.piece_id = id;
    }

    send_uniforms(gl: WebGL2RenderingContext, program: ShaderProgram) {
        super.send_uniforms(gl, program);
        gl.uniform1i(program.pieceTypeLoc, this.piece_type);
        gl.uniform1i(program.pieceIdLoc, this.piece_id);
    }

}