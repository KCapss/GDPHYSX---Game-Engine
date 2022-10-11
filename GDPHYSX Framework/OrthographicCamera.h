#pragma once
#include "Camera.h"
class OrthographicCamera :
    public Camera
{
public:
    //Constructor && Destructor
    OrthographicCamera();

    //Getter Function
    glm::mat4 getProjection();

    //Update Function
    void updatePosition(glm::vec3 shipPos);

    //Update
    void camPanning(GLFWwindow* window, glm::vec3 shipPos);
    void camPanningReset();


private:
    float distance = 0;
    const float PANNING_SPEED = 1.0f;
    float xOffset = 0, zOffset = 0;


    glm::mat4 projection;
};

