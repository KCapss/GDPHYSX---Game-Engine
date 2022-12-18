#version 330 core 

//uniform vec3 lightColor;

out vec4 FragColor; //Returns a Color

void main()
{
    
    FragColor = vec4(1.0f, 0.7f, 0.8f, 1.0f); //Same color as the lightSource or fade white if disabled;
}