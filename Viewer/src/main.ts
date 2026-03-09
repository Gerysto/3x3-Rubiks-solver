import { Camera } from "./engine/Camera.js";
import { Renderer } from "./engine/Renderer.js";
import { Scene } from "./engine/Scene.js";
import { Object } from "./engine/Object.js";
import { ShaderProgram } from "./shaders/ShaderProgram.js";
import { MouseController } from "./input/MouseController.js";

const vertex_url = 'src/shaders/phong.vert';
const fragment_url = 'src/shaders/phong.frag';

async function start() {
    const canvas = document.getElementById("c") as HTMLCanvasElement;
    const gl = canvas.getContext("webgl2") as WebGL2RenderingContext;

    const program = new ShaderProgram();
    await program.load_shaders(gl, vertex_url, fragment_url);
    const renderer = new Renderer(gl, canvas, program);

    const scene = new Scene();
    const camera = new Camera();
    
    new MouseController(camera, canvas);
    
    // Example: Loading just one model!
    const object = new Object();

    await object.readObj("assets/models/corners/c0.obj");
    object.createVAO(gl, program);

    scene.addObject(object);

    console.log("Starting renderer!!");
    renderer.start(scene, camera);
}


start();