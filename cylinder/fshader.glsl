#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform vec3 lightPos;

uniform vec3 lightColor;
uniform vec3 objColor;


in vec3 FragPos;
in vec3 Normal;

out vec4 FragColor;
//! [0]
void main()
{
    //! 设置环境光
    float ambientStrength = 0.8f;
    vec3 ambient = ambientStrength * lightColor;
    //! 设置漫反射
    //! 漫反射强度是光线到物体的向量与物体表面向量的点乘
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos-FragPos);
    float diff = max(dot(norm,lightDir),0.0);
    vec3 diffuse = diff * lightColor;
    //! 最终光线为(环境光强+漫反射光强)与物体颜色的乘积
    vec3 result = (ambient+diffuse)*objColor;
    FragColor = vec4(result,1.0f);
}
//! [0]

