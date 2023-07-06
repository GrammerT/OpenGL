#version 330 core

struct Material{
    vec3 ambient;
    sampler2D diffuse;
    sampler2D speclar;
    float shininess;
};

struct LightPoint
{
    float constant;
    float linear;
    float quadratic;
};

uniform Material material;
uniform LightPoint lightP;
uniform vec3 objColor;
uniform vec3 ambientColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 lightDir;
uniform vec3 cameraPos;

in vec3 fragPos;
in vec3 fNormal;
in vec2 fTexCoord;

out vec4 fragColor;

void main()
{

    float distance = length(lightPos - fragPos);
    float attenuation = 1.0f / (lightP.constant + lightP.linear*distance +lightP.quadratic*(distance*distance));
//    vec3 ambient = ambientColor*lightColor;
    vec3 lightDire = normalize(lightPos-fragPos);
    vec3 reflectVec = reflect(-lightDire,fNormal);
    vec3 cameraVec = normalize(cameraPos-fragPos);

    //! specular;
    float specularAmount = pow(max(dot(reflectVec,cameraVec),0),material.shininess);
    vec3 spcular = texture(material.speclar,fTexCoord).rgb*specularAmount*lightColor;

    //! diffuse
    //vec3 diffuse = material.diffuse*max(dot(lightDire,fNormal),0)*lightColor;
    vec3 diffuse = texture(material.diffuse,fTexCoord).rgb*max(dot(lightDire,fNormal),0)*lightColor;
    //! ambient
    vec3 ambientVec = texture(material.diffuse,fTexCoord).rgb * ambientColor;

    fragColor = vec4(((spcular+diffuse)*attenuation+ambientVec)*objColor,1.0f);// vec4(diffuse*objColor+ambientVec*objColor+spcular*objColor,1.0f);

}
