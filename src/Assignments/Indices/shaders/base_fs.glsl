#version 410

in vec3 FragColor;                          // Input interpolated color from vertex shader

layout(location = 0) out vec4 FragColorOut; // Output final color

void main() {
    FragColorOut = vec4(FragColor, 1.0);    // Set fragment color
}