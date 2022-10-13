#pragma once
#include "Model.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
class Skybox :
    public Model
{
public:
    Skybox(std::string name);
    void loadValues();

    void loadTexture();
    void loadBuffer();


    void update();
    void draw();
    void deAllocate();



private:
    unsigned int skyVAO = 0, skyVBO = 0, skyEBO = 0;
    unsigned int skyboxTex;

private:
    //Vertices for the cube
    float skyboxVertices[24];

    //Skybox Indices
    unsigned int skyboxIndices[36];
    
    //skyboxface
    std::string faceSkybox[6];

private:
    //Class Container
    Shader* shader;
    
};

