#pragma once
#include "ParticleContact.h"
class ParticleContactGenerator : public ParticleContact
{
public:

    virtual unsigned addContact(ParticleContact* contact,
        unsigned limit) const = 0;


    //Needs a constructor
};

