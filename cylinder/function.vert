#version 330
#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

attribute vec3 VertexPosition;
attribute vec3 VertexNormal;

flat out vec3 LightIntensity;

struct LightInfo {
  vec4 Position; // Light position in eye coords.
  vec3 LightAmbint;       // Ambient light intensity 环境光强度
  vec3 LightDiffuse;       // Diffuse light intensity     漫射光强度
  vec3 LightSpecular;       // Specular light intensity  镜面光强度
};
uniform LightInfo Light;

struct MaterialInfo {
  vec3 RateAmbient;            // Ambient reflectivity  环境光反射率
  vec3 RateDiffuse;            // Diffuse reflectivity 漫反射率
  vec3 RateSpecular;            // Specular reflectivity 镜面反射率
  float Shininess;    // Specular shininess factor 镜面光泽因子
};
uniform MaterialInfo Material;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;

void getEyeSpace( out vec3 norm, out vec4 position )
{
    norm = normalize( NormalMatrix * VertexNormal);
    position = ModelViewMatrix * vec4(VertexPosition,1.0);
}

vec3 phongModel( vec4 position, vec3 norm )
{
    vec3 s = normalize(vec3(Light.Position - position));//! 模型点到灯光的向量
    vec3 v = normalize(-position.xyz);  //! 对上面的向量取反方向
    vec3 r = reflect( -s, norm ); //! s 的反射向量
    vec3 ambient = Light.LightAmbint * Material.RateAmbient;//! 环境光强度*环境光反射率
    float sDotN = max( dot(s,norm), 0.0 ); //! 求出光照和向量的夹角cos值
    vec3 diffuse = Light.LightDiffuse * Material.RateDiffuse * sDotN; //! 漫反射光强度*漫反射率*cos值-->光强
    vec3 spec = vec3(0.0);
    if( sDotN > 0.0 )
        spec = Light.LightSpecular * Material.RateSpecular *
               pow( max( dot(r,v), 0.0 ), Material.Shininess );//! 计算镜面光强

    return ambient + diffuse + spec; //! 综合光照信息就是三者之和
}

void main()
{
    vec3 eyeNorm;
    vec4 eyePosition;

    // Get the position and normal in eye space
    getEyeSpace(eyeNorm, eyePosition);

    // Evaluate the lighting equation.
    LightIntensity = phongModel( eyePosition, eyeNorm );

    gl_Position = MVP * vec4(VertexPosition,1.0);
}
