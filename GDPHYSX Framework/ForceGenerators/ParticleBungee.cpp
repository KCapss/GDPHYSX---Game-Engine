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

	/*std::cout << "Initial Force x: " << force.x <<
		"y: " << force.y <<
		"z: " << force.z << std::endl;*/

	// Check if the bungee is compressed
	float magnitude = glm::length(force);
	if (magnitude <= restLength) return;

	// Calculate the magnitude of the force
	magnitude = springConstant * abs(restLength - magnitude);

	// Calculate final force and apply it
	force = glm::normalize(force);
	force *= -magnitude;
	particle->addForce(force);
}
