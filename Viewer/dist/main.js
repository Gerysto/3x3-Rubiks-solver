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
import { ShaderProgram } from "./shaders/ShaderProgram.js";
import { MouseController } from "./input/MouseController.js";
import { RubiksCube } from "./rubikscube/rubiks_cube.js";
import { RubiksAnimator } from "./rubikscube/rubiks_animator.js";
import { init_listeners } from "./input/eventListeners.js";
import createModule from "../libs/cube_lib.js";
const vertex_url = 'src/shaders/phong.vert';
const fragment_url = 'src/shaders/phong.frag';
function start() {
    return __awaiter(this, void 0, void 0, function* () {
        const canvas = document.getElementById("c");
        const gl = canvas.getContext("webgl2");
        const program = new ShaderProgram();
        yield program.load_shaders(gl, vertex_url, fragment_url);
        program.use(gl);
        const scene = new Scene();
        const camera = new Camera();
        let cube = new RubiksCube();
        yield cube.createVAOs(gl, program);
        cube.add_to_scene(scene);
        const renderer = new Renderer(gl, canvas, program);
        new MouseController(camera, canvas);
        let module = yield createModule();
        let ctrl = new module.CubeController();
        const animator = new RubiksAnimator(cube, ctrl);
        console.log("Initializing listeners!!");
        init_listeners(animator);
        console.log("Starting renderer!!");
        start_rendering(renderer, scene, camera, animator);
    });
}
function start_rendering(renderer, scene, camera, animator) {
    let prev_time = 0;
    const loop = (time) => {
        const dt = time - prev_time;
        prev_time = time;
        animator.update(dt / 1000);
        renderer.render(scene, camera);
        requestAnimationFrame(loop);
    };
    requestAnimationFrame(loop);
}
start();
