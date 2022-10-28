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


protected:

    //Own particle
    Particle* particle;
    ParticleSpring* springPhysics;

    glm::vec3 anchorPos = glm::vec3(0);
};
