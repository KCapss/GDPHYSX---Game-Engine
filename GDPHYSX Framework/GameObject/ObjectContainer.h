#pragma once
#include "../Physics/Particle.h"
#include <vector>
#include "../Physics/ParticleContact.h"
#include "RigidBodyObject.h"

using namespace std;

class ObjectContainer
{
public:
	void addParticle(Particle* particle);
	void addRBObject(RigidBodyObject* rgObj);

	void updateParticleContainer(float deltaTime);
	void updateRBObjContainer(float deltaTime);
	

	//Debugging
	float floorDepth = -8.5f;

private:
	vector<Particle*> particleContainer;
	vector<RigidBodyObject*> rigidBodyObjContainer;
	ParticleContact* particleContact;
};

