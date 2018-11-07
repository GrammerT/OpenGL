#version 330
#ifdef GL_ES
// Set default precision to medium
//precision mediump int;
//precision mediump float;
#endif

attribute vec3 VertexPosition;

uniform vec3 FaceColor;
uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;


out vec3 _fragColor;

void main()
{
    _fragColor = FaceColor;
    gl_Position = MVP * vec4(VertexPosition,1.0);
}
