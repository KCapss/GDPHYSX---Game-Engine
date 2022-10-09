#pragma once
#include "Model.h"
#include <string>

class Player :
    public Model
{
public:
    //Constructor
    Player(std::string name, GLFWwindow *window);
    void recomputeTransform();

    //switch
    void cameraSwitch();
    void lightSwitch();

    //Pre-Operation
    void loadObj();
    void loadTexture();
    void loadBuffer();

    //Computation
    void updateLightForward();
    
    //UpdateFunction
    void playerMovement();
    void updateCamera();
    void updateLight();

    void update();
    void draw(); //override base class draw()

private:
    const float SHIP_FORWARD_SPEED = 100.f;
    const float SHIP_ROTATION_SPEED = 0.3f;
    float camDistance;
    glm::mat4 shipTransform = glm::mat4(1.0f);


    //Special Parameters
    unsigned char* norm_bytes;
    GLuint normTexture = 0;


};

