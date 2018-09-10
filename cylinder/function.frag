#version 330
#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

flat in vec3 LightIntensity;

out vec4 FragColor;

void main() {
    FragColor = vec4(LightIntensity, 1.0);
}
