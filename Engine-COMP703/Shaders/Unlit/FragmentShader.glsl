// Fragment Shader
uniform sampler2D u_Texture;

// Fragment Passed variables
varying vec2 v_TexCoord;

void main() 
{
    vec4 texColor = texture2D(u_Texture, v_TexCoord);
    gl_FragColor = texColor;
}