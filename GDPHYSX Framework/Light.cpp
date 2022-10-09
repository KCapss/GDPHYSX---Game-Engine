#include "Light.h"
#include <iostream>

using namespace std;

//Constructor with predefined value
Light::Light(glm::vec3 objPos)
{
    //Attributes
    this->lightPos = glm::vec3(10, 0, -10); //default 
    this->lightColor = glm::vec3(0.9f, 0.9f, 0.9f);

    this->ambientStr = 0.3f;
    this->ambientColor = lightColor; // can be customizable

    this->specStr = 1.5f;
    this->specPhong = 60.20f;

    //Parts
    this->speed = 200.0f;
    this->distance = 10.f;
    this->lightRotation = glm::normalize(lightPos);

   

    //Special Properties
    this->lumens = 10000000.0f;

}


//Getter Function
glm::vec3 Light::getLightPos()
{
    return this->lightPos;
}

glm::vec3 Light::getLightColor()
{
    return this->lightColor;
}

float Light::getAmbientStr()
{
    return this->ambientStr;
}

glm::vec3 Light::getAmbientColor()
{
    return this->ambientColor;
}

float Light::getSpecStr()
{
    return this->specStr;
}

float Light::getSpecPhong()
{
    return this->specPhong;
}

float Light::getLumens()
{
    return this->lumens;
}

void Light::setLightPos(glm::vec3 newLightPos)
{
    this->lightPos = newLightPos;
}

void Light::setLumens(float lumens)
{
    this->lumens = lumens;
}



