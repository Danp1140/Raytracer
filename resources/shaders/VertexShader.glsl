#version 410 core
layout(location=0) in vec2 vertex;
layout(location=1) in vec4 colorin;

out vec4 colorthru;

void main() {
    colorthru=colorin;
    gl_Position=vec4(vertex, 0, 1);
}
