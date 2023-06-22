#version 330 core

out vec4 fragColor;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

in vec3 fragPos;
in vec3 fNormal;

void main()
{
//    vec3 ambient = ambientColor*lightColor;
    vec3 lightDire = normalize(lightPos-fragPos);
    vec3 reflectVec = reflect(-lightDire,fNormal);
    vec3 cameraVec = normalize(cameraPos-fragPos);

    float specularAmount = pow(max(dot(reflectVec,cameraVec),0),1);
    vec3 spcular = specularAmount*lightColor;

    vec3 diffuse = max(dot(lightDire,fNormal),0)*lightColor;

//    fragColor = vec4(ambient,1.0f);
    fragColor = vec4(diffuse*objColor+ambientColor*objColor+spcular*objColor,1.0f);

}
