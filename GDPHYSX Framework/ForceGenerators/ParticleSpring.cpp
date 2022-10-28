#include "ParticleSpring.h"

ParticleSpring::ParticleSpring(Particle* other, float springConstant, float restLength)
{
	this->other = other;
	this->springConstant = springConstant;
	this->restLength = restLength;
}

void ParticleSpring::updateForce(Particle* particle, float deltaTime)
{
	// Calculate vector of spring
	glm::vec3 force = particle->getPosition();

	/*std::cout << "Position x: " << force.x <<
		"y: " << force.y <<
		"z: " << force.z << std::endl;*/

	force -= other->getPosition();

	// Calculate magnitude of the force 
	float magnitude = glm::length(force);
	magnitude = abs(magnitude - restLength);
	magnitude *= springConstant;

	// Calculate final force and apply it
	force = glm::normalize(force);
	force *= -1.0 * magnitude;
	particle->addForce(force);
}



