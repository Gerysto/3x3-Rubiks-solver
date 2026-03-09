var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
import { Camera } from "./engine/Camera.js";
import { Renderer } from "./engine/Renderer.js";
import { Scene } from "./engine/Scene.js";
import { Object } from "./engine/Object.js";
import { ShaderProgram } from "./shaders/ShaderProgram.js";
const vertex_url = 'src/shaders/phong.vertex';
const fragment_url = 'src/shaders/phong.vertex';
function start() {
    return __awaiter(this, void 0, void 0, function* () {
        const canvas = document.getElementById("c");
        const gl = canvas.getContext("webgl2");
        const program = new ShaderProgram(gl, vertex_url, fragment_url);
        const renderer = new Renderer(gl, canvas, program);
        const scene = new Scene();
        const camera = new Camera();
        // Example: Loading just one model!
        const object = new Object();
        object.readObj("assets/models/corners/c0.obj");
        object.createVAO(gl, program);
        scene.addObject(object);
        renderer.start(scene, camera);
    });
}
start();
