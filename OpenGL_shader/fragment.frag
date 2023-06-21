#version 330 core
in vec2 texCoord;

out vec4 fragColor;

uniform sampler2D ourTexture;
uniform vec3 objColor;
uniform vec3 ambineColor;



void main()
{
    fragColor = vec4(objColor*ambineColor,1.0f)*texture(ourTexture,texCoord);
}
