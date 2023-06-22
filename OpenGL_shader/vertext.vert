#version 330 core
layout(location=0) in vec3 pos;
layout(location=1) in vec3 normal;

uniform mat4 modelMat;
uniform mat4 viewMat;
uniform mat4 projMat;

out vec3 fNormal;
out vec3 fragPos;


void main()
{
   gl_Position=projMat*viewMat*modelMat*vec4(pos.xyz,1.0f);
   fragPos = vec3(modelMat*vec4(pos.xyz,1.0));
   fNormal = mat3(transpose(inverse(modelMat)))*normal;
}
