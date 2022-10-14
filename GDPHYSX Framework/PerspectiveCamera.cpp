#include "PerspectiveCamera.h"
#include <cmath>

PerspectiveCamera::PerspectiveCamera(float width, float height)
{
    this->lastX = width / 2.f;
    this->lastY = height / 2.f;


    //Camera Setup
    this->projection = glm::perspective(glm::radians(60.0f),
        width / height,
        0.01f,
        1000000.0f);

    this->distance = 10.0f;
    this->cameraPos = glm::vec3(0, 0, -distance);
   
    updateCamera();

}

glm::mat4 PerspectiveCamera::getProjection()
{
    return this->projection;
}

void PerspectiveCamera::RotateCam(GLFWwindow* window, glm::mat4 shipPosTransformMat)
{
    // Changed mouse pannning to right click
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {

        //CurrentCam Pos
        double xPos, yPos;
        glfwGetCursorPos(window, &xPos, &yPos);

        if (!this->rotateActive)
        {
            lastX = xPos;
            lastY = yPos;
            this->rotateActive = true;
        }

        //Compared to Last Check
        float xoffset = xPos - lastX;
        float yoffset = lastY - yPos;
        lastX = xPos;
        lastY = yPos;

        float sensitivity = this->camSensitivity;
        xoffset *= sensitivity;
        yoffset *= sensitivity;

        //Any Offset will increment
        x += xoffset;
        y += yoffset;

        //Preventing Rotating in Vertical Manner
        if (y > 89.0f)
            y = 89.0f;
        if (y < -89.0f)
            y = -89.0f;

        //Simplified Rotation
        direction.x = cos(glm::radians(x + -90.f)) * cos(glm::radians(y));
        direction.y = sin(glm::radians(y));
        direction.z = sin(glm::radians(x + -90.f)) * cos(glm::radians(y));

        //gett the new rotation based on ship position and its distance
        glm::mat4 camTransform = glm::translate(shipPosTransformMat, -direction * distance);
        camTransform = glm::translate(camTransform, glm::vec3(0, 1, 0) * (distance / 3.0f));
        this->cameraPos = glm::vec3(camTransform * glm::vec4(0, 0, 0, 1));
        
        glm::mat4 centerTransform = glm::translate(shipPosTransformMat, direction * distance / 2.f);
        this->Center = glm::vec3(centerTransform * glm::vec4(0, 0, 0, 1));
       
        
    }

    else {
        this->rotateActive = false;
    }
}

void PerspectiveCamera::newCamPos(glm::mat4 shipPosTransformMat)
{
    glm::mat4 camTransform = glm::translate(shipPosTransformMat, -direction * distance);
    camTransform = glm::translate(camTransform, glm::vec3(0, 1, 0) * (distance / 3.0f));
    this->cameraPos = glm::vec3(camTransform * glm::vec4(0, 0, 0, 1));

    glm::mat4 centerTransform = glm::translate(shipPosTransformMat, direction * distance / 2.f);
    this->Center = glm::vec3(centerTransform * glm::vec4(0, 0, 0, 1));

    updateCamera();
}


