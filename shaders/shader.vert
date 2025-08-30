#version 300 es

in vec3 vertex;
in vec3 normal;
in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

out vec3 f_vertex;
out vec3 f_normal;
out vec3 f_matamb;
out vec3 f_matdiff;
out vec3 f_matspec;
out float f_matshin;

uniform mat4 TG;
uniform mat4 VM;
uniform mat4 PM;
uniform mat4 NM;

void main() {
    f_vertex = VM*TG*vec4(vertex, 1.0);
    f_normal = vec3(NM*vec4(normal, 1.0));
    f_matamb = matamb;
    f_matdiff = matdiff;
    f_matspec = matspec;
    f_matshin = matshin;

    gl_Position = vec4(vertex, 1.0);
}