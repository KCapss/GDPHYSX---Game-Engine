#pragma once
#include "../Physics/Particle.h"
#include <vector>
#include "../Physics/ParticleContact.h"

using namespace std;

class ObjectContainer
{
public:
	void addParticle(Particle* particle);
	void updateParticleContainer(float deltaTime);

	//Debugging
	float floorDepth = -8.5f;

private:
	vector<Particle*> particleContainer;
	ParticleContact* particleContact;
};

