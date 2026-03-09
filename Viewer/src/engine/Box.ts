import {Vec3} from './Vec3.ts';

export class Box {
    min : Vec3;
    max : Vec3;

    constructor(v_min: Vec3, v_max: Vec3) {
        this.min = v_min;
        this.max = v_max;
    }

    center() : Vec3{
        return Vec3.add(this.min, this.max).scale(0.5);
    }

    baseCenter() : Vec3 {
        return new Vec3(
            (this.min.x+this.max.x)/2.0,
            (this.min.y),
            (this.min.z+this.max.z)/2.0);
    }

    height() : number {
        return this.max.y - this.min.y;
    }

    expand(p : Vec3) {
        this.max = Vec3.max(this.max, p);
        this.min = Vec3.min(this.min, p);
    }
}