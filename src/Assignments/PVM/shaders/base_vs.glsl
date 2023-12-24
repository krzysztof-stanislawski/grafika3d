#version 420

layout(std140, binding=1) uniform Transformations {
    mat4 PVM;
};

layout(location = 0) in vec4 aPos;      // Input vertex position
layout(location = 1) in vec3 aColor;    // Input vertex color

out vec3 FragColor;                     // Output interpolated color to fragment shader

void main() {
    gl_Position =  PVM * aPos;
    FragColor = aColor;                 // Pass color to fragment shader
}
