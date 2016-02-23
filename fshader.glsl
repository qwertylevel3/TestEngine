#ifdef GL_ES
// Set default precision to medium
precision mediump int;
precision mediump float;
#endif

uniform sampler2D texture;
uniform float alpha;

varying vec2 v_texcoord;

//! [0]
void main()
{
    // Set fragment color from texture
    vec4 v=vec4(1.0,1.0,1.0,alpha);
    gl_FragColor = texture2D(texture, v_texcoord)*v;
}
//! [0]

