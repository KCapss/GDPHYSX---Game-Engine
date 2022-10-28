#pragma once
#include "ParticleForceGenerator.h"

class ParticleSpring : public ParticleForceGenerator
{
private:
	// Particle at the other end of the spring (particle at initial point)
	Particle* other;

	// spring constant
	float springConstant;

	// rest length of spring (initial length)
	float restLength;

public:
	// constructor 
	ParticleSpring(Particle* other, float springConstant, float restLength);

	// applies spring force to given particle
	virtual void updateForce(Particle* particle, float deltaTime);
};

