#version 330 core //Version Number

layout(location = 0) in vec3 aPos; 

out vec3 texCoord;

uniform mat4 projection;
uniform mat4 view;

void main()
{
    vec4 pos = projection * view  * vec4(aPos, 1); 

  
    gl_Position = vec4(pos.x, pos.y, pos.w, pos.w);
    
    texCoord = aPos;
}