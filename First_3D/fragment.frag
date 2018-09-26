#version 430

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

in vec3 gNormal;
in vec3 FragPos;

out vec4 fragColor;

void main(void)
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 norm = normalize(gNormal);
    vec3 lightDir = normalize(lightPos-FragPos);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = diff*lightColor;

    vec3 result = (ambient+diffuse) * objectColor;
    fragColor = vec4(result,1.0);
//    fragColor = vec4(1.0,0.0,0.0,1.0);
}
