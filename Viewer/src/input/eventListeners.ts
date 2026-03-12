import { RubiksAnimator } from "../rubikscube/rubiks_animator";

export function init_listeners(animator: RubiksAnimator): void{
    const send_button  = document.getElementById("send_scramble") as HTMLButtonElement;
    const solve_button = document.getElementById("solve") as HTMLButtonElement;
    
    send_button.addEventListener('click', () => {
        const scramble_field = document.getElementById("scramble_field") as HTMLInputElement;
        let alg = scramble_field.value as string;
        animator.enqueue_algorithm(alg);
    })

    solve_button.addEventListener('click', () => {
        const s = animator.cube_ctrl.find_solution();
        animator.enqueue_algorithm(s);
    });

    async function init_solver() {
        animator.cube_ctrl.init_solver();
        console.log("Finished initializing solver!");
    }

    init_solver();
}