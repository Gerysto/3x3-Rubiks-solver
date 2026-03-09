import {Scene} from './Scene.js';
import {Camera} from './Camera.js';
import {Object} from './Object.js';
import {ShaderProgram} from '../shaders/ShaderProgram.js'
import { J3DIMatrix4 } from '../../libs/J3DIMath.js';

export class Renderer {

    gl: WebGL2RenderingContext;
    aspect_ratio: number;

    constructor(canvas) {
        this.gl = canvas.getContext("webgl2");
        const width = canvas.clientWidth;
        const height = canvas.clientHeight;

        this.aspect_ratio = width/height;

        if(!this.gl) {
            throw new Error("Failed to start WebGL!");
        }

        this.gl.viewport(0,0, width, height);
        this.gl.enable(this.gl.DEPTH_TEST);
        this.gl.clearColor(0.8,0.8,0.8,1);
    }

    start(scene: Scene, camera: Camera, program: ShaderProgram) {
        const loop = () => {
            this.gl.clear(
                this.gl.COLOR_BUFFER_BIT |
                this.gl.DEPTH_BUFFER_BIT
            );

            for (const obj of scene.objects) {
                this.drawObject(obj, camera, program);
            }
        }

        loop();
    }

    drawObject(obj: Object, camera: Camera, program: ShaderProgram) {
        const gl = this.gl;
        const ra = this.aspect_ratio;

        const VM = camera.getViewMatrix();          // View matrix
        const TG = obj.ModelTransform;              // Model matrix
        const NM = this.normalMatrix(VM, TG);       // Normal matrix
        const PM = camera.getProjectionMatrix(ra);  // Projection matrix
        
        VM.setUniform(gl, program.VMLoc, false);
        TG.setUniform(gl, program.TGLoc, false);
        NM.setUniform(gl, program.NMLoc, false);
        PM.setUniform(gl, program.PMLoc, false);

        gl.bindVertexArray(obj.vao);
        gl.drawArrays(gl.TRIANGLES, 0, obj.vertices.length / 3);
    }

    private normalMatrix(VM: J3DIMatrix4, TG: J3DIMatrix4) : J3DIMatrix4 {
        const NM = new J3DIMatrix4();
        NM.load(VM);
        NM.multiply(TG);
        NM.invert();
        NM.transpose();
        return NM;
    }
}