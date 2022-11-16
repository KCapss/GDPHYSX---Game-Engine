#include "ParticleContact.h"

ParticleContact::ParticleContact(Particle* particle1, Particle* particle2)
{
	particle[0] = particle1;
	particle[1] = particle2;

	contactNormal = glm::normalize(particle[0]->getVelocity());
	restitution = 1.0f; // temporarily all objects same material
}

void ParticleContact::resolve(float deltaTime)
{
	resolveVelocity(deltaTime);
}

float ParticleContact::calculateSeparatingVelocity() const
{
	glm::vec3 relativeVelocity = particle[0]->getVelocity();
	if (particle[1]) relativeVelocity -= particle[1]->getVelocity();
	return glm::dot(relativeVelocity, contactNormal);
}

void ParticleContact::resolveVelocity(float duration)
{
	float separatingVelocity = calculateSeparatingVelocity();
	if (separatingVelocity > 0)
	{
		// contact is separating / stationary, no impulse required
		return;
	}

	float newSepVelocity = -separatingVelocity * restitution;

	float deltaVelocity = newSepVelocity - separatingVelocity;

	// apply deltaVelocity to each object in proportion to its inverse mass
	float totalInverseMass = particle[0]->getInverseMass();
	if (particle[1]) totalInverseMass += particle[1]->getInverseMass();

	// if all particles have infinite mass, impulse has no effect
	if (totalInverseMass <= 0) return;

	// calculate applied impulse
	float impulse = deltaVelocity / totalInverseMass;

	// find amount of impulse per unit of inverse mass
	glm::vec3 impulsePerIMass = contactNormal * impulse;
	// Apply impulses: applied in direction of contact, proportional to inverse mass
	particle[0]->setVelocity(particle[0]->getVelocity() + impulsePerIMass * particle[0]->getInverseMass());
	if (particle[1])
	{
		// particle 1 goes in opposite direction
		particle[1]->setVelocity(particle[1]->getVelocity() + impulsePerIMass * -particle[1]->getInverseMass());
	}
}







