export class ShaderProgram {

    program : WebGLProgram;

    vertexLoc : number;
    normalLoc : number;
    matambLoc : number;
    matdiffLoc : number;
    matspecLoc : number;
    matshinLoc : number;
    TGLoc : number;
    VMLoc : number;
    PMLoc : number;
    NMLoc : number;

    constructor(gl, vertexSource: string, fragmentSource: string) {
        const vs = this.createShader(gl, gl.VERTEX_SHADER, vertexSource);
        const fs = this.createShader(gl, gl.FRAGMENT_SHADER, fragmentSource);

        this.program = this.createProgram(gl, vs, fs);
        gl.useProgram(this.program);

        this.initLocations(gl);
    }

    initLocations(gl) {

        this.vertexLoc  = gl.getAttribLocation(this.program,  "vertex");
        this.normalLoc  = gl.getAttribLocation(this.program,  "normal");
        this.matambLoc  = gl.getAttribLocation(this.program,  "matamb");
        this.matdiffLoc = gl.getAttribLocation(this.program, "matdiff");
        this.matspecLoc = gl.getAttribLocation(this.program, "matspec");
        this.matshinLoc = gl.getAttribLocation(this.program, "matshin");
        
        this.TGLoc = gl.getUniformLocation(this.program, "TG");
        this.VMLoc = gl.getUniformLocation(this.program, "VM");
        this.PMLoc = gl.getUniformLocation(this.program, "PM");
        this.NMLoc = gl.getUniformLocation(this.program, "NM");
    }

    createShader(gl, type, source) {
        var shader = gl.createShader(type);
        gl.shaderSource(shader,source);
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