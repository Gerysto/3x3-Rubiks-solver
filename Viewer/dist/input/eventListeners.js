var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
export function init_listeners(animator, camera) {
    const send_button = document.getElementById("send_scramble");
    const solve_button = document.getElementById("solve");
    const turn_speed = document.getElementById("turn_speed");
    const default_orientation = document.getElementById("default_orientation");
    const random_scramble = document.getElementById("random_scramble");
    const scramble_field = document.getElementById("scramble_field");
    send_button.addEventListener('click', () => {
        let alg = scramble_field.value;
        animator.enqueue_algorithm(alg);
    });
    solve_button.addEventListener('click', () => {
        const s = animator.cube_ctrl.find_solution();
        animator.enqueue_algorithm(s);
    });
    turn_speed.addEventListener('input', () => {
        const tps = parseFloat(turn_speed.value);
        animator.TPS = tps;
    });
    default_orientation.addEventListener('click', () => {
        camera.angleX = 45;
        camera.angleY = 0;
        camera.angleZ = 0;
    });
    random_scramble.addEventListener('click', () => {
        let s = animator.cube_ctrl.generate_random_scramble(30);
        scramble_field.value = s;
        console.log(s);
    });
    function init_solver() {
        return __awaiter(this, void 0, void 0, function* () {
            animator.cube_ctrl.init_solver();
            console.log("Finished initializing solver!");
        });
    }
    init_solver(); // <--- UN COMMENT! (this really slows down the page!)
}
