#version 330 core //Version Number

layout(location = 0) in vec3 aPos; 
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 aTex;

out vec2 texCoord;
out vec3 normCoord;
out vec3 fragPos;

uniform mat4 transform;
uniform mat4 projection;
uniform mat4 view;

void main()
{
    gl_Position = projection * view * transform * vec4(aPos, 1); 
    
    texCoord = aTex;

    normCoord = mat3(transpose(inverse(transform)) ) * vertexNormal;
    fragPos = vec3(transform * vec4(aPos, 1.0f));
    }