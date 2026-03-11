var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
import createModule from '../../libs/cube_lib.js';
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
    vectorToArray(v) {
        let res = [];
        for (let i = 0; i < v.size(); ++i) {
            res.push(v.get(i));
        }
        return res;
    }
    start(scene, camera, rubiks_cube) {
        return __awaiter(this, void 0, void 0, function* () {
            let t = 0.0;
            let module = yield createModule();
            let ctrl = new module.CubeController();
            ctrl.execute_sequence_in_notation("R U R' U'");
            const corner_state = this.vectorToArray(ctrl.get_state_corners());
            const edge_state = this.vectorToArray(ctrl.get_state_edges());
            rubiks_cube.update_state(corner_state, edge_state);
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
                //rubiks_cube.perform_move("R", true, t);
                t += 0.02;
                //if (t > 1) t -= 1;
                requestAnimationFrame(loop);
            };
            loop();
        });
    }
    drawObject(obj, camera) {
        const gl = this.gl;
        const ra = this.aspect_ratio;
        const VM = camera.getViewMatrix(); // View matrix
        const TG = obj.ModelTransform; // Model matrix
        const NM = this.normalMatrix(VM, TG); // Normal matrix
        const PM = camera.getProjectionMatrix(ra); // Projection matrix
        /*console.log("Des de renderer: ", this.program.VMLoc);
        console.log("Des de renderer: ", this.program.TGLoc);
        console.log("Des de renderer: ", this.program.NMLoc);
        console.log("Des de renderer: ", this.program.PMLoc);*/
        VM.setUniform(gl, this.program.VMLoc, false);
        TG.setUniform(gl, this.program.TGLoc, false);
        NM.setUniform(gl, this.program.NMLoc, false);
        PM.setUniform(gl, this.program.PMLoc, false);
        gl.bindVertexArray(obj.vao);
        gl.drawArrays(gl.TRIANGLES, 0, obj.faces.length * 3);
        gl.bindVertexArray(null);
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
