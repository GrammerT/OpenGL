#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

in vec3 LightIntensity;

out vec4 FragColor;
//! [0]
void main()
{
    FragColor = vec4(LightIntensity,1.0);
}
//! [0]

