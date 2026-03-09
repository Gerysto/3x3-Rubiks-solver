import {Scene} from './Scene.js';
import {Camera} from './Camera.js';
import {Object} from './Object.js';
import {ShaderProgram} from '../shaders/ShaderProgram.js'
//import { J3DIMatrix4 } from '../../libs/J3DIMath.js';

export class Renderer {

    gl: WebGL2RenderingContext;
    aspect_ratio: number;
    program : ShaderProgram;

    constructor(gl: WebGL2RenderingContext, canvas: HTMLCanvasElement, program: ShaderProgram) {
        this.gl = gl;

        const width = canvas.clientWidth;
        const height = canvas.clientHeight;
        this.program = program;
        this.aspect_ratio = width/height;

        if(!this.gl) {
            throw new Error("Failed to start WebGL!");
        }

        this.gl.viewport(0,0, canvas.width, canvas.height);
        this.gl.enable(this.gl.DEPTH_TEST);
        this.gl.clearColor(0.8,0.8,0.8,1);
    }

    start(scene: Scene, camera: Camera) {
        const loop = () => {
            this.gl.clear(
                this.gl.COLOR_BUFFER_BIT |
                this.gl.DEPTH_BUFFER_BIT
            );
            if (Renderer.resizeCanvasToDisplaySize(this.gl)) {
                // Re-calculate projection view / projection matrices!
            };
            
            for (const obj of scene.objects) {
                //console.log("Inside start function", obj);
                this.drawObject(obj, camera);
            }
            requestAnimationFrame(loop);
        }

        loop();
    }

    drawObject(obj: Object, camera: Camera) {
        const gl = this.gl;
        const ra = this.aspect_ratio;

        const VM = camera.getViewMatrix();          // View matrix
        const TG = obj.ModelTransform;              // Model matrix
        const NM = this.normalMatrix(VM, TG);       // Normal matrix
        const PM = camera.getProjectionMatrix(ra);  // Projection matrix
        
        const F: GLboolean = false;


        /*console.log("Des de renderer: ", this.program.VMLoc);
        console.log("Des de renderer: ", this.program.TGLoc);
        console.log("Des de renderer: ", this.program.NMLoc);
        console.log("Des de renderer: ", this.program.PMLoc);*/

        VM.setUniform(gl, this.program.VMLoc, F);
        TG.setUniform(gl, this.program.TGLoc, F);
        NM.setUniform(gl, this.program.NMLoc, F);
        PM.setUniform(gl, this.program.PMLoc, F);


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


    private static resizeCanvasToDisplaySize(gl:WebGL2RenderingContext) : boolean {
        const canvas : HTMLCanvasElement = gl.canvas as HTMLCanvasElement;
        const dpr = window.devicePixelRatio || 1;
        const displayWidth = Math.floor(canvas.clientWidth * dpr);
        const displayHeight = Math.floor(canvas.clientHeight * dpr);

        if (canvas.width !== displayWidth || canvas.height !== displayHeight) {
            canvas.width = displayWidth;
            canvas.height = displayHeight;
            gl.viewport(0,0, canvas.width, canvas.height);
            return true;
        }
        return false;
    }
}