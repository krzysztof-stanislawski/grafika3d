#version 420

layout(location = 0) in vec4 aPos;
layout(location = 1) in vec3 aColor;

layout(std140, binding=1) uniform Transformations {
    mat4 PVM;
};

out vec3 FragColor;

void main() {
    gl_Position = PVM * aPos;
    FragColor = aColor;
}