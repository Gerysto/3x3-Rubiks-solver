import { RubiksAnimator } from "./rubikscube/rubiks_animator";

export function init_listeners(animator: RubiksAnimator): void{
    const send_button = document.getElementById("send_scramble") as HTMLButtonElement;
    
    send_button.addEventListener('click', () => {
        const scramble_field = document.getElementById("scramble_field") as HTMLInputElement;
        let alg = scramble_field.value as string;
        animator.enqueue_algorithm(alg);
    })
}