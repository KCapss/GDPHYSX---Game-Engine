#include "ParticleContact.h"


ParticleContact::ParticleContact()
{
}

ParticleContact::ParticleContact(Particle* particle1, Particle* particle2)
{
	particle[0] = particle1;
	particle[1] = particle2;

	contactNormal = -1.0f * glm::normalize(particle[0]->getVelocity());
	restitution = 0.93f; // temporarily all objects same material
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

void ParticleContact::resolveVelocity(float deltaTime)
{
	float separatingVelocity = calculateSeparatingVelocity();
	if (separatingVelocity > 0 )
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
	std::cout << "Impulse" << impulse << std::endl;

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

void ParticleContact::resolveInterpenetration(float deltaTime)
{
	// If no penetration, skip step
	if (penetration <= 0) return;

	// Movement of each object is based on inverse mass, so total that
	float totalInverseMass = particle[0]->getInverseMass();
	if (particle[1]) totalInverseMass += particle[1]->getInverseMass();

	// If all particle have infinite mass, then do nothing
	if (totalInverseMass <= 0) return;

	// Find amount of penetration per unit of inverse mass.
	glm::vec3 movePerIMass = contactNormal * (-penetration / totalInverseMass);

	// Apply penetration resolution
	particle[0]->setPosition(particle[0]->getInverseMass() + movePerIMass * particle[0]->getInverseMass());
	if (particle[1])
	{
		particle[1]->setPosition(particle[1]->getPosition() + movePerIMass * particle[1]->getInverseMass());
	}

}







