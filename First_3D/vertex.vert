#version 430

attribute vec4 Vertex;
uniform mat4 ModelViewProjectionMatrix;
uniform vec4 Color;

out vec4 outColor;

void main(void)
{
    gl_Position = ModelViewProjectionMatrix * Vertex;
    outColor = Color;
}
