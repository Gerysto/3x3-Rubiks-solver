import { Camera } from "./engine/Camera.js";
import { Renderer } from "./engine/Renderer.js";
import { Scene } from "./engine/Scene.js";
import { Object } from "./engine/Object.js";
import { ShaderProgram } from "./shaders/ShaderProgram.js";

const vertex_url = 'src/shaders/phong.vertex';
const fragment_url = 'src/shaders/phong.vertex';

async function start() {
    const canvas = document.getElementById("c") as HTMLCanvasElement;
    const gl = canvas.getContext("webgl2") as WebGL2RenderingContext;

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
}

start();