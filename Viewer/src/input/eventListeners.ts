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

    scramble_field.classList.add('valid');
    
    function check_input_scramble() {
        let is_correct: boolean = animator.cube_ctrl.is_scramble_correct(scramble_field.value);
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
        let alg = scramble_field.value as string;
        animator.enqueue_algorithm(alg);
    })


    solve_button.addEventListener('click', async () => {
        const cog_image = document.getElementById('cog-img') as HTMLImageElement;
        cog_image.classList.add("animated");
        solve_button.disabled = true;


        const solver_worker = new Worker(
            "src/workers/SolverWorker.js", {type: 'module'});

        console.log("STARTS WAITING....");
        await new Promise(r => setTimeout(r, 5000));
        console.log("STOPS WAITING!");

        // Obtain the state:
        const state = {corners: animator.cube.state.corners,
                       edges: animator.cube.state.edges}
        
        solver_worker.postMessage(state);
        console.log("MESSAGE SENT TO WORKER!!");
        
        solver_worker.onmessage = (e) => {
            console.log("Response recieved!!!");
            let sequence: string = e.data;
            animator.enqueue_algorithm(sequence);

            solve_button.disabled = false;
            cog_image.classList.remove("animated");
        };

        /*
        const s = animator.cube_ctrl.find_solution();
        animator.enqueue_algorithm(s);*/

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
        check_input_scramble();
    });
}