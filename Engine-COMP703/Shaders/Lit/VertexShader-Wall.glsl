// Vertex Shader

// Matrices
uniform mat4 u_Projection;
uniform mat4 u_Viewing;
uniform mat4 u_Model;

// Passed Attributes
attribute vec3 a_Position;
attribute vec3 a_Normal;
attribute vec2 a_TexCoord;

// Fragment Passed variables
varying vec2 v_TexCoord;
varying vec3 v_Normal;
varying vec3 v_FragPos;

void main()
{
    gl_Position = u_Projection * u_Viewing * u_Model * vec4(a_Position, 1.0);
    
    vec2 tilingFactor = vec2(1, 7);
    v_TexCoord = a_TexCoord * tilingFactor;

    v_Normal = normalize(mat3(u_Model) * a_Normal);
    v_FragPos = vec3(u_Model * vec4(a_Position, 1.0));
}