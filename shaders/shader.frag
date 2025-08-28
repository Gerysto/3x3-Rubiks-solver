#version 300 es

precision highp float;

in vec3 f_color;
out vec4 FragColor;

void main() {
    FragColor = vec4(f_color,1);
}