var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
import { MeshObject } from '../engine/MeshObject.js';
import { corner_TG, edge_TG, center_TG } from './piece_transformations.js';
import { PIECES_INVOLVED } from './rubiks_constants.js';
const CORNER_MODELS_URL = 'assets/models/corners/c#.obj';
const EDGE_MODELS_URL = 'assets/models/edges/e#.obj';
const CENTER_MODELS_URL = 'assets/models/centers/f#.obj';
export class RubiksCube {
    constructor() {
        this.corners = [];
        this.edges = [];
        this.centers = [];
    }
    load() {
        return __awaiter(this, void 0, void 0, function* () {
            for (let c = 0; c < 8; ++c) {
                const path = CORNER_MODELS_URL.replace('#', c.toString());
                let obj = new MeshObject();
                obj.ModelTransform = corner_TG[c];
                yield obj.readObj(path);
                this.corners.push(obj);
            }
            for (let i = 0; i < 12; ++i) {
                const path = EDGE_MODELS_URL.replace('#', i.toString());
                let obj = new MeshObject();
                obj.ModelTransform = edge_TG[i];
                yield obj.readObj(path);
                this.edges.push(obj);
            }
            for (let i = 0; i < 6; ++i) {
                const path = CENTER_MODELS_URL.replace('#', i.toString());
                let obj = new MeshObject();
                obj.ModelTransform = center_TG[i];
                yield obj.readObj(path);
                this.centers.push(obj);
            }
        });
    }
    createVAOs(gl, program) {
        return __awaiter(this, void 0, void 0, function* () {
            yield this.load();
            for (let obj of this.corners)
                obj.createVAO(gl, program);
            for (let obj of this.edges)
                obj.createVAO(gl, program);
            for (let obj of this.centers)
                obj.createVAO(gl, program);
        });
    }
    add_to_scene(scene) {
        for (let obj of this.corners)
            scene.addObject(obj);
        for (let obj of this.edges)
            scene.addObject(obj);
        for (let obj of this.centers)
            scene.addObject(obj);
    }
    /**
     * Partilly performs one of the moves: {U, R, F, D, L, B}, according to the interpolation value @param t provided
     * @param move one of the outer moves in cubing notation {U, R, F, D, L, B}
     * @param clockwhise whether the turn should be clockwhise {U}, or anticlockwhise {U'}
     * @param t interpolation parameter (ranging from 0 to 1)
     */
    perform_move(move, clockwhise, t) {
        const pieces_involved = PIECES_INVOLVED.get(move);
        let angle = 90 * t;
        if (clockwhise)
            angle *= -1;
        // Corners
        for (let i of pieces_involved[0]) {
            // Divide index by 3 to conver from 'stiker index' to 'piece index'
            const piece = Math.floor(i / 3);
            this.corners[piece].ModelTransform = new J3DIMatrix4();
            this.corners[piece].ModelTransform.rotate(angle, 1, 0, 0);
            this.corners[piece].ModelTransform.multiply(corner_TG[piece]);
        }
        // Edges: 
        for (let i of pieces_involved[1]) {
            // Divide index by 2 to conver from 'stiker index' to 'piece index'
            const piece = Math.floor(i / 2);
            this.edges[piece].ModelTransform = new J3DIMatrix4();
            this.edges[piece].ModelTransform.rotate(angle, 1, 0, 0);
            this.edges[piece].ModelTransform.multiply(edge_TG[piece]);
        }
        // Centers: 
        for (let i of pieces_involved[2]) {
            this.centers[i].ModelTransform = new J3DIMatrix4();
            this.centers[i].ModelTransform.rotate(angle, 1, 0, 0);
            this.centers[i].ModelTransform.multiply(center_TG[i]);
        }
    }
}
