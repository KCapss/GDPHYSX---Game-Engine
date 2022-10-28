#pragma once
#include "../Model.h"
#include "../ForceGenerators/ParticleAnchoredSpring.h"
class AnchorSpringObject :
    public Model
{
public:
    AnchorSpringObject(std::string name, ObjectType objType, GLFWwindow* currWindow);
    //~AnchorSpringObject();

    void setStartPos(glm::vec3 Pos);
    void retrieveSource(Light* light, PerspectiveCamera* perspCam, OrthographicCamera* orthoCam);
  

    void update(float timeStep);
    void draw();

    void reset();
    
    Particle* particle;
    ParticleAnchoredSpring* aSpringPhysics;

protected:

    Model* refPoint;
    glm::vec3 anchorPos = glm::vec3(0);
    float tick = 0;
    float maxTime = 1000.0f;

private:
};

