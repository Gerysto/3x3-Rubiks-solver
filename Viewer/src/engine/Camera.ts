import {J3DIMatrix4} from "../../libs/J3DIMath.js";

export class Camera {
    
    angleX: number;
    angleY: number;
    angleZ: number;

    distance: number;

    fov: number;
    zNear: number;
    zFar: number;

    constructor() {
        this.angleX = 0;
        this.angleY = 0;
        this.angleZ = 0;

        this.distance = 20;

        this.fov = 30;
        this.zNear = 1;
        this.zFar = 40;
    }

    /**
     * Calculates the view matrix (using Euler angles) and returns it.
     * @returns J3DIMatrix VM (View Matrix)
     */
    getViewMatrix() {
        const VM = new J3DIMatrix4();
       
        // Euler angles:
        
        VM.translate(0,0,-this.distance);
        VM.rotate(-this.angleZ, 0,0,1);
        VM.rotate( this.angleX, 1,0,0);
        VM.rotate(-this.angleY, 0,1,0);
        /* this.VM.translate(0,0,0); <--- to change VRP */

        return VM;
    }

    /**
     * Calculates the projection matrix and returns it.
     * @returns J3DIMatrix PM (Projection Matrix)
     */
    getProjectionMatrix(aspectRatio: number) : J3DIMatrix4 {
        const PM = new J3DIMatrix4();
        
        PM.perspective(this.fov, aspectRatio, this.zNear, this.zFar);
        return PM;
    }
}