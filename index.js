g = {};

async function start() {
    let canvas = document.getElementById("c");
    let gl = canvas.getContext("webgl2");
    if (!gl) {
        throw new Error("Failed to start WebGL!");
    }
    
    g.program = await loadShaders(gl);
    initialize(gl);
}

function resizeCanvasToDisplaySize(canvas) {
    const dpr = window.devicePixelRatio || 1;
    const displayWidth = Math.floor(canvas.clientWidth * dpr);
    const displayHeight = Math.floor(canvas.clientHeight * dpr);

    if (canvas.width !== displayWidth || canvas.height !== displayHeight) {
        canvas.width = displayWidth;
        canvas.height = displayHeight;
        return true;
    }
    return false;
}

async function loadShaders(gl) {
    // Setup the program (vertex + fragment shaders)
    let vertShaderSource = await getShaderSource("shaders/shader.vert");
    let fragShaderSource = await getShaderSource("shaders/shader.frag");

    let vertexShader = createShader(gl, gl.VERTEX_SHADER, vertShaderSource);
    let fragmentShader = createShader(gl, gl.FRAGMENT_SHADER, fragShaderSource);

    let program = createProgram(gl,vertexShader,fragmentShader);
    gl.useProgram(program);
    
    return program;
}

function initialize(gl) {
    
    // Set viewport size:
    resizeCanvasToDisplaySize(gl.canvas);
    gl.viewport(0,0,gl.canvas.width,gl.canvas.height);
    console.log(gl.canvas.width, gl.canvas.height);

    // Get attribute locations:
    g.vertexLoc = gl.getAttribLocation(g.program, "vertex");
    g.normalLoc = gl.getAttribLocation(g.program, "normal");
    g.matambLoc = gl.getAttribLocation(g.program, "matamb");
    g.matdiffLoc = gl.getAttribLocation(g.program, "matdiff");
    g.matspecLoc = gl.getAttribLocation(g.program, "matspec");
    g.matshinLoc = gl.getAttribLocation(g.program, "matshin");
    
    // set up the VAO 
    const url = "Patricio.obj";
    let vao_model = createBuffersModel(url);
    gl.drawArrays(gl.TRIANGLES, 0, 3);
}

// Creates and fills the requiered Web-GL buffers to render the model.
// Returns the model's VAO (vertex array object)
function createbuffersModel(url) {
    vao = gl.createVertexArray();
    gl.bindVertexArray(vao);

    model = new Model();

    model.load(url);
    // Create and fill-in the buffers
    let vertices = model.get_VBO_vertices();
    let normals = model.get_VBO_normals();
    let matamb = model.get_VBO_matamb();
    let matdiff = model.get_VBO_matdiff();
    let matspec = model.get_VBO_matspec();
    let matshin = model.get_VBO_matshin();

    // Vertex buffer: 
    let vertexBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
    gl.enableVertexAttribArray(vertexLoc);
    gl.vertexAttribPointer(vertexLoc, 3, gl.FLOAT, false, 0, 0);
    
    // Normals buffer: 
    let normalBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, normalBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(normals), gl.STATIC_DRAW);
    gl.enableVertexAttribArray(g.normalLoc);
    gl.vertexAttribPointer(g.normalLoc, 3, gl.FLOAT, false, 0, 0);

    // Ambient material parameter buffer: 
    let matambBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, matambBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(matamb), gl.STATIC_DRAW);
    gl.enableVertexAttribArray(g.matambLoc);
    gl.vertexAttribPointer(g.matambLoc, 3, gl.FLOAT, false, 0, 0);
        
    // Diffuse material parameter buffer: 
    let matdiffBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, matdiffbuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(matdiff), gl.STATIC_DRAW);
    gl.enableVertexAttribArray(g.matdiffLoc);
    gl.vertexAttribPointer(g.matdiffLoc, 3, gl.FLOAT, false, 0, 0);
    
    // Specular material parameter buffer: 
    let matspecBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, matspecBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(matspec), gl.STATIC_DRAW);
    gl.enableVertexAttribArray(g.matspecLoc);
    gl.vertexAttribPointer(g.matspecLoc, 3, gl.FLOAT, false, 0, 0);
    
    
    // shinyness material parameter buffer: 
    let matshinBuffer = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, matshinBuffer);
    gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(matshin), gl.STATIC_DRAW);
    gl.enableVertexAttribArray(g.matshinLoc);
    gl.vertexAttribPointer(g.matshinLoc, 1, gl.FLOAT, false, 0, 0);
    
    gl.bindVertexArray(null);
    return vao;
}