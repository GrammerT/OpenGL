#version 330 core
layout(location=0) in vec3 pos;
layout(location=1) in vec3 acolor;
layout(location=2) in vec2 aTexCoord;

out vec4 vertexColor;
out vec2 texCoord;
void main()
{
   gl_Position = vec4(pos.x,pos.y,pos.z,1.0f);
   vertexColor = vec4(acolor.x,acolor.y,acolor.z, 1.0f);
   texCoord = aTexCoord;
}
