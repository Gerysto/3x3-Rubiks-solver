import {Object} from '../engine/Object.js';
import { Scene } from '../engine/Scene.js';
import { ShaderProgram } from '../shaders/ShaderProgram.js';
import { corner_TG, edge_TG, center_TG } from './piece_transformations.js';
import { PIECES_INVOLVED } from './rubiks_constants.js';

const CORNER_MODELS_URL = 'assets/models/corners/c#.obj';
const EDGE_MODELS_URL   = 'assets/models/edges/e#.obj';
const CENTER_MODELS_URL = 'assets/models/centers/f#.obj';

export class RubiksCube {

    corners: Object[];
    edges: Object[];
    centers: Object[];

    constructor() {
        this.corners = [];
        this.edges = [];
        this.centers = [];

        for (let c = 0; c < 8; ++c) {
            const path = CORNER_MODELS_URL.replace('#', c.toString());
            let obj: Object = new Object();
            obj.ModelTransform = corner_TG[c];
            obj.readObj(path);
            this.corners.push(obj);
        }

        for (let i = 0; i < 12; ++i) {
            const path = EDGE_MODELS_URL.replace('#', i.toString());
            let obj: Object = new Object();
            obj.ModelTransform = edge_TG[i];
            obj.readObj(path);
            this.edges.push(obj);
        }

        for (let i = 0; i < 6; ++i) {
            const path = CENTER_MODELS_URL.replace('#', i.toString());
            let obj: Object = new Object();
            obj.ModelTransform = center_TG[i];
            obj.readObj(path);
            this.centers.push(obj);
        }
    }

    createVAOs(gl: WebGL2RenderingContext, program: ShaderProgram) {
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

        // Corners
        for (let i of pieces_involved[0]) {
            // Divide index by 3 to conver from 'stiker index' to 'piece index'

            this.corners[i/3].ModelTransform = new J3DIMatrix4();
            this.corners[i/3].ModelTransform.rotate(90*t, 1, 0, 0);
            this.corners[i/3].ModelTransform.multiply(corner_TG[i]);
        }

        // Edges: 
        for (let i of pieces_involved[1])   {
            // Divide index by 2 to conver from 'stiker index' to 'piece index'
            this.edges[i/2].ModelTransform = new J3DIMatrix4();
            this.edges[i/2].ModelTransform.rotate(90*t, 1, 0, 0);
            this.edges[i/2].ModelTransform.multiply(edge_TG[i]);
        }

        // Centers: 
        for (let i of pieces_involved[2]) {
            this.centers[i].ModelTransform = new J3DIMatrix4();
            this.centers[i].ModelTransform.rotate(90*t, 1, 0, 0);
            this.centers[i].ModelTransform.multiply(center_TG[i]);
        }
    }
}