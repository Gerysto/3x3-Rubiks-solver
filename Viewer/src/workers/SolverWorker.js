import createModule from "../../libs/cube_lib.js";


const wasmConfig = {
    locateFile: function(path) {
        // This forces the .data (and usually .wasm) to be fetched from the root
        if (path.endsWith('.data')) {
            return "../../" + path; 
        }
        if (path.endsWith('.wasm')) {
            return "../../libs/" + path;
        }
        return path;
    }
};

const moduleInstance = await createModule(wasmConfig);
const ctrl = new moduleInstance.CubeController();

ctrl.init_solver(); // Thinking :D



onmessage = (e) => {
    console.log("Message recieved from main script!");
    const cube_ctrl = e.data;
    const s = cube_ctrl.find_solution();
    console.log("Solution: ", s);
}