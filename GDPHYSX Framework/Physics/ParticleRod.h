#pragma once
#include "ParticleLink.h"
class ParticleRod :
    public ParticleLink
{
public:
    float length;

protected:
    virtual unsigned addContact (ParticleContact* contact,
        unsigned limit) const;

private:

};

