#version 450 core

layout (location = 0) out vec3 FragColor;

vec3 pos[3] = vec3[3](
    vec3(-0.4, -0.4, 0.0),
    vec3(0.4, -0.4, 0.0),
    vec3(0.0, 0.4, 0.0)
);

vec3 color[3] = vec3[3](
    vec3(1.0, 0.0, 0.0),
    vec3(0.0, 1.0, 0.0),
    vec3(0.0, 0.0, 1.0)
);

void main() {
    gl_Position = vec4(pos[gl_VertexIndex],1.0);
    FragColor = color[gl_VertexIndex];
}