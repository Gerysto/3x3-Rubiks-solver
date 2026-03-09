import {Camera} from './Camera.ts';
import {Vec3} from './Vec3.ts';
import {Box} from './Box.ts';
import {Object} from './Object.ts';
import {J3DIMatrix4, J3DIVector3} from '../../libs/J3DIMath.js'


export class Scene {

    objects : Object[];
    camera : Camera;
    boundingBox : Box;

    constructor() {
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

        // Convert min and max to World Space:
        p_max.multVecMatrix(obj.ModelTransform);
        p_min.multVecMatrix(obj.ModelTransform);

        
        this.boundingBox.expand(Vec3.fromArray
            (p_max.getAsArray()));
        this.boundingBox.expand(Vec3.fromArray
            (p_min.getAsArray()));
    }
}