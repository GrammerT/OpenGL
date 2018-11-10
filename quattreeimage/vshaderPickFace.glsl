#ifdef GL_ES
// Set default precision to medium
precision highp int;
precision highp float;
#endif

uniform mat4 modelView;
uniform mat4 projection;

attribute vec3 VertexPosition;
attribute vec4 a_color;

varying vec4 v_color;


//! [0]
void main()
{
    gl_Position = projection * modelView * vec4(VertexPosition, 1.0f);
    v_color = a_color;
}
//! [0]
