export function init_listeners(animator) {
    const send_button = document.getElementById("send_scramble");
    send_button.addEventListener('click', () => {
        const scramble_field = document.getElementById("scramble_field");
        let alg = scramble_field.value;
        animator.enqueue_algorithm(alg);
    });
}
