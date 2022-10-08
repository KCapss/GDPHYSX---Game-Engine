#pragma once
#include "Particle.h"
class Ballistic :
    public Particle
{
public:
    using Particle::Particle;

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

