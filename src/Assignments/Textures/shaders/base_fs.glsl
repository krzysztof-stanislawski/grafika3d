#version 420

layout(std140, binding = 2) uniform Modifier {
    vec4 Kd;
    bool use_map_Kd;
};

in vec2 vertex_texcoords; 

uniform sampler2D map_Kd;

layout(location = 0) out vec4 FragColorOut;

void main() {
    if(use_map_Kd) {
       FragColorOut = Kd*texture(map_Kd, vertex_texcoords);
    } else {
        FragColorOut = Kd;
    }
}
