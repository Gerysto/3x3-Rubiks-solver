import { CubeController } from '../../libs/cube_lib.js';
import { State, RubiksCube } from '../rubikscube/rubiks_cube.js';

export class RubiksAnimator {

    cube: RubiksCube;
    progress: number;
    queue: [State, string, boolean][];

    cube_ctrl: any;
    TPS: number = 16; // Turns per second 
    
    // (final_state, move, clockwhise?)
    current_move: [State, string, boolean] | null;

    constructor(cube: RubiksCube, ctrl: any) {
        this.cube = cube;
        this.progress = 0;
        this.queue = [];
        this.current_move = null;
        this.cube_ctrl = ctrl;
        this.TPS = 5;
    }

    enqueue(final_state: State, move: string, clockwhise: boolean) {
        this.queue.push([final_state, move, clockwhise]);
    }

    update(dt: number) {
        if (!this.current_move) {
            if (this.queue.length == 0) return;
            else {
                this.current_move = this.queue.shift() as [State, string, boolean];
            }
        }

        const [final_state, move, clockwhise] = this.current_move;

        this.progress += this.TPS*dt;
        this.cube.perform_move(move, clockwhise, this.progress);

        if (this.progress > 1.0) {
            this.progress = 0;
            this.current_move = null;
            this.cube.update_state(final_state.corners, final_state.edges);
        }
    }

    vectorToArray(v: any): number[] {
        let res = [];
        for (let i = 0; i < v.size(); ++i) {
            res.push(v.get(i));
        }
        return res;
    }

    enqueue_algorithm(algorithm: string) {
        const seq = algorithm.split(" ");
        
        for (let move of seq) {
            let clockwhise = true;
            let double_move = false;

            if (move.length == 0) continue;
            else if (move.length == 2 && move[1] == "'") clockwhise = false;
            else if (move.length == 2 && move[1] == "2") {move = move[0], double_move = true;}
            else if (move.length >= 2) throw Error("Invalid move squence");
            
            this.cube_ctrl.execute_sequence_in_notation(move);
            let c = this.vectorToArray(this.cube_ctrl.get_state_corners());
            let e = this.vectorToArray(this.cube_ctrl.get_state_edges());
            this.enqueue(new State(c,e), move[0], clockwhise);
            if (double_move) {
                this.cube_ctrl.execute_sequence_in_notation(move);
                let c = this.vectorToArray(this.cube_ctrl.get_state_corners());
                let e = this.vectorToArray(this.cube_ctrl.get_state_edges());
                this.enqueue(new State(c,e), move[0], clockwhise);
            }
        }
    }

    /**
     * 
        let module = await createModule();
        let ctrl = new module.CubeController();
        ctrl.execute_sequence_in_notation("R");

        const corner_state = this.vectorToArray(ctrl.get_state_corners());
        const edge_state   = this.vectorToArray(ctrl.get_state_edges());
        rubiks_cube.update_state(corner_state, edge_state);
     */
}