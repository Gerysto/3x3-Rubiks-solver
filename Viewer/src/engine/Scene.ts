import {Camera} from './Camera.ts';
import {Box} from './Box.ts';
import {Object} from './Object.ts';


export class Scene {

    objects : Object[];
    camera : Camera;
    boundingBox : Box;

    constructor() {
        this.camera = new Camera();
    }
}