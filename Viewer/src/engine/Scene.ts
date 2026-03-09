import {Camera} from './Camera.js';
import {Vec3} from './Vec3.js';
import {Box} from './Box.js';
import {Object} from './Object.js';
//import {J3DIMatrix4, J3DIVector3} from '../../libs/J3DIMath.js'


export class Scene {

    objects : Object[];
    camera : Camera;
    boundingBox : Box;

    constructor() {
        this.objects = [];
        this.camera = new Camera();
        this.boundingBox = new Box(
            new Vec3( 1e100,  1e100,  1e100), // Min
            new Vec3(-1e100, -1e100, -1e100)  // Max
        );
    }

    addObject(obj: Object) {
        this.objects.push(obj);
        this.expandSceneBoundingBox(obj);
    }

    recomputeBoundingBox() {
        this.boundingBox = new Box(
            new Vec3( 1e100,  1e100,  1e100), // Min
            new Vec3(-1e100, -1e100, -1e100)  // Max
        );

        for (let obj of this.objects) {
            this.expandSceneBoundingBox(obj);
        }
    }

    private expandSceneBoundingBox(obj: Object) {
        const max = obj.boundingBox.max;
        const min = obj.boundingBox.min;

        let p_max = new J3DIVector3(max.x, max.y, max.z);
        let p_min = new J3DIVector3(min.x, min.y, min.z);

        const TG : J3DIMatrix4 = obj.ModelTransform;
        // Convert min and max to World Space:
        p_max.multVecMatrix(TG);
        p_min.multVecMatrix(TG);

        
        this.boundingBox.expand(Vec3.fromArray
            (p_max.getAsArray()));
        this.boundingBox.expand(Vec3.fromArray
            (p_min.getAsArray()));
    }
}