#version 430

attribute vec3 Vertex;
uniform mat4 ModelViewProjectionMatrix;


//out vec4 outColor;

void main(void)
{
    gl_Position = ModelViewProjectionMatrix * vec4(Vertex,1.0);
//    outColor = Color;
}
