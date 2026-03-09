import { Camera } from "./engine/Camera";
import { Renderer } from "./engine/Renderer";
import { Scene } from "./engine/Scene";
import { Object } from "./engine/Object";
import { ShaderProgram } from "./shaders/ShaderProgram";

const vertex_url = 'src/shaders/phong.vertex';
const fragment_url = 'src/shaders/phong.vertex';

async function start() {
    const canvas : any = document.getElementById("c");
    const gl = canvas.getContext("webgl2");

    const program = new ShaderProgram(this.gl, vertex_url, fragment_url);
    const renderer = new Renderer(canvas, program);

    const scene = new Scene();
    const camera = new Camera();
    
    // Example: Loading just one model!
    const object = new Object();

    object.readObj("assets/models/corners/c0.obj");
    object.createVAO(gl, program);

    scene.addObject(object);

    renderer.start(scene, camera);
}