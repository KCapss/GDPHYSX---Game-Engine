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


    //Check for intersection
    bool isParticleInside(vec3 pointPos);


protected:
    float length = 20.0f; //fixed dimenstion in ...
    


private:
    

};

