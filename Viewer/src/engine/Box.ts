import {Vec3} from './Vec3.ts';

export class Box {
    min : Vec3;
    max : Vec3;

    constructor(v_min, v_max) {
        this.min = v_min;
        this.max = v_max;
    }
}