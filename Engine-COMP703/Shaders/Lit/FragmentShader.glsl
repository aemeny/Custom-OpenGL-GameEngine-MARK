// Fragment Shader
uniform sampler2D u_Texture;
uniform vec3 u_ViewPos;

// Fragment Passed variables
varying vec2 v_TexCoord;
varying vec3 v_Normal;
varying vec3 v_FragPos;

void main() 
{
    // Basic predefined variables
    vec3 lightPos = vec3(2, 5, 0);
    vec3 ambientColor = vec3(0.4, 0.4, 0.4);
    vec3 diffuseColor = vec3(1, 1, 1);
    vec3 specularColor = vec3(1, 1, 1);

    // Calculate Diffuse
    vec3 norm = normalize(v_Normal);
    vec3 lightDir = normalize(lightPos - v_FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diffuseColor * diff;

    // Calculate Specular
    vec3 viewDir = normalize(u_ViewPos - v_FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = specularColor * spec;

    // Calculate Ambient
    vec3 ambient = ambientColor; // Simple ambient light

    // Apply lighting with texture colour
    vec4 texColor = texture2D(u_Texture, v_TexCoord);
    vec3 lighting = ambient + diffuse + specular;
    gl_FragColor = vec4(lighting, 1.0) * texColor;
}