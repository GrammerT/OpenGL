#version 330 core
layout(location=0) in vec3 pos;
layout(location=1) in vec2 aTexCoord;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec2 texCoord;


void main()
{
   gl_Position=projMat*viewMat*modelMat*vec4(pos.x,pos.y,pos.z,1.0f);
   texCoord=aTexCoord;
}
