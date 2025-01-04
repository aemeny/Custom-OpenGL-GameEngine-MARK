// Vertex Shader

// Matrices
uniform mat4 u_Projection;
uniform mat4 u_Viewing;
uniform mat4 u_Model;

// Passed Attributes
attribute vec3 a_Position;
attribute vec2 a_TexCoord;

// Fragment Passed variables
varying vec2 v_TexCoord;

void main()
{
    gl_Position = u_Projection * u_Viewing * u_Model * vec4(a_Position, 1.0);
    
    v_TexCoord = a_TexCoord;
}