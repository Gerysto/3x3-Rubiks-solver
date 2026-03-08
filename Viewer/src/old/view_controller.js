async function run() {
    const Module = await createModule();
    const obj = new Module.CubeController();

    const send_button = document.getElementById("send_scramble");
    
    send_button.addEventListener('click', () => {
        scramble_field = document.getElementById("scramble_field");
        obj.execute_sequence_in_notation(scramble_field.value);
        obj.print_state();
    })
}

run();