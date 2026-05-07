import createModule from "../../libs/cube_lib.js";
import {arrayToVectorInt, vectorIntToArray} from "../../libs/wasm_utils.js"

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
self.postMessage('READY');

onmessage = (e) => {
    console.log("Message recieved from main script!");
    const cube_state = e.data;
    console.log("Data: ", cube_state);
    
    let corners = arrayToVectorInt(cube_state.corners, moduleInstance);
    let edges = arrayToVectorInt(cube_state.edges, moduleInstance);
    let orientation = arrayToVectorInt(cube_state.orientation, moduleInstance);
    ctrl.set_state(corners, edges, orientation);

    const s = ctrl.find_solution();
    console.log("Solution: ", s);
    self.postMessage(s);
}