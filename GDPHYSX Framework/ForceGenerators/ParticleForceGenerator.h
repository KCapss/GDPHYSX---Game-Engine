#pragma once
#include "../Physics/Particle.h"

class ParticleForceGenerator
{
public:
	// unique updateForce per generator
	virtual void updateForce(Particle* particle, float duration) = 0;
};

