#pragma once
#include "Particle.h"
class Ballistic :
    public Particle
{
public:
    //using Particle::Particle;

    Ballistic();
    Ballistic(vec3 Pos, float mass);
    

    // Properties
    enum shotType {
        PISTOL,
        ARTILLERY,
        FIREBALL,
        LASER,
        FIREWORK
    };

    // Setter
    void setShotType(shotType currentShotType);

private:
 
};

