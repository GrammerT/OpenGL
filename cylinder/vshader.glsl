#version 330
#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

attribute vec3 VertexNormal;
attribute vec3 VertexPosition;


uniform vec4 LightPosition; // Light position in eye coords.
uniform vec3 Kd;            // Diffuse reflectivity
uniform vec3 Ld;            // Diffuse light intensity

uniform mat4 p_matrix;
uniform mat4 m_matrix;
uniform mat4 v_matrix;
uniform mat3 n_matrix;//! 传入应该归一化


out vec3 LightIntensity;

//! [0]
void main()
{
    // Calculate vertex position in screen space
    vec3 tNormal = normalize(n_matrix * VertexNormal);
    vec4 eyeCoords = v_matrix*m_matrix*vec4(VertexPosition,1.0f);
    vec3 direction = normalize(vec3(LightPosition-eyeCoords));
    LightIntensity = Ld*Kd*max(dot(direction,tNormal),0.0);

    gl_Position = p_matrix *v_matrix* m_matrix * vec4(VertexPosition,1.0);
    // Pass texture coordinate to fragment shader
}
//! [0]


