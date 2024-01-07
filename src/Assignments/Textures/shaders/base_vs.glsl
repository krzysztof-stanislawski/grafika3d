#version 420

layout(location = 0) in vec4 aPos;
layout(location = 1) in vec2 aTexCoord;

layout(std140, binding=1) uniform Transformations {
    mat4 PVM;
};

out vec2 vertex_texcoords;

void main() {
    vertex_texcoords = aTexCoord;
    gl_Position = PVM * aPos;
}