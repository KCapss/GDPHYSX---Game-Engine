#include "Camera.h"

//Default Constructor
Camera::Camera()
{
    this->cameraPos = glm::vec3(0, 0, -30.0f);
    this->WorldUp = glm::vec3(0, 1.0f, 0);
    this->Center = glm::vec3(0, 0, 0);

    this->viewMatrix = glm::mat4(1.0f);
    updateCamera();
}

//Camera Update
void Camera::updateCamera()
{
   
    glm::mat4 cameraPositionMatrix = glm::translate(glm::mat4(1.0f),
        cameraPos * -1.0f);

    //Option 1 = Manual Computation
    glm::vec3 F = glm::normalize(glm::vec3(Center - cameraPos));
    glm::vec3 R = glm::normalize(glm::cross(F, WorldUp));
    glm::vec3 U = (glm::cross(R, F));

    glm::mat4 cameraOrientation = glm::mat4(
        glm::vec4(R, 0),
        glm::vec4(U, 0),
        glm::vec4(F * -1.0f, 0),
        glm::vec4(glm::vec3(0, 0, 0), 1.0f));
    cameraOrientation = glm::transpose(cameraOrientation);
    this->viewMatrix = cameraOrientation * cameraPositionMatrix;
   
}
//Getter
glm::vec3 Camera::getCameraPos()
{
    return this->cameraPos;
}

glm::mat4 Camera::getViewMatrix()
{
    return this->viewMatrix;
}


