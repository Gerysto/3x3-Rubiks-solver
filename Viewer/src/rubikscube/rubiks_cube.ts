import {Object} from '../engine/Object.js';

const CORNER_MODELS_URL = 'Viewer/assets/models/corners/c#.obj';
const EDGE_MODELS_URL = 'Viewer/assets/models/edges/e#.obj';
const CENTER_MODELS_URL = 'Viewer/assets/models/centers/f#.obj';

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
            let corner: Object = new Object();
            corner.readObj(path);
        }

        for (let e = 0; e < 12; ++e) {
            const path = CORNER_MODELS_URL.replace('#', e.toString());
            let edge: Object = new Object();
            edge.readObj(path);
        }

        for (let f = 0; f < 6; ++f) {
            const path = CORNER_MODELS_URL.replace('#', f.toString());
            let center: Object = new Object();
            center.readObj(path);
        }
    }
}