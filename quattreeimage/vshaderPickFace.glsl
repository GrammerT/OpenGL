#ifdef GL_ES
// Set default precision to medium
precision highp int;
precision highp float;
#endif

attribute vec3 VertexPosition;
attribute vec4 FaceColor;

varying vec4 v_color;

uniform mat4 modelView;
uniform mat4 projection;

//! [0]
void main()
{
    gl_Position = projection * modelView * vec4(VertexPosition, 1.0f);
    v_color = FaceColor;
}
//! [0]
