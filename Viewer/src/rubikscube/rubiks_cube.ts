import { PieceObject } from './PieceObject.js';
import { Scene } from '../engine/Scene.js';
import { ShaderProgram } from '../shaders/ShaderProgram.js';
import { corner_TG, edge_TG, center_TG } from './piece_transformations.js';
import { PIECES_INVOLVED, AXIS_OF_ROTATION, SOLVED } from './rubiks_constants.js';
import { MeshObject } from '../engine/MeshObject.js';

const CORNER_MODEL_URL = 'assets/models/corner_piece.obj';
const EDGE_MODEL_URL   = 'assets/models/edge_piece.obj';
const CENTER_MODEL_URL = 'assets/models/center_piece.obj';

export class State {
    corners: number[];
    edges: number[];

    constructor(corners: number[], edges: number[]) {
        this.corners = corners;
        this.edges = edges;
    }
}

export class RubiksCube {

    corners: PieceObject[];
    edges: PieceObject[];
    centers: PieceObject[];
    state: State;

    constructor() {
        this.corners = [];
        this.edges = [];
        this.centers = [];
        this.state = new State(SOLVED.CORNERS, SOLVED.EDGES);
    }

    private async load() {
        const base_corner = new MeshObject();
        const base_edge   = new MeshObject();
        const base_center = new MeshObject(); 

        await base_corner.readObj(CORNER_MODEL_URL);
        await base_edge  .readObj(EDGE_MODEL_URL);
        await base_center.readObj(CENTER_MODEL_URL);

        for (let i = 0; i < 8; ++i) {
            let obj: PieceObject = new PieceObject(PieceObject.CORNER_PIECE, i);
            obj.copy_properties_of(base_corner);
            obj.ModelTransform = corner_TG[i];
            this.corners.push(obj);
        }

        for (let i = 0; i < 12; ++i) {
            let obj: PieceObject = new PieceObject(PieceObject.EDGE_PIECE, i);
            obj.copy_properties_of(base_edge);
            obj.ModelTransform = edge_TG[i];
            this.edges.push(obj);
        }

        for (let i = 0; i < 6; ++i) {
            let obj: PieceObject = new PieceObject(PieceObject.CENTER_PIECE, i);
            obj.copy_properties_of(base_center);
            obj.ModelTransform = center_TG[i];
            this.centers.push(obj);
        }
    }

    async createVAOs(gl: WebGL2RenderingContext, program: ShaderProgram) {
        await this.load();
        for (let obj of this.corners) obj.createVAO(gl, program);
        for (let obj of this.edges)   obj.createVAO(gl, program);
        for (let obj of this.centers) obj.createVAO(gl, program);
    }

    add_to_scene(scene: Scene) {
        for (let obj of this.corners) scene.addObject(obj);
        for (let obj of this.edges)   scene.addObject(obj);
        for (let obj of this.centers) scene.addObject(obj);
    }

    /**
     * Partilly performs one of the moves: {U, R, F, D, L, B}, according to the interpolation value @param t provided 
     * @param move one of the outer moves in cubing notation {U, R, F, D, L, B}
     * @param clockwhise whether the turn should be clockwhise {U}, or anticlockwhise {U'}
     * @param t interpolation parameter (ranging from 0 to 1)
     */
    perform_move(move: string, clockwhise: boolean, t: number) {
        const pieces_involved = PIECES_INVOLVED.get(move) as number[][];

        let angle = 90*t;
        if (clockwhise) angle *= -1;

        const aux = AXIS_OF_ROTATION.get(move)
        if (aux == undefined) {
            throw Error("Invalid move: '" + move + "' ");
        }
        const [x, y, z] = aux as number[];

        // Corners
        for (let i of pieces_involved[0]) {
            // Divide index by 3 to conver from 'stiker index' to 'piece index'
            const pos = Math.floor(i/3);
            const piece = Math.floor(this.state.corners[pos]/3);
        
            this.corners[piece].ModelTransform = new J3DIMatrix4();
            this.corners[piece].ModelTransform.rotate(angle, x, y, z);
            this.corners[piece].ModelTransform.multiply(corner_TG[pos]);

            const orientation = this.state.corners[pos]%3;
            if (orientation != 0) {
                // Orient the corner:
                this.corners[piece].ModelTransform.rotate(
                    -orientation*360/3, -1,1,-1
                );
            }
        }

        // Edges: 
        for (let i of pieces_involved[1])   {
            // Divide index by 2 to conver from 'stiker index' to 'piece index'
            const pos = Math.floor(i/2);
            const piece = Math.floor(this.state.edges[pos]/2);

            this.edges[piece].ModelTransform = new J3DIMatrix4();
            this.edges[piece].ModelTransform.rotate(angle, x, y, z);
            this.edges[piece].ModelTransform.multiply(edge_TG[pos]);

            const orientation = this.state.edges[pos]%2;
            if (orientation != 0) {
                // Orient the edge:
                this.edges[piece].ModelTransform.rotate(
                    180, 0,1,-1
                );
            }
        }

        // Centers: 
        for (let i of pieces_involved[2]) {
            this.centers[i].ModelTransform = new J3DIMatrix4();
            this.centers[i].ModelTransform.rotate(angle, x, y, z);
            this.centers[i].ModelTransform.multiply(center_TG[i]);
        }
    }

    update_state(corners: number[], edges: number[]) {
        this.state.corners = corners;
        this.state.edges = edges;

        console.log("Updating state: ", corners, edges);
        for (let i = 0; i < corners.length; ++i) {
            const piece = Math.floor(corners[i]/3);
            this.corners[piece].ModelTransform = new J3DIMatrix4();
            this.corners[piece].ModelTransform.multiply(corner_TG[i]);
            
            const orientation = corners[i]%3;
            if (orientation != 0) {
                // Orient the corner:
                this.corners[piece].ModelTransform.rotate(
                    -orientation*360/3, -1,1,-1
                );
            }
        }

        for (let i = 0; i < edges.length; ++i) {
            const piece = Math.floor(edges[i]/2); 
            this.edges[piece].ModelTransform = new J3DIMatrix4();
            this.edges[piece].ModelTransform.multiply(edge_TG[i]);

            const orientation = edges[i]%2;
            if (orientation != 0) {
                // Orient the edge:
                this.edges[piece].ModelTransform.rotate(180, 0,1,-1);
            }
        }

        for (let i in this.centers) {
            this.centers[i].ModelTransform = center_TG[i]
        }
    }
}