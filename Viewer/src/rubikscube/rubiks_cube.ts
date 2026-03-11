import {MeshObject} from '../engine/MeshObject.js';
import { Scene } from '../engine/Scene.js';
import { ShaderProgram } from '../shaders/ShaderProgram.js';
import { corner_TG, edge_TG, center_TG } from './piece_transformations.js';
import { PIECES_INVOLVED, AXIS_OF_ROTATION, SOLVED } from './rubiks_constants.js';

const CORNER_MODELS_URL = 'assets/models/corners/c#.obj';
const EDGE_MODELS_URL   = 'assets/models/edges/e#.obj';
const CENTER_MODELS_URL = 'assets/models/centers/f#.obj';

export class State {
    corners: number[];
    edges: number[];

    constructor(corners: number[], edges: number[]) {
        this.corners = corners;
        this.edges = edges;
    }
}

export class RubiksCube {

    corners: MeshObject[];
    edges: MeshObject[];
    centers: MeshObject[];
    state: State;

    constructor() {
        this.corners = [];
        this.edges = [];
        this.centers = [];
        this.state = new State(SOLVED.CORNERS, SOLVED.EDGES);
    }

    private async load() {
        for (let c = 0; c < 8; ++c) {
            const path = CORNER_MODELS_URL.replace('#', c.toString());
            let obj: MeshObject = new MeshObject();
            obj.ModelTransform = corner_TG[c];
            await obj.readObj(path);
            this.corners.push(obj);
        }

        for (let i = 0; i < 12; ++i) {
            const path = EDGE_MODELS_URL.replace('#', i.toString());
            let obj: MeshObject = new MeshObject();
            obj.ModelTransform = edge_TG[i];
            await obj.readObj(path);
            this.edges.push(obj);
        }

        for (let i = 0; i < 6; ++i) {
            const path = CENTER_MODELS_URL.replace('#', i.toString());
            let obj: MeshObject = new MeshObject();
            obj.ModelTransform = center_TG[i];
            await obj.readObj(path);
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
                // Orient the corner:
                this.edges[piece].ModelTransform.rotate(
                    -orientation*180, -1,1,-1
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