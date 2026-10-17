import { vectorIntToArray } from '../../libs/wasm_utils.js';
import { State } from '../rubikscube/rubiks_cube.js';
export class RubiksAnimator {
    constructor(cube, ctrl) {
        this.TPS = 16; // Turns per second 
        this.cube = cube;
        this.progress = 0;
        this.queue = [];
        this.current_move = null;
        this.cube_ctrl = ctrl;
        this.TPS = 5;
    }
    enqueue(final_state, move, clockwhise) {
        this.queue.push([final_state, move, clockwhise]);
    }
    update(dt) {
        if (!this.current_move) {
            if (this.queue.length == 0)
                return;
            else {
                this.current_move = this.queue.shift();
            }
        }
        const [final_state, move, clockwhise] = this.current_move;
        this.progress += this.TPS * dt;
        this.cube.perform_move(move, clockwhise, this.progress);
        if (this.progress > 1.0) {
            this.progress = 0;
            this.current_move = null;
            this.cube.update_state(final_state.corners, final_state.edges, final_state.orientation);
        }
    }
    enqueue_algorithm(algorithm) {
        const seq = algorithm.split(" ");
        for (let move of seq) {
            let clockwhise = true;
            let double_move = false;
            if (move.length == 0)
                continue;
            else if (move.length == 2 && move[1] == "'")
                clockwhise = false;
            else if (move.length == 2 && move[1] == "2") {
                move = move[0], double_move = true;
            }
            else if (move.length >= 2)
                throw Error("Invalid move squence");
            this.cube_ctrl.execute_sequence_in_notation(move);
            let c = vectorIntToArray(this.cube_ctrl.get_state_corners());
            let e = vectorIntToArray(this.cube_ctrl.get_state_edges());
            let o = vectorIntToArray(this.cube_ctrl.get_cube_orientation());
            this.enqueue(new State(c, e, o), move[0], clockwhise);
            if (double_move) {
                this.cube_ctrl.execute_sequence_in_notation(move);
                let c = vectorIntToArray(this.cube_ctrl.get_state_corners());
                let e = vectorIntToArray(this.cube_ctrl.get_state_edges());
                let o = vectorIntToArray(this.cube_ctrl.get_cube_orientation());
                this.enqueue(new State(c, e, o), move[0], clockwhise);
            }
        }
    }
}
