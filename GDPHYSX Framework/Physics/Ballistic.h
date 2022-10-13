#pragma once
#include "Particle.h"

enum ShotTypes {
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
    void setShotType(ShotTypes chosenShotType);
    void setAge(float age);

    // Getter
    ShotTypes getShotType();
    float getAge();


    void updateBallistic(float deltaTime);

private:
    ShotTypes currentShotType = ShotTypes::UNUSED;
    float age = 500; // particle can only last 500 seconds 

};

