#pragma once
#include "../Physics/Particle.h"
#include <vector>

using namespace std;

class ObjectContainer
{
public:
	void addParticle(Particle* particle);
	void updateParticleContainer();

private:
	vector<Particle*> particleContainer;

};

