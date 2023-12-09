#version 420

layout(std140, binding = 0) uniform Modifier {
    float strength;
    vec3  color;
};

in vec3 FragColor;                          // Input interpolated color from vertex shader

layout(location = 0) out vec4 FragColorOut; // Output final color

void main() {
    vec3 modifiedColor = FragColor * color * strength;  // Modify the color using buffer data
    FragColorOut = vec4(modifiedColor, 1.0);    // Set fragment color
}