#pragma once
#include "ParticleForceGenerator.h"

class ParticleGravity : ParticleForceGenerator
{
private:
	glm::vec3 gravity;

public:
	// creates generator w/ given acceleration
	ParticleGravity(const glm::vec3& gravity);

	// applies gravitational force
	virtual void updateForce(Particle* particle, float deltaTime);
};

