#pragma once
#include "../Physics/RigidBody.h"
#include "../Model.h"


class RigidBodyObject : 
    public RigidBody, public Model
{
public:
    RigidBodyObject(std::string name, ObjectType objType, GLFWwindow* currWindow);

    void update(float timeStep);
    void draw();


protected:
    float length; //fixed dimenstion in ...
    


private:


};

