#version 410

layout(location = 0) in vec3 aPos;      // Input vertex position
layout(location = 1) in vec3 aColor;    // Input vertex color

out vec3 FragColor;                     // Output interpolated color to fragment shader

void main() {
    gl_Position = vec4(aPos, 1.0);      // Set vertex position
    FragColor = aColor;                 // Pass color to fragment shader
}
