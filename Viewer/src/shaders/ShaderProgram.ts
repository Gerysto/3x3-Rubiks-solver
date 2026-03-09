export class ShaderProgram {

    program : WebGLProgram;

    vertexLoc : number = -1;
    normalLoc : number = -1;
    matambLoc : number = -1;
    matdiffLoc : number = -1;
    matspecLoc : number = -1;
    matshinLoc : number = -1;
    TGLoc : WebGLUniformLocation = -1;
    VMLoc : WebGLUniformLocation = -1;
    PMLoc : WebGLUniformLocation = -1;
    NMLoc : WebGLUniformLocation = -1;

    constructor() {
        this.program = WebGLProgram;
    }

    async load_shaders(gl : WebGL2RenderingContext, url_vertex: string, url_fragment: string) {
        
        const vs_source = await this.getShaderSource(url_vertex);
        const fs_source = await this.getShaderSource(url_fragment);
        
        const vs = this.createShader(gl, gl.VERTEX_SHADER, vs_source);
        const fs = this.createShader(gl, gl.FRAGMENT_SHADER, fs_source);

        this.program = this.createProgram(gl, vs, fs);
        gl.useProgram(this.program);
        this.initLocations(gl);
    }

    initLocations(gl:WebGL2RenderingContext) {
        this.vertexLoc  = gl.getAttribLocation(this.program,  "vertex");
        this.normalLoc  = gl.getAttribLocation(this.program,  "normal");
        this.matambLoc  = gl.getAttribLocation(this.program,  "matamb");
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

        this.TGLoc = TGLocAux as WebGLUniformLocation;
        this.VMLoc = VMLocAux as WebGLUniformLocation;
        this.PMLoc = PMLocAux as WebGLUniformLocation;
        this.NMLoc = NMLocAux as WebGLUniformLocation;

        console.log(this.TGLoc);
        console.log(this.VMLoc);
        console.log(this.PMLoc);
        console.log(this.NMLoc);
    }

    private async getShaderSource(url: string): Promise<string> {
    let contents = await fetch(url);
    if (!contents.ok) {
        throw new Error("Failed to read contents of: " + url);
    }
    let result = await contents.text();
    return result;
}


    createShader(gl:WebGL2RenderingContext, type: GLenum, source: string) {
        var shader = gl.createShader(type);
        if (!(shader instanceof WebGLShader)) 
            throw Error("Failed to create shader!");
        
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

    createProgram(gl: WebGL2RenderingContext, vertexSource:WebGLShader, fragmentSource: WebGLShader) {
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

    use(gl: WebGL2RenderingContext) {
        gl.useProgram(this.program);
    }

}