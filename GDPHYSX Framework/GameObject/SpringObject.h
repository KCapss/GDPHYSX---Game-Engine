#pragma once
#include "../Model.h"
#include "../ForceGenerators/ParticleSpring.h"

class SpringObject :
    public Model
{
public:
    SpringObject(std::string name, ObjectType objType, GLFWwindow* currWindow);

    void init(Particle* other, float springConst, float restLength);


    void setStartPos(glm::vec3 Pos);
    //void retrieveSource(Light* light, PerspectiveCamera* perspCam, OrthographicCamera* orthoCam);


    void update(float timeStep);
    void draw();
    void reset();

    Particle* particle;
    ParticleSpring* springPhysics;

protected:

    //Own particle
    float tick = 0;
    float maxTime = 1000.0f;

   
};

