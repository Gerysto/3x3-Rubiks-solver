var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    function adopt(value) { return value instanceof P ? value : new P(function (resolve) { resolve(value); }); }
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : adopt(result.value).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
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
        this.program = WebGLProgram;
        this.load_shaders(gl, url_fragment, url_fragment);
    }
    load_shaders(gl, url_vertex, url_fragment) {
        return __awaiter(this, void 0, void 0, function* () {
            const vs_source = yield this.getShaderSource(url_vertex);
            const fs_source = yield this.getShaderSource(url_fragment);
            const vs = this.createShader(gl, gl.VERTEX_SHADER, vs_source);
            const fs = this.createShader(gl, gl.FRAGMENT_SHADER, fs_source);
            this.program = this.createProgram(gl, vs, fs);
            gl.useProgram(this.program);
            this.initLocations(gl);
        });
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
    getShaderSource(url) {
        return __awaiter(this, void 0, void 0, function* () {
            let contents = yield fetch(url);
            if (!contents.ok) {
                throw new Error("Failed to read contents of: " + url);
            }
            let result = yield contents.text();
            return result;
        });
    }
    createShader(gl, type, source) {
        var shader = gl.createShader(type);
        if (!(shader instanceof WebGLShader))
            throw Error("Failed to create shader!");
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
