#version 420

layout(std140, binding = 1) uniform Transformations {
    vec2 scale;
    vec2 translation;
    mat2 rotation;
};

layout(location = 0) in vec3 aPos;      // Input vertex position
layout(location = 1) in vec3 aColor;    // Input vertex color

out vec3 FragColor;                     // Output interpolated color to fragment shader

void main() {
    vec2 translatedPosition = aPos.xy + translation;
    vec2 scaledPosition = scale * translatedPosition;
    vec2 rotatedPosition = rotation * scaledPosition;

    //gl_Position = vec4(rotatedPosition, aPos.z, 1.0); // Set transformed vertex position
    gl_Position = vec4(scaledPosition, aPos.z, 1.0);
    FragColor = aColor;                 // Pass color to fragment shader
}
