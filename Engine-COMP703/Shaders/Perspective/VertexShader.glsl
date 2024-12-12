// Vertex Shader
attribute vec3 a_Position;
//attribute vec3 a_Normal;
attribute vec2 a_TexCoord;

uniform mat4 u_Projection;
uniform mat4 u_Viewing;

varying vec2 v_TexCoord;
//varying vec3 v_Normal;
//varying vec3 v_FragPos

void main() {
    gl_Position = u_Projection * vec4(a_Position.x, a_Position.y, a_Position.z - 10.0, 1.0);
    
    v_TexCoord = a_TexCoord;
    //v_Normal = normalize(
}