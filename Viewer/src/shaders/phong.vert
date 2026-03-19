#version 300 es

in vec3 vertex;
in vec3 normal;
in vec3 matamb;
in vec3 matdiff;
in vec3 matspec;
in float matshin;

out vec3 vertexSCO;
out vec3 normalSCO;
out vec3 f_matamb;
out vec3 f_matdiff;
out vec3 f_matspec;
out float f_matshin;

uniform mat4 TG;
uniform mat4 VM;
uniform mat4 PM;
uniform mat4 NM;

uniform int piece_type;
uniform int piece_id;

const vec3 white  = vec3(1.00, 0.96, 0.94);
const vec3 yellow = vec3(1.00, 1.00, 0.00);
const vec3 green  = vec3(0.00, 0.80, 0.00);
const vec3 blue   = vec3(0.01, 0.08, 0.80);
const vec3 red    = vec3(0.80, 0.00, 0.00);
const vec3 orange = vec3(0.80, 0.16, 0.00);

const vec3 black  = vec3(0.00, 0.00, 0.00);

// This table contains first the plastic corner_color
// and then, the stikers read clockwhise 
// (always starting from white or yellow)

const int CORNER_PIECE = 0;
const int EDGE_PIECE   = 1;
const int CENTER_PIECE = 2;

vec3[] corner_colors =  vec3[](
    white , blue  , orange, // Corner 0
    white , red   , blue  , // Corner 1 
    white , green , red   , // Corner 2
    white , orange, green , // Corner 3

    yellow, orange, blue  , // Corner 4
    yellow, blue  , red   , // Corner 5
    yellow, red   , green , // Corner 6
    yellow, green , orange  // Corner 7
);

vec3[] edge_colors = vec3[](
    white , blue  , // Edge 0
    white , red   , // Edge 1
    white , green , // Edge 2
    white , orange, // Edge 3

    blue  , orange, // Edge 4
    blue  , red   , // Edge 5
    green , red   , // Edge 6
    green , orange, // Edge 7

    yellow, blue  , // Edge 8
    yellow, red   , // Edge 9
    yellow, green , // Edge 10
    yellow, orange  // Edge 11
);

vec3[] center_colors = vec3[](
    white , // Center 0
    red   , // Center 1
    green , // Center 2
    yellow, // Center 3
    orange, // Center 4
    blue    // Center 5
);

const float EPSILON = 0.1;

vec3 get_corner_color(int id, vec3 col) {
    if (distance(col, black) < EPSILON) return black;
    return col.r * corner_colors[3*id + 0] \
         + col.g * corner_colors[3*id + 1] \
         + col.b * corner_colors[3*id + 2];
}

vec3 get_edge_color(int id, vec3 col) {
    if (distance(col, black) < EPSILON) return black;
    return col.r * edge_colors[2*id + 0] \
         + col.g * edge_colors[2*id + 1];
}

vec3 get_center_color(int id, vec3 col) {
    if (distance(col, black) < EPSILON) return black;
    return col.r * center_colors[id];
}

void main() {
    vec4 v = VM*TG*vec4(vertex, 1.0);
    vertexSCO = v.xyz;
    normalSCO = normalize((NM*vec4(normal, 1.0)).xyz);
    f_matamb = matamb;
    f_matspec = matspec;
    f_matshin = matshin;

    
    // Determine the color:

    if (piece_type == CORNER_PIECE) {
        f_matdiff = get_corner_color(piece_id, matdiff);
    } 
    else if (piece_type == EDGE_PIECE) {
        f_matdiff = get_edge_color(piece_id, matdiff);
    }
    else if (piece_type == EDGE_PIECE) {
        f_matdiff = get_center_color(piece_id, matdiff);
    }



    gl_Position = PM*v;

}
