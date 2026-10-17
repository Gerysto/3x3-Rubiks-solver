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
    return __awaiter(this, void 0, void 0, function* () {
        const send_button = document.getElementById("send_scramble");
        const solve_button = document.getElementById("solve");
        const turn_speed = document.getElementById("turn_speed");
        const turn_speed_label = document.getElementById("turn_speed_label");
        const default_orientation = document.getElementById("default_orientation");
        const random_scramble = document.getElementById("random_scramble");
        const scramble_field = document.getElementById("scramble_field");
        scramble_field.classList.add('valid');
        function check_input_scramble() {
            let is_correct = animator.cube_ctrl.is_scramble_correct(scramble_field.value);
            console.log("Is correct? ", is_correct);
            if (!is_correct) {
                send_button.disabled = true;
                scramble_field.classList.replace('valid', 'invalid');
            }
            else {
                scramble_field.classList.replace('invalid', 'valid');
                send_button.disabled = false;
            }
        }
        check_input_scramble();
        turn_speed.value = animator.TPS.toString();
        turn_speed_label.innerHTML = animator.TPS.toString() + " TPS";
        scramble_field.addEventListener('input', () => check_input_scramble());
        send_button.addEventListener('click', () => {
            let alg = scramble_field.value;
            animator.enqueue_algorithm(alg);
        });
        // Create worker:
        const solver_worker = new Worker("src/workers/SolverWorker.js", { type: 'module' });
        // Wait for worker to initialize:
        yield new Promise((resolve) => {
            solver_worker.onmessage = (e) => {
                if (e.data == 'READY')
                    resolve("You shall pass!");
            };
        });
        solve_button.addEventListener('click', () => {
            const cog_image = document.getElementById('cog-img');
            cog_image.classList.add("animated");
            solve_button.disabled = true;
            send_button.disabled = true;
            // Obtain the state:
            const state = { corners: animator.cube.state.corners,
                edges: animator.cube.state.edges,
                orientation: animator.cube.state.orientation };
            solver_worker.postMessage(state);
            console.log("MESSAGE SENT TO WORKER!!");
            solver_worker.onmessage = (e) => {
                console.log("Response recieved!!!");
                let sequence = e.data;
                animator.enqueue_algorithm(sequence);
                solve_button.disabled = false;
                send_button.disabled = false;
                cog_image.classList.remove("animated");
            };
        });
        turn_speed.addEventListener('input', () => {
            const tps = parseFloat(turn_speed.value);
            turn_speed_label.innerHTML = turn_speed.value + " TPS";
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
            check_input_scramble();
        });
    });
}
