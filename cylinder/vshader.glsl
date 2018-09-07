#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

attribute vec3 VertexNormal;
attribute vec3 VertexPosition;


uniform mat4 p_matrix;
uniform mat4 m_matrix;
uniform mat4 v_matrix;

out vec3 FragPos;
out vec3 Normal;

//! [0]
void main()
{
    // Calculate vertex position in screen space
    gl_Position = p_matrix *v_matrix* m_matrix * vec4(VertexPosition,1.0);
    FragPos = vec3(m_matrix*vec4(VertexPosition,1.0f));
    Normal = VertexNormal;
    // Pass texture coordinate to fragment shader
}
//! [0]


