#include "ParticleBungee.h"

ParticleBungee::ParticleBungee(Particle* other, float springConstant, float restLength)
{
	this->other = other;
	this->springConstant = springConstant;
	this->restLength = restLength;
}

void ParticleBungee::updateForce(Particle* particle, float deltaTime)
{
	// Calculate vector of spring
	glm::vec3 force = particle->getPosition();
	force -= other->getPosition();

	// Check if the bungee is compressed
	float magnitude = glm::length(force);
	if (magnitude <= restLength) return;

	// Calculate the magnitude of the force
	magnitude = springConstant * (restLength - magnitude);

	// Calculate final force and apply it
	force = glm::normalize(force);
	force *= -1.0 * magnitude;
	particle->addForce(force);
}
