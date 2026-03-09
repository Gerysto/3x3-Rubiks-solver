export class ShaderProgram {
    constructor(gl, url_vertex, url_fragment) {
        this.vertexLoc = -1;
        this.normalLoc = -1;
        this.matambLoc = -1;
        this.matdiffLoc = -1;
        this.matspecLoc = -1;
        this.matshinLoc = -1;
        this.TGLoc = -1;
        this.VMLoc = -1;
        this.PMLoc = -1;
        this.NMLoc = -1;
        const vs = this.createShader(gl, gl.VERTEX_SHADER, url_vertex);
        const fs = this.createShader(gl, gl.FRAGMENT_SHADER, url_fragment);
        this.program = this.createProgram(gl, vs, fs);
        gl.useProgram(this.program);
        this.initLocations(gl);
    }
    initLocations(gl) {
        this.vertexLoc = gl.getAttribLocation(this.program, "vertex");
        this.normalLoc = gl.getAttribLocation(this.program, "normal");
        this.matambLoc = gl.getAttribLocation(this.program, "matamb");
        this.matdiffLoc = gl.getAttribLocation(this.program, "matdiff");
        this.matspecLoc = gl.getAttribLocation(this.program, "matspec");
        this.matshinLoc = gl.getAttribLocation(this.program, "matshin");
        const TGLocAux = gl.getUniformLocation(this.program, "TG");
        const VMLocAux = gl.getUniformLocation(this.program, "VM");
        const PMLocAux = gl.getUniformLocation(this.program, "PM");
        const NMLocAux = gl.getUniformLocation(this.program, "NM");
        if (!(TGLocAux instanceof WebGLUniformLocation))
            throw Error("Failed to assign location to uniform TGLoc");
        if (!(VMLocAux instanceof WebGLUniformLocation))
            throw Error("Failed to assign location to uniform VMLoc");
        if (!(PMLocAux instanceof WebGLUniformLocation))
            throw Error("Failed to assign location to uniform PMLoc");
        if (!(NMLocAux instanceof WebGLUniformLocation))
            throw Error("Failed to assign location to uniform NMLoc");
        this.TGLoc = TGLocAux;
        this.VMLoc = VMLocAux;
        this.PMLoc = PMLocAux;
        this.NMLoc = NMLocAux;
    }
    createShader(gl, type, source) {
        var shader = gl.createShader(type);
        if (!(shader instanceof WebGLShader))
            throw Error("Failed to load create shader!");
        gl.shaderSource(shader, source);
        gl.compileShader(shader);
        var success = gl.getShaderParameter(shader, gl.COMPILE_STATUS);
        if (success) {
            return shader;
        }
        console.log(gl.getShaderInfoLog(shader));
        gl.deleteShader(shader);
        throw new Error("Failed to create Shader!\n" + source);
    }
    createProgram(gl, vertexSource, fragmentSource) {
        var program = gl.createProgram();
        gl.attachShader(program, vertexSource);
        gl.attachShader(program, fragmentSource);
        gl.linkProgram(program);
        var success = gl.getProgramParameter(program, gl.LINK_STATUS);
        if (success) {
            return program;
        }
        console.log(gl.getProgramInfoLog(program));
        gl.deleteProgram(program);
        throw new Error("Failed to create Program!");
    }
    use(gl) {
        gl.useProgram(this.program);
    }
}
