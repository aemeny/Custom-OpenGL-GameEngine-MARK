// Fragment Shader
uniform sampler2D u_Texture;
//uniform vec3 u_ViewPos;

varying vec2 v_TexCoord;
//varying vec3 v_Normal;
//varying vec3 v_FragPos

void main() {
    vec4 texColor = texture2D(u_Texture, v_TexCoord);

    gl_FragColor = texColor;
}