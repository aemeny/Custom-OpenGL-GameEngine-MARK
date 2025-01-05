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
    vec4 clipPos = u_Projection * u_Viewing * u_Model * vec4(a_Position, 1.0);
    gl_Position = clipPos;
    
    v_TexCoord = vec2((a_TexCoord.x * (2.0/3.75)) + 0.2, a_TexCoord.y * (2.0/3.75));
    //v_TexCoord = a_TexCoord;
}