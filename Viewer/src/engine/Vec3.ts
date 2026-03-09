export class Vec3 {
    x : number;
    y : number;
    z : number;
    
    constructor(_x: number, _y: number, _z: number) {
        this.x = _x;
        this.y = _y;
        this.z = _z;
    }

    /**
     * Adds v1 and v2 and returns the resulting Vec3 
     */
    static add(v1: Vec3, v2: Vec3) {

        return new Vec3(    v1.x + v2.x,
                            v1.y + v2.y,
                            v1.z + v2.z);
    }

    /**
     * Subtracts v1 and v2 and returns the resulting Vec3 
     */
    static sub(v1: Vec3, v2: Vec3) {
        
        return new Vec3(    v1.x - v2.x,
                            v1.y - v2.y,
                            v1.z - v2.z);
    }

    /**
     * Returns a copy of "this" scaled by the specified scalar.
     */
    scale(s: number) {
        
        return new Vec3(    s*this.x,
                            s*this.y,
                            s*this.z);
    }

    static max(v1: Vec3, v2: Vec3) : Vec3 {
        return new Vec3(
            Math.max(v1.x, v2.x),
            Math.max(v1.y, v2.y),
            Math.max(v1.z, v2.z),
        );
    }

    static min(v1: Vec3, v2: Vec3) : Vec3 {
        return new Vec3(
            Math.min(v1.x, v2.x),
            Math.min(v1.y, v2.y),
            Math.min(v1.z, v2.z),
        );
    }
}