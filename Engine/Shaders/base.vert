#version 450 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;

layout (location = 0) out vec3 FragColor;



void main() {
    gl_Position = vec4(pos,1.0);
    FragColor = col;
}