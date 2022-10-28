#pragma once
#include "ParticleForceGenerator.h"

class ParticleAnchoredSpring : public ParticleForceGenerator
{
private:
	// location of anchored end of spring
	glm::vec3* anchor;

	// spring constant
	float springConstant;

	// rest length of spring (initial length)
	float restLength;

public:
	// constructor 
	ParticleAnchoredSpring(glm::vec3* anchor, float springConstant, float restLength);

	// applies spring force to given particle
	virtual void updateForce(Particle* particle, float deltaTime);
};

