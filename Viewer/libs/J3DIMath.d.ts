declare class J3DIMatrix4 {
    constructor(m?: any);
    load(m: any): void;
    getAsArray(): number[];
    getAsFloat32Array(): Float32Array;
    setUniform(ctx: WebGL2RenderingContext, loc: any, transpose: any): void;
    makeIdentity(): void;
    transpose(): void;
    invert(): void;
    translate(x: number, y: number, z: number): void;
    scale(x: number, y: number, z: number): void;
    rotate(angle: number, x: number, y: number, z: number): void;
    multiply(m: J3DIMatrix4): void;
    divide(m: J3DIMatrix4): void;
    ortho(left:number, right:number, bottom:number, top:number, near:number, far:number): void;
    frustrum(left:number, right:number, bottom:number, top:number, near:number, far:number): void;
    perspective(fovy: number, aspect: number, zNear: number, zFar: number): void;
    lookat(eyex:number, eyey:number, eyez:number, centerx:number, centery:number, centerz:number, upx:number, upy:number, upz:number): void;
}

declare class J3DIVector3 {
    constructor(x?: number, y?: number, z?: number);
    load(x: number, y: number, z: number): void;
    getAsArray() : number[];
    getAsFloat32Array() : Float32Array;
    vectorLength(): number;
    divide(divisor: number) : void;
    cross(v: J3DIVector3): void;
    dot(v: J3DIVector3): number;
    multVecMatrix(matrix: J3DIMatrix4) : void;
}