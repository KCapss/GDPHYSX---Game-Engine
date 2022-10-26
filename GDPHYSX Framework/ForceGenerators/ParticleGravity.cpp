#include "ParticleGravity.h"

ParticleGravity::ParticleGravity(const glm::vec3& gravity)
{
	this->gravity = gravity;
}

void ParticleGravity::updateForce(Particle* particle, float deltaTime)
{
	// Check that we do not have infinite mass
	if (!particle->hasFiniteMass()) return;

	// Apply mass-scaled force to particle
	particle->addForce(gravity * particle->getMass());
}
