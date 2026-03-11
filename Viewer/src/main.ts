import { Camera } from "./engine/Camera.js";
import { Renderer } from "./engine/Renderer.js";
import { Scene } from "./engine/Scene.js";
import { MeshObject } from "./engine/MeshObject.js";
import { ShaderProgram } from "./shaders/ShaderProgram.js";
import { MouseController } from "./input/MouseController.js";
import { RubiksCube } from "./rubikscube/rubiks_cube.js";

const vertex_url = 'src/shaders/phong.vert';
const fragment_url = 'src/shaders/phong.frag';

async function start() {
    const canvas = document.getElementById("c") as HTMLCanvasElement;
    const gl = canvas.getContext("webgl2") as WebGL2RenderingContext;

    const program = new ShaderProgram();
    await program.load_shaders(gl, vertex_url, fragment_url);
    program.use(gl);

    const scene = new Scene();
    const camera = new Camera();

    let cube: RubiksCube = new RubiksCube();
    await cube.createVAOs(gl, program);
    cube.add_to_scene(scene);

    const renderer = new Renderer(gl, canvas, program);

    new MouseController(camera, canvas);
    

    console.log("Starting renderer!!");
    renderer.start(scene, camera, cube);
}


start();