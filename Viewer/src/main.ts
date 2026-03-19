import { Camera } from "./engine/Camera.js";
import { Renderer } from "./engine/Renderer.js";
import { Scene } from "./engine/Scene.js";
import { ShaderProgram } from "./shaders/ShaderProgram.js";
import { MouseController } from "./input/MouseController.js";
import { RubiksCube, State } from "./rubikscube/rubiks_cube.js";
import { RubiksAnimator } from "./rubikscube/rubiks_animator.js";
import { init_listeners } from "./input/eventListeners.js";

import createModule from "../libs/cube_lib.js";

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
    
    let module = await createModule();
    let ctrl = new module.CubeController();
    ctrl.init_solver();

    const animator: RubiksAnimator = new RubiksAnimator(cube, ctrl);

    console.log("Initializing listeners!!");
    init_listeners(animator, camera);    
    
    console.log("Starting renderer!!");

    const loader = document.getElementById("loader") as HTMLDivElement;
    loader.style.display = "none";
    loader.hidden = true;
    canvas.style.display = "block";
    start_rendering(renderer, scene, camera, animator);
}

function start_rendering(renderer: Renderer, scene: Scene, camera: Camera, animator: RubiksAnimator) {
    let prev_time = 0;
    const loop = (time: number) => {
        const dt = time - prev_time;
        prev_time = time;
        
        animator.update(dt/1000);

        renderer.render(scene, camera);
        requestAnimationFrame(loop);
    }

    requestAnimationFrame(loop);
}

start();