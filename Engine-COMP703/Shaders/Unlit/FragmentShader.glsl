// Fragment Shader
uniform sampler2D u_Texture;

// Fragment Passed variables
varying vec2 v_TexCoord;
varying vec4 v_ClipSpacePosition;

void main() 
{
    // Convert clip-space position to normalized device coordinates (NDC)
    vec2 ndc = v_ClipSpacePosition.xy / v_ClipSpacePosition.w;

    // Map NDC to UV coordinates (0.0 to 1.0)
    vec2 screenUV = (ndc.xy + 1.0) * 0.5;

    // Sample the texture using the calculated UVs
    vec4 texColor = texture(u_Texture, screenUV);

    gl_FragColor = texColor;
}