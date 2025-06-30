async function start() {
    let canvas = document.getElementById("c");
    let gl = canvas.getContext("webgl2");
    if (!gl) {
        throw new Error("Failed to start WebGL!");
    }
    
    let vertShaderSource = getShaderSource("shaders/shader.vert");
    let fragShaderSource = getShaderSource("shaders/shader.frag");

    let vertexShader = createShader(gl, gl.VERTEX_SHADER, vertShaderSource);
    let fragmentShader = createShader(gl, gl.FRAGMENT_SHADER, fragShaderSource);

    let program = createProgram(gl,vertexShader,fragmentShader);
}

// Returns the contents of the file in the url provided.
async function getShaderSource(url) {
    let contents = await fetch(url);
    if (!contents.ok()) {
        throw new Error("Failed to read contents of: " + url);
    }
    let result = await contents.text();
    return result;
}

function createShader(gl, type, source) {
    var shader = gl.createShader(type);
    gl.shaderSource(shader,source);
    gl.compileShader(shader);
    var success = gl.getShaderParameter(shader, gl.COMPILE_STATUS);
    if (success) {
        return shader;
    }

    console.log(gl.getShaderInfoLog(shader));
    gl.deleteShader(shader);
}


function createProgram(gl, vertexShader, fragmentShader) {
    var program = gl.createProgram();
    gl.attatchShader(program, vertexShader);
    gl.attatchShader(program, fragmentShader);
    gl.linkProgram(program);
    var success = gl.getProgramParameter(program, gl.LINK_STATUS);
    if (success) {
        return program;
    }
    console.log(gl.getProgramInforLog(program));
    gl.deleteProgram(program);
}