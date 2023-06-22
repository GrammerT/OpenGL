#version 330 core

out vec4 fragColor;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

in vec3 fragPos;
in vec3 fNormal;

void main()
{
//    vec3 ambient = ambientColor*lightColor;

    vec3 lightDire = normalize(lightPos-fragPos);
    float diffuse = max(dot(lightDire,fNormal),0);

//    fragColor = vec4(ambient,1.0f);
    fragColor = vec4(diffuse*objColor+ambientColor*lightColor,1.0f);

}
