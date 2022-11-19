#pragma once
#include "ParticleLink.h"
class ParticleRod :
    public ParticleLink
{
public:
    //ParticleRod(Particle p1, Particle p2);
    float length = 10.0f;

protected:
    virtual unsigned addContact (ParticleContact* contact,
        unsigned limit) const;

private:

};

