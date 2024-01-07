//go back to pyramid shaders
#version 420

layout(std140, binding = 0) uniform Modifier {
    float strength;
    vec3  color;
};

in vec3 FragColor;

layout(location = 0) out vec4 FragColorOut;

void main() {
    FragColorOut = vec4(FragColor * color * strength, 1.0);
}