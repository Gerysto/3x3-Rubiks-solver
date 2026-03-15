import { Camera } from "../engine/Camera";
import { RubiksAnimator } from "../rubikscube/rubiks_animator";

export function init_listeners(animator: RubiksAnimator,
                               camera: Camera): void{
    const send_button  = document.getElementById("send_scramble") as HTMLButtonElement;
    const solve_button = document.getElementById("solve") as HTMLButtonElement;
    const turn_speed = document.getElementById("turn_speed") as HTMLInputElement;
    const turn_speed_label = document.getElementById("turn_speed_label") as HTMLLabelElement;
    const default_orientation = document.getElementById("default_orientation") as HTMLButtonElement;
    const random_scramble = document.getElementById("random_scramble") as HTMLButtonElement;

    const scramble_field = document.getElementById("scramble_field") as HTMLInputElement;

    send_button.addEventListener('click', () => {    
        let alg = scramble_field.value as string;
        animator.enqueue_algorithm(alg);
    })

    solve_button.addEventListener('click', () => {
        const s = animator.cube_ctrl.find_solution();
        animator.enqueue_algorithm(s);
    });

    turn_speed.addEventListener('input', () => {
        const tps: number = parseFloat(turn_speed.value);
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
    });

    async function init_solver() {
        animator.cube_ctrl.init_solver();
        console.log("Finished initializing solver!");
    }


    init_solver();// <--- UN COMMENT! (this really slows down the page!)
}