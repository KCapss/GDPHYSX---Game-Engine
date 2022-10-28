#pragma once

#include <vector>
#include "../Physics/Particle.h"
#include "ParticleForceGenerator.h"


class ParticleForceRegistry
{
protected:
	// Keepts track of force generator and particle it applies to
	struct ParticleForceRegistration
	{
		Particle* particle;
		ParticleForceGenerator* fg;
	};

	// holds the list of registrations
	typedef std::vector<ParticleForceRegistration> Registry;
	Registry registrations;

public:
	
	// Registers force generator to particle
	void add(Particle* particle, ParticleForceGenerator* fg);

	// Removes pair from registry. If not registered, this method will have no effect.
	void remove(Particle* particle, ParticleForceGenerator* fg);

	//  Clears the connection of pairs from registry. 
	void clear();

	// Calls updateForces of all force generators to their corresponding particles.
	void updateForces(float deltaTime);
};

