#pragma once
#include "AnchorSpringObject.h"
#include "SpringObject.h"
#include "BungeeObject.h"
#include "../ForceGenerators/ParticleForceRegistry.h"

#include <vector>

class SpringParticleContainer
{
public:
	SpringParticleContainer(ParticleForceRegistry* pfGenReg);

	void loadAnchor(AnchorSpringObject* ASpring);
	void loadSpring(SpringObject* Spring);
	void loadBungee(BungeeObject* Bungee);

	//FireTrigger
	void fire(int i);

	//Update Position 
	void updateSpringContainer(float timeStep);

	//Draw Object
	void draw();

protected:
	
	std::vector<AnchorSpringObject*> ASpringList;
	std::vector<SpringObject*> SpringList;
	std::vector<BungeeObject*> BungeeList;

	ParticleForceRegistry* pfGenManager;


private:



};

