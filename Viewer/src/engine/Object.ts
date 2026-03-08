import {Box} from './Box.js';
import {Vec3} from './Vec3.js';
import {ShaderProgram} from '../shaders/ShaderProgram.ts'

export class Material {
    Ka : number[];
    Kd : number[];
    Ks : number[];
    Ns : number;

    constructor(Ka, Kd, Ks, Ns) {
        this.Ka = Ka; // Ambient
        this.Kd = Kd; // Diffuse
        this.Ks = Ks; // Specular
        this.Ns = Ns; // Shininess
    };
}

export class Face {
    v : number;
    n : number;
    material : string;

    constructor(v, n, m) {
        this.v = v; // Vertices
        this.n = n; // Normals
        this.material = m;
    };
}

export class Object {
    materials : Map<string,Material>
    vertices : number[];
    normals : number[];
    faces : Face[];

    constructor() {
        this.materials = new Map();
        this.vertices = [];
        this.normals = [];
        this.faces = [];
    };

    createVAO(gl: WebGL2RenderingContext, p: ShaderProgram) {
        let vao = gl.createVertexArray();
        gl.bindVertexArray(vao);

        const vertices = this.get_VBO_vertices();
        const normals = this.get_VBO_normals();
        const matamb = this.get_VBO_matamb();
        const matdiff = this.get_VBO_matdiff();
        const matspec = this.get_VBO_matspec();
        const matshin = this.get_VBO_matshin();

        // Vertex buffer: 
        let vertexBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, vertexBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(vertices), gl.STATIC_DRAW);
        gl.enableVertexAttribArray(p.vertexLoc);
        gl.vertexAttribPointer(p.vertexLoc, 3, gl.FLOAT, false, 0, 0);
        
        // Normals buffer: 
        let normalBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, normalBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(normals), gl.STATIC_DRAW);
        gl.enableVertexAttribArray(p.normalLoc);
        gl.vertexAttribPointer(p.normalLoc, 3, gl.FLOAT, false, 0, 0);

        // Ambient material parameter buffer: 
        let matambBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, matambBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(matamb), gl.STATIC_DRAW);
        gl.enableVertexAttribArray(p.matambLoc);
        gl.vertexAttribPointer(p.matambLoc, 3, gl.FLOAT, false, 0, 0);
            
        // Diffuse material parameter buffer: 
        let matdiffBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, matdiffBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(matdiff), gl.STATIC_DRAW);
        gl.enableVertexAttribArray(p.matdiffLoc);
        gl.vertexAttribPointer(p.matdiffLoc, 3, gl.FLOAT, false, 0, 0);
        
        // Specular material parameter buffer: 
        let matspecBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, matspecBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(matspec), gl.STATIC_DRAW);
        gl.enableVertexAttribArray(p.matspecLoc);
        gl.vertexAttribPointer(p.matspecLoc, 3, gl.FLOAT, false, 0, 0);
        
        
        // shinyness material parameter buffer: 
        let matshinBuffer = gl.createBuffer();
        gl.bindBuffer(gl.ARRAY_BUFFER, matshinBuffer);
        gl.bufferData(gl.ARRAY_BUFFER, new Float32Array(matshin), gl.STATIC_DRAW);
        gl.enableVertexAttribArray(p.matshinLoc);
        gl.vertexAttribPointer(p.matshinLoc, 1, gl.FLOAT, false, 0, 0);
        
        gl.bindVertexArray(null);
        
        return vao;
    }

    computeBoundingBox(): Box {
        // TODO!
        return new Box(new Vec3(-1,-1,-1),new Vec3(1,1,1));
    }

    async readObj(obj_url) {
        const response = await fetch(obj_url);
        if (!response.ok) {
            throw new Error('Failed to fetch from url:' + obj_url);
        }
        const contents = await response.text();

        let lines = contents.split("\n");
        let curr_mtl = "";

        for (let i = 0; i < lines.length; ++i) {
            const line = lines[i];
            var c;
            if (line.length <= 0) continue;
            else c = line[0];
            
            let arr : string[] = []; // Auxiliary array
            switch (c){
                case '#':
                    // comment -> ignore
                    break;
                case 'v':
                    switch (line[1]) {
                        case ' ':
                            arr = line.split(" ");
                            for (let j = 1; j < arr.length; ++j) {
                                let f : number = parseFloat(arr[j]);
                                if (arr[j] == ""){
                                    continue;
                                }
                                this.vertices.push(f);
                            }
                            break;
                        case 'n':
                            arr = line.split(" ");
                            for (let j = 1; j < arr.length; ++j) {
                                let f : number = parseFloat(arr[j]);
                                if (arr[j] == "")
                                    continue;
                                this.normals.push(f);
                            } 
                            break;
                        case 't':
                            // Not yet supported!!
                            break;
                        default:
                            // DO nothing!
                            break;
                    }
                    break;
                case 'f':
                    arr = line.split(" ");
                    let first = arr[1].indexOf("/");
                    if (first == -1) this.parseV(arr, curr_mtl);
                    
                    let second = arr[1].indexOf("/", first+1);
                    if (second == -1) this.parseVT(arr, curr_mtl);
                    if (second == first+1) this.parseVN(arr, curr_mtl);
                    else this.parseVTN(arr, curr_mtl);
                    break;
                case 'm': // Check for "mtllib"
                    arr = line.split(" ");
                    if (arr[0] == "mtllib") {
                        let url_mtl = arr[1];
                        await this.loadMaterials(url_mtl, obj_url);
                    }
                    else {
                        // Not yet supported : (
                    }
                    break;
                case 'u': // Check for "usemtl"
                    arr = line.split(" ");
                    if (arr[0] == "usemtl") {
                        curr_mtl = arr[1];
                    }
                    else {
                        // Not yet supported : (
                    }
                    break;
                default: // ignore
                    break;
            }
        }
    };

    private parseV(arr, curr_mtl) {
        let v : number[] = [];
        let n : number[] = [];
        let i = 0;
        while (i < 3) {
            v.push(parseInt(arr[i+1])-1);
            ++i;
        }
        let f = new Face(v,n,curr_mtl);
        this.faces.push(f);

        while (i < arr.length-1) {
            if (arr[i+1] == "") {
                ++i;
                continue;
            }
            v = [f.v[0], f.v[2], parseInt(arr[i+1])-1];
            f = new Face(v,n,curr_mtl);
            this.faces.push(f);
            ++i;
        }
    }

    private parseVT(arr, curr_mtl) {
        let v : number[] = [];
        let n : number[] = [];
        let i = 0;
        while (i < 3) {
            let aux = arr[i+1].split("/");
            v.push(parseInt(aux[0])-1);
            ++i;
        }
        let f = new Face(v,n,curr_mtl);
        this.faces.push(f);

        while (i < arr.length-1) {
            if (arr[i+1] == "") {
                ++i;
                continue;
            }
            let aux = arr[i+1].split("/");
            v = [f.v[0], f.v[2], parseInt(aux[0])-1];
            f = new Face(v,n,curr_mtl);
            this.faces.push(f);
            ++i;
        }
    }

    private parseVN(arr, curr_mtl) {
        let v : number[] = [];
        let n : number[] = [];
        let i = 0;
        while (i < 3) {
            let aux = arr[i+1].split("/");
            v.push(parseInt(aux[0])-1);
            n.push(parseInt(aux[2])-1);
            ++i;
        }
        let f = new Face(v,n,curr_mtl);
        this.faces.push(f);

        while (i < arr.length-1) {
            if (arr[i+1] == "") {
                ++i;
                continue;
            }
            let aux = arr[i+1].split("/");
            v = [f.v[0], f.v[2], parseInt(aux[0])-1];
            n = [f.n[0], f.n[2], parseInt(aux[2])-1]
            f = new Face(v,n,curr_mtl);
            this.faces.push(f);
            ++i;
        }
    }

    private parseVTN(arr, curr_mtl) {
        let v : number[] = [];
        let n : number[] = [];
        let i = 0;
        while (i < 3) {
            let aux = arr[i+1].split("/");
            v.push(parseInt(aux[0])-1);
            // textures are not implemented yet!
            n.push(parseInt(aux[2])-1);
            ++i;
        }
        let f = new Face(v,n,curr_mtl);
        this.faces.push(f);

        while (i < arr.length-1) {
            let aux = arr[i+1].split("/");
            if (aux.length < 3 || isNaN(parseInt(aux[0])) || isNaN(parseInt(aux[2]))) {
                console.log("NaN value found!!");
                ++i;
                continue;
            }
            v = [f.v[0], f.v[2], parseInt(aux[0])-1];
            // textures are not implemented yet!
            n = [f.n[0], f.n[2], parseInt(aux[2])-1];
            f = new Face(v,n,curr_mtl);
            this.faces.push(f);
            ++i;
        }
    }

    private async loadMaterials(mtl_url, obj_url) {
        // Fetch .mtl file
        const dir = obj_url.substring(0, obj_url.lastIndexOf("/")+1);
        //console.log(dir);
        const response = await fetch(dir + mtl_url);
        if (!response.ok) {
            throw new Error('Failed to fetch from url: ' + mtl_url);
        }
        const contents = await response.text();
        const lines = contents.split("\n");

        let curr_mtl = "";
        let Ka : number[] = [];
        let Kd : number[] = [];
        let Ks : number[] = [];
        let Ns : number = 0;

        for (let i = 0; i < lines.length; ++i) {
            const line = lines[i];
            const arr : string[] = line.split(" ");
            if (arr[0] == "newmtl"){
                if (curr_mtl != "") {
                    let mat = new Material(Ka, Kd, Ks, Ns);
                    this.materials.set(curr_mtl, mat);
                }
                curr_mtl = arr[1];
            }
            else if (arr[0] == "Ka"){
                Ka = [];
                Ka.push(parseFloat(arr[1]));
                Ka.push(parseFloat(arr[2]));
                Ka.push(parseFloat(arr[3]));
            }
            else if (arr[0] == "Kd"){
                Kd = [];
                Kd.push(parseFloat(arr[1]));
                Kd.push(parseFloat(arr[2]));
                Kd.push(parseFloat(arr[3]));

            }
            else if (arr[0] == "Ks"){
                Ks = [];
                Ks.push(parseFloat(arr[1]));
                Ks.push(parseFloat(arr[2]));
                Ks.push(parseFloat(arr[3]));

            }
            else if (arr[0] == "Ns"){
                Ns = parseFloat(arr[1]);
            }
            else {
                // Not yet supported!
            }
        }

        if (curr_mtl != "") {
            let mat = new Material(Ka, Kd, Ks, Ns);
            this.materials.set(curr_mtl, mat);
        }
        //console.log("Finished storing materials!");
        //console.log(this.materials);
    }

    get_VBO_vertices() : Float32Array {
        let vertices = new Float32Array(3*3*this.faces.length);
        for (let i = 0; i < this.faces.length; ++i) {
            let v0 = this.faces[i].v[0];
            let v1 = this.faces[i].v[1];
            let v2 = this.faces[i].v[2];

            vertices[9*i  ] = this.vertices[3*v0  ];
            vertices[9*i+1] = this.vertices[3*v0+1];
            vertices[9*i+2] = this.vertices[3*v0+2];
            vertices[9*i+3] = this.vertices[3*v1  ];
            vertices[9*i+4] = this.vertices[3*v1+1];
            vertices[9*i+5] = this.vertices[3*v1+2];
            vertices[9*i+6] = this.vertices[3*v2  ];
            vertices[9*i+7] = this.vertices[3*v2+1];
            vertices[9*i+8] = this.vertices[3*v2+2];
        }
        return vertices;
    }

    get_VBO_normals() : Float32Array {
        let normals = new Float32Array(3*3*this.faces.length);
        for (let i = 0; i < this.faces.length; ++i) {
            let n0 = this.faces[i].n[0];
            let n1 = this.faces[i].n[1];
            let n2 = this.faces[i].n[2];

            normals[9*i  ] = this.normals[3*n0  ];
            normals[9*i+1] = this.normals[3*n0+1];
            normals[9*i+2] = this.normals[3*n0+2];
            normals[9*i+3] = this.normals[3*n1  ];
            normals[9*i+4] = this.normals[3*n1+1];
            normals[9*i+5] = this.normals[3*n1+2];
            normals[9*i+6] = this.normals[3*n2  ];
            normals[9*i+7] = this.normals[3*n2+1];
            normals[9*i+8] = this.normals[3*n2+2];
        }
        return normals;
    }

    get_VBO_matamb() : Float32Array{
        //console.log(this.faces);
        let matamb = new Float32Array(3*3*this.faces.length);
        for (let i = 0; i < this.faces.length; ++i) {
            let mat = this.faces[i].material;

            const mat_values = this.materials.get(mat);
            if (mat_values == undefined) {
                console.error("Error! undefined material!");
                return matamb;
            }

            let Ka = mat_values.Ka;
            
            matamb[9*i  ] = Ka[0];
            matamb[9*i+1] = Ka[1];
            matamb[9*i+2] = Ka[2];
            matamb[9*i+3] = Ka[0];
            matamb[9*i+4] = Ka[1];
            matamb[9*i+5] = Ka[2];
            matamb[9*i+6] = Ka[0];
            matamb[9*i+7] = Ka[1];
            matamb[9*i+8] = Ka[2];
        }
        return matamb;
    }

    get_VBO_matdiff() : Float32Array{
        let matdiff = new Float32Array(3*3*this.faces.length);
        for (let i = 0; i < this.faces.length; ++i) {
            let mat = this.faces[i].material;
            const mat_values = this.materials.get(mat);

            if (mat_values == undefined) {
                console.error("Error! undefined material!");
                return matdiff;
            }

            let Kd = mat_values.Kd;
            
            matdiff[9*i  ] = Kd[0];
            matdiff[9*i+1] = Kd[1];
            matdiff[9*i+2] = Kd[2];
            matdiff[9*i+3] = Kd[0];
            matdiff[9*i+4] = Kd[1];
            matdiff[9*i+5] = Kd[2];
            matdiff[9*i+6] = Kd[0];
            matdiff[9*i+7] = Kd[1];
            matdiff[9*i+8] = Kd[2];
        }
        return matdiff;
    }

    get_VBO_matspec() : Float32Array {
        let matspec = new Float32Array(3*3*this.faces.length);
        for (let i = 0; i < this.faces.length; ++i) {
            let mat = this.faces[i].material;
            const mat_values = this.materials.get(mat);

            if (mat_values == undefined) {
                console.error("Error! undefined material!");
                return matspec;
            }

            let Ks = mat_values.Ks;

            matspec[9*i  ] = Ks[0];
            matspec[9*i+1] = Ks[1];
            matspec[9*i+2] = Ks[2];
            matspec[9*i+3] = Ks[0];
            matspec[9*i+4] = Ks[1];
            matspec[9*i+5] = Ks[2];
            matspec[9*i+6] = Ks[0];
            matspec[9*i+7] = Ks[1];
            matspec[9*i+8] = Ks[2];
        }
        return matspec;
    }
    
    get_VBO_matshin() : Float32Array {
        let matshin = new Float32Array(3*this.faces.length);
        for (let i = 0; i < this.faces.length; ++i) {
            let mat = this.faces[i].material;
            const mat_values = this.materials.get(mat);

            if (mat_values == undefined) {
                console.error("Error! undefined material!");
                return matshin;
            }

            let Ns = mat_values.Ns;

            
            matshin[3*i  ] = Ns;
            matshin[3*i+1] = Ns;
            matshin[3*i+2] = Ns;
        }
        return matshin;
    }
}

