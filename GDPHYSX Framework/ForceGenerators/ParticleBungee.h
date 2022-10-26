#pragma once
#include "../Physics/Particle.h"

class ParticleBungee
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
	ParticleBungee(Particle* other, float springConstant, float restLength);

	// applies spring force to given particle
	virtual void updateForce(Particle* particle, float deltaTime);
};

