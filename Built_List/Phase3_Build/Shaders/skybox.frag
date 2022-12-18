#version 330 core //Version

out vec4 FragColor; //Returns a Color

in vec3 texCoord;

uniform samplerCube skybox;

void main()
{
    FragColor = texture(skybox, texCoord);
}