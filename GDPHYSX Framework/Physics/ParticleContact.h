#pragma once
#include "Particle.h"
class ParticleContact
{
public:
	ParticleContact(Particle* particle1, Particle* particle2);

	// Holds particles involved in contact
	Particle* particle[2];

	// holds normal restitution coefficient
	float restitution;

	// holds direction of contact in world coordinates
	glm::vec3 contactNormal;

	// Resolves contact for both velocity and interpenetration
	void resolve(float deltaTime);

	// holds depth of penetration of contact
	float penetration;

protected:
	// Calculates seperating velocity at contact
	float calculateSeparatingVelocity() const;

private:
	// Handles impulse calculations for this collision
	void resolveVelocity(float deltaTime);

	// Handles interpentration resultion for this contacrt
	void resolveInterpenetration(float deltaTime);
};

