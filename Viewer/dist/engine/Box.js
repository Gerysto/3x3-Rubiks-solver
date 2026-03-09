import { Vec3 } from './Vec3.js';
export class Box {
    constructor(v_min, v_max) {
        this.min = v_min;
        this.max = v_max;
    }
    center() {
        return Vec3.add(this.min, this.max).scale(0.5);
    }
    baseCenter() {
        return new Vec3((this.min.x + this.max.x) / 2.0, (this.min.y), (this.min.z + this.max.z) / 2.0);
    }
    height() {
        return this.max.y - this.min.y;
    }
    expand(p) {
        this.max = Vec3.max(this.max, p);
        this.min = Vec3.min(this.min, p);
    }
}
