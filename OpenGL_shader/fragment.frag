#version 330 core

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 speclar;
    float shininess;
};

uniform Material material;

uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 cameraPos;

in vec3 fragPos;
in vec3 fNormal;

out vec4 fragColor;

void main()
{
//    vec3 ambient = ambientColor*lightColor;
    vec3 lightDire = normalize(lightPos-fragPos);
    vec3 reflectVec = reflect(-lightDire,fNormal);
    vec3 cameraVec = normalize(cameraPos-fragPos);

    //! specular;
    float specularAmount = pow(max(dot(reflectVec,cameraVec),0),material.shininess);
    vec3 spcular = material.speclar * specularAmount*lightColor;

    //! diffuse
    vec3 diffuse = material.diffuse*max(dot(lightDire,fNormal),0)*lightColor;

    //! ambient
    vec3 ambientVec = material.ambient * ambientColor;

    fragColor = vec4(diffuse*objColor+ambientVec*objColor+spcular*objColor,1.0f);

}
