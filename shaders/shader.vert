#version 300 es

in vec3 vertex;
in vec3 color;
out vec3 f_color;

void main() {
    f_color = color;
    gl_Position = vec4(vertex, 1.0);
}