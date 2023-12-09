#version 420

layout(std140, binding = 1) uniform Transformations {
    vec2 scale;
    vec2 translation;
    mat2 rotation;
};

layout(location = 0) in vec4 aPos;      // Input vertex position
layout(location = 1) in vec3 aColor;    // Input vertex color

out vec3 FragColor;                     // Output interpolated color to fragment shader

void main() {
    gl_Position = aPos;

    gl_Position.xy = rotation*(scale*aPos.xy)+translation;
    gl_Position.xy = rotation*(scale*aPos.xy);
    gl_Position.zw = aPos.zw;

    FragColor = aColor;                 // Pass color to fragment shader
}
