#version 330 core

out vec4 fragColor;

uniform vec3 objColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

in vec3 fragPos;
in vec3 fNormal;

void main()
{
    float ambientStrength = 0.1f;
    vec3 ambient = ambientStrength*lightColor;

    vec3 lightDire = normalize(lightPos-fragPos);
    float diffuse = max(dot(lightDire,fNormal),0);

//    fragColor = vec4(objColor*ambient,1.0f);
    fragColor = vec4(objColor*diffuse,1.0f);

}
