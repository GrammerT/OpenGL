#version 430

attribute vec3 Vertex;
attribute vec3 normal;

uniform mat4 Model;
uniform mat4 View;
uniform mat4 Projection;

//uniform vec4 Color;

out vec3 gNormal;
out vec3 FragPos;

void main(void)
{
    FragPos = vec3(Model * vec4(Vertex,1.0)); //! 点在世界坐标系下的位置
    gNormal =/*Model**/normal;
    gl_Position = Projection*View*vec4(FragPos,1.0);
}
