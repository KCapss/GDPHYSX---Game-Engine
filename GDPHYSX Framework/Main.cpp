#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "Space.h"
#include <string>
#include <iostream>

using namespace std;


int main(void)
{
   Space* space = new Space(1280, 720);
   int frameLimit = 60;
   const float timePerFrame = 1 / (float)frameLimit;

   //Debug
   int frameCount = 0;
    
    if (space->initializeWindow()) {
        return 0;
    }

    float timeSinceLastUpdate = glfwGetTime(), timer = timeSinceLastUpdate;
    float deltaTime = 0, nowTime = 0;
    int frames = 0, updates = 0;

    space->initializeObj();


    while (!glfwWindowShouldClose(space->window))
    {
        nowTime = glfwGetTime();
        deltaTime += (nowTime - timeSinceLastUpdate) / timePerFrame;
        timeSinceLastUpdate = nowTime;
        frameCount = 0;

        //Creating Fixed Time Step
        while (deltaTime >= 1.0f) {
          
            
            //Process Events
            
            //Update Data Function Call
            space->update(timePerFrame);
            updates++;
            deltaTime--;
            frameCount++;
        }
      

        //Draw Function Call
        space->draw();
        
        //Debug
        //cout << "Frame: " << frameCount << endl;
        frames++;

        // - Reset after one second
        if (glfwGetTime() - timer > 1.0) {
            timer++;
            //std::cout << "FPS: " << frames << " Updates:" << updates << std::endl;
            updates = 0, frames = 0;
        }
    }

    //de-allocate any remaining
    space->deleteBuffer();
   
    return 0;


}