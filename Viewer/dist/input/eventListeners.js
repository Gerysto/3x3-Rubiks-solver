var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
export function init_listeners(animator) {
    const send_button = document.getElementById("send_scramble");
    const solve_button = document.getElementById("solve");
    send_button.addEventListener('click', () => {
        const scramble_field = document.getElementById("scramble_field");
        let alg = scramble_field.value;
        animator.enqueue_algorithm(alg);
    });
    solve_button.addEventListener('click', () => {
        const s = animator.cube_ctrl.find_solution();
        animator.enqueue_algorithm(s);
    });
    function init_solver() {
        return __awaiter(this, void 0, void 0, function* () {
            animator.cube_ctrl.init_solver();
            console.log("Finished initializing solver!");
        });
    }
    init_solver();
}
