#version 320 es

layout(location = 0) in vec4 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    //gl_Position = projection * view * model * position;
    gl_Position = vec4(0.0, 0.0, 0.0, 1.0);
}
