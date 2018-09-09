#version 330
#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

//smooth in vec3 LightIntensity;
flat in vec3 LightIntensity;

out vec4 FragColor;
//! [0]
void main()
{
    FragColor = vec4(LightIntensity,1.0);
}
//! [0]

