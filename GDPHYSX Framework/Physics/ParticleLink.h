#pragma once
#include "Particle.h"
#include "ParticleContact.h"

class ParticleLink: public ParticleContact
{
public:
	//Members
	Particle* particle[2];

	//Function
	virtual unsigned addContact(ParticleContact* contact,
		unsigned limit) const = 0;
protected:
	//Defaul Function
	float currentLength() const;
	


};

