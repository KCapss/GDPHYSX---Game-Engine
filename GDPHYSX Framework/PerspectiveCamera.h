#pragma once
#include "Camera.h"
class PerspectiveCamera :
    public Camera
{
public:
    PerspectiveCamera(float width, float height);
    glm::mat4 getProjection();

    //UpdateFunctio
    void RotateCam(GLFWwindow *window, glm::mat4 shipPosTransformMat); //only applies on perspective
    void newCamPos(glm::mat4 shipPosTransformMat);

private:
    bool rotateActive = false;
    glm::mat4 projection;
    float distance;


    glm::vec3 d_camRotate = glm::vec3(0);

   

    float camSensitivity = 0.20f;

    double xCamCurrPos = 0, yCamCurrPos = 0;
    float lastX = 800 / 2.0f;  // starting last position of the mouse
    float lastY = 800 / 2.0f; // starting last position of the mouse


    
    bool onXplane = false;

    //Rotation Based on which axis
    float x = 0, y = 0, z = 0;
    float xOffset = 90.0f;

};


