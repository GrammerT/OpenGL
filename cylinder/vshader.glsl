#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform mat4 p_matrix;
uniform mat4 mv_matrix;
attribute vec4 a_position;
uniform vec4 vColor;
out vec4 fColor;
//varying vec2 v_texcoord;
//varying vec3 v_vertcoord;

//! [0]
void main()
{
    // Calculate vertex position in screen space
    fColor = vColor;
    gl_Position = p_matrix * mv_matrix * a_position;
    // Pass texture coordinate to fragment shader
}
//! [0]


