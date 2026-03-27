#version 300 es

precision highp float;

in vec3 vertexSCO;
in vec3 normalSCO;
in vec3 f_matamb;
in vec3 f_matdiff;
in vec3 f_matspec;
in float f_matshin;

out vec4 FragColor;


uniform mat4 VM;

vec3 lightCol = vec3(1.0,1.0,1.0);
vec3 cameraLight = vec3(0,0,0);

const float lightDistance = 3.0;

const vec3 lights[8] = vec3[8](
    vec3(-lightDistance , -lightDistance ,-lightDistance ),
    vec3(-lightDistance , -lightDistance , lightDistance ),
    vec3(-lightDistance ,  lightDistance ,-lightDistance ),
    vec3(-lightDistance ,  lightDistance , lightDistance ),
    vec3( lightDistance , -lightDistance ,-lightDistance ),
    vec3( lightDistance , -lightDistance , lightDistance ),
    vec3( lightDistance ,  lightDistance ,-lightDistance ),
    vec3( lightDistance ,  lightDistance , lightDistance )
);

vec3 amb = vec3(0.1, 0.1, 0.1);

vec3 ambient() {
    return f_matamb*amb;
}
vec3 diffuse(vec3 L, vec3 norm) {
    return lightCol*f_matdiff*vec3(min(max(dot(norm,L),0.0),1.0));
}
vec3 specular(vec3 L, vec3 vertexSCO, vec3 normalSCO) {
    vec3 R = 2.0*dot(normalSCO,L)*normalSCO - L;
    vec3 v = normalize(vertexSCO);
    return lightCol*f_matspec*min(max(pow(dot(-v,R),f_matshin),0.0),1.0);
}


vec3 phong_lighting(vec3 normalSCO, vec3 vertexSCO) {
    
    vec3 col;
    col += ambient();
    col += diffuse(cameraLight, normalSCO);
    col += specular(cameraLight, vertexSCO, normalSCO);
    for (int i = 0; i < 8; ++i) {
        vec3 L = vec3(VM*vec4(lights[i] ,1.0)) - vertexSCO;
        L = normalize(L);
        col += diffuse(L, normalSCO);
        col += specular(L, vertexSCO, normalSCO);
    }
    return col;
}

void main() {

    vec3 col, L, n;
    n = normalize(normalSCO);
    col = phong_lighting(normalSCO, vertexSCO);

    FragColor = vec4(col,1.0);
}