#include "ParticleForceRegistry.h"

void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* fg)
{
	ParticleForceRegistration registration;
	registration.particle = particle;
	registration.fg = fg;
	registrations.push_back(registration);
}

void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* fg)
{
	for (int i = 0; i < registrations.size(); i++)
	{
		if (registrations[i].particle == particle && registrations[i].fg == fg)
		{
			Registry::iterator it;
			it = registrations.begin() + i;
			registrations.erase(it);
			return; // go back if found
		}
	}
}

void ParticleForceRegistry::clear()
{
	registrations.clear();
}

void ParticleForceRegistry::updateForces(float deltaTime)
{
	for (int i = 0; i < registrations.size(); i++)
	{
		registrations[i].fg->updateForce(registrations[i].particle, deltaTime);
	}
}
