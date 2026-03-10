import { Object } from '../engine/Object.js';
import { corner_TG, edge_TG, center_TG } from './piece_transformations.js';
const CORNER_MODELS_URL = 'assets/models/corners/c#.obj';
const EDGE_MODELS_URL = 'assets/models/edges/e#.obj';
const CENTER_MODELS_URL = 'assets/models/centers/f#.obj';
export class RubiksCube {
    constructor() {
        this.corners = [];
        this.edges = [];
        this.centers = [];
        for (let c = 0; c < 8; ++c) {
            const path = CORNER_MODELS_URL.replace('#', c.toString());
            let obj = new Object();
            obj.ModelTransform = corner_TG[c];
            obj.readObj(path);
            this.corners.push(obj);
        }
        for (let i = 0; i < 12; ++i) {
            const path = EDGE_MODELS_URL.replace('#', i.toString());
            let obj = new Object();
            obj.ModelTransform = edge_TG[i];
            obj.readObj(path);
            this.edges.push(obj);
        }
        for (let i = 0; i < 6; ++i) {
            const path = CENTER_MODELS_URL.replace('#', i.toString());
            let obj = new Object();
            obj.ModelTransform = center_TG[i];
            obj.readObj(path);
            this.centers.push(obj);
        }
    }
    createVAOs(gl, program) {
        for (let obj of this.corners)
            obj.createVAO(gl, program);
        for (let obj of this.edges)
            obj.createVAO(gl, program);
        for (let obj of this.centers)
            obj.createVAO(gl, program);
    }
    add_to_scene(scene) {
        for (let obj of this.corners)
            scene.addObject(obj);
        for (let obj of this.edges)
            scene.addObject(obj);
        for (let obj of this.centers)
            scene.addObject(obj);
    }
}
