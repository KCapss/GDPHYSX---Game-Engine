#version 330 core 

out vec4 FragColor; //Returns a Color
//Simple shader that colors the model Red
void main()
{
    //               r   g   b   a     Ranges from 0->1
    FragColor = vec4(0.0f, 0.0f, 0.9f, 1.0f); //Sets the color of the Fragment
}