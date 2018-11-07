#version 330
#ifdef GL_ES
// Set default precision to medium
//precision mediump int;
//precision mediump float;
#endif

in vec3 _fragColor;

out vec4 FragColor;

void main() {
    FragColor = vec4(_fragColor, 1.0);
}
