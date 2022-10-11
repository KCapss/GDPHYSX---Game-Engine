#pragma once
#include "Particle.h"

enum shotType {
    PISTOL,
    ARTILLERY,
    FIREBALL,
    LASER,
    FIREWORK,
    UNUSED
};

class Ballistic :
    public Particle
{
public:
    //using Particle::Particle;

    Ballistic();
    Ballistic(vec3 Pos, float mass);

    // Setter
    void setShotType(shotType chosenShotType);

    // Getter
    shotType getShotType();

    void updateBallistic();

private:
    shotType currentShotType = shotType::UNUSED;
};

