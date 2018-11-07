#ifdef GL_ES
// Set default precision to medium
precision highp int;
precision highp float;
#endif

varying vec4 v_color;

//! [0]
void main()
{
    gl_FragColor = v_color;
}
//! [0]

