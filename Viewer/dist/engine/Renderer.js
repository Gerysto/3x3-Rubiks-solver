//import { J3DIMatrix4 } from '../../libs/J3DIMath.js';
export class Renderer {
    constructor(gl, canvas, program) {
        this.gl = gl;
        const width = canvas.clientWidth;
        const height = canvas.clientHeight;
        this.program = program;
        this.aspect_ratio = width / height;
        if (!this.gl) {
            throw new Error("Failed to start WebGL!");
        }
        this.gl.viewport(0, 0, canvas.width, canvas.height);
        this.gl.enable(this.gl.DEPTH_TEST);
        this.gl.clearColor(0.8, 0.8, 0.8, 1);
    }
    start(scene, camera) {
        const loop = () => {
            this.gl.clear(this.gl.COLOR_BUFFER_BIT |
                this.gl.DEPTH_BUFFER_BIT);
            if (Renderer.resizeCanvasToDisplaySize(this.gl)) {
                // Re-calculate projection view / projection matrices!
            }
            ;
            for (const obj of scene.objects) {
                //console.log("Inside start function", obj);
                this.drawObject(obj, camera);
            }
            requestAnimationFrame(loop);
        };
        loop();
    }
    drawObject(obj, camera) {
        const gl = this.gl;
        const ra = this.aspect_ratio;
        const VM = camera.getViewMatrix(); // View matrix
        const TG = obj.ModelTransform; // Model matrix
        const NM = this.normalMatrix(VM, TG); // Normal matrix
        const PM = camera.getProjectionMatrix(ra); // Projection matrix
        const F = false;
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
    normalMatrix(VM, TG) {
        const NM = new J3DIMatrix4();
        NM.load(VM);
        NM.multiply(TG);
        NM.invert();
        NM.transpose();
        return NM;
    }
    static resizeCanvasToDisplaySize(gl) {
        const canvas = gl.canvas;
        const dpr = window.devicePixelRatio || 1;
        const displayWidth = Math.floor(canvas.clientWidth * dpr);
        const displayHeight = Math.floor(canvas.clientHeight * dpr);
        if (canvas.width !== displayWidth || canvas.height !== displayHeight) {
            canvas.width = displayWidth;
            canvas.height = displayHeight;
            gl.viewport(0, 0, canvas.width, canvas.height);
            return true;
        }
        return false;
    }
}
