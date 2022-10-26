#pragma once
#include "../Model.h"
#include "../ForceGenerators/ParticleAnchoredSpring.h"
class AnchorSpringObject :
    public Model
{
public:
    AnchorSpringObject(std::string name, ObjectType objType, GLFWwindow* currWindow);
    //~AnchorSpringObject();

    void update(float timeStep);
    void draw();
    

protected:

    ParticleAnchoredSpring* aSpring;
    Particle* particle;

    glm::vec3 anchorPos = glm::vec3(0);

private:
};

