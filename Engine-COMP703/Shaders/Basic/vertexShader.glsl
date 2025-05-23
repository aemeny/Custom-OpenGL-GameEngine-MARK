attribute vec3 a_Position;            

uniform mat4 u_Projection;    
uniform mat4 u_Viewing;
                               
void main()                            
{                                      
    gl_Position = u_Projection * u_Viewing * vec4(a_Position, 1.0);
}                             
                                       