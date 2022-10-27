#include "ParticleAnchoredSpring.h"

ParticleAnchoredSpring::ParticleAnchoredSpring(glm::vec3* anchor, float springConstant, float restLength)
{
	this->anchor = anchor;
	this->springConstant = springConstant;
	this->restLength = restLength;

}

void ParticleAnchoredSpring::updateForce(Particle* particle, float deltaTime)
{
	// Calculate vector of spring
	glm::vec3 force = particle->getPosition();

	
	force -= * anchor;


	// Calculate magnitude of the force 
	float magnitude = glm::length(force);
	magnitude = abs(magnitude - restLength);
	magnitude *= springConstant;

	// Calculate final force and apply it
	force = glm::normalize(force);
	force *= -1.0 * magnitude;
	std::cout << "Force x: " << force.x <<
		"y: " << force.y <<
		"z: " << force.z << std::endl;

	particle->addForce(force);

	
	
}
