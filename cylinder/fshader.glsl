#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif
uniform vec4 Ambient;


in vec4 fColor;
out vec4 FragColor;
//! [0]
void main()
{
    vec4 scatteredLight = Ambient;
    FragColor = min(fColor*scatteredLight,vec4(1.0));
}
//! [0]

