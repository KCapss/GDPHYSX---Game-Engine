#pragma once
#include "../ForceGenerators/ParticleBungee.h"
#include "../Model.h"

//Reference
#include "ParticleObject.h"

class BungeeObject :
    public Model
{
public:
    BungeeObject(std::string name, ObjectType objType, GLFWwindow* currWindow);
    
    void init(Particle* other, float springConst, float restLength);


    void setStartPos(glm::vec3 Pos);
    //void retrieveSource(Light* light, PerspectiveCamera* perspCam, OrthographicCamera* orthoCam);


    void update(float timeStep);
    void draw();


protected:

    //Own particle
    Particle* particle; 
    ParticleBungee* bungeePhysics;

    glm::vec3 anchorPos = glm::vec3(0);
};

