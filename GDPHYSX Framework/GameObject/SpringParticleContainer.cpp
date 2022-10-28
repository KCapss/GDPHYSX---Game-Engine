#include "SpringParticleContainer.h"



SpringParticleContainer::SpringParticleContainer(ParticleForceRegistry* pfGenReg)
{
	this->pfGenManager = pfGenReg;
}

void SpringParticleContainer::loadAnchor(AnchorSpringObject* ASpring)
{
	this->pfGenManager->add(ASpring->particle, (ParticleForceGenerator*)ASpring->aSpringPhysics);
	ASpring->setActive(false);
	this->ASpringList.push_back(ASpring);
}

void SpringParticleContainer::loadSpring(SpringObject* Spring)
{
	this->pfGenManager->add(Spring->particle, (ParticleForceGenerator*)Spring->springPhysics);
	Spring->setActive(false);
	this->SpringList.push_back(Spring);
}

void SpringParticleContainer::loadBungee(BungeeObject* Bungee)
{
	this->pfGenManager->add(Bungee->particle, (ParticleForceGenerator*)Bungee->bungeePhysics);
	Bungee->setActive(false);
	this->BungeeList.push_back(Bungee);
}

void SpringParticleContainer::fire(int i)
{
	switch (i) {

	//Normal Spring
	case 6:
		for (int i = 0; i < SpringList.size(); i++) {
			if (!SpringList[i]->isSetActive()) {

				SpringList[i]->reset();
				break;
			}
		}
		break;
	//Anchored
	case 7:
		for (int i = 0; i < ASpringList.size(); i++) {
			if (!ASpringList[i]->isSetActive()) {

				ASpringList[i]->reset();
				break;
			}
		}
		break;

	//Bungee
	case 8:
		for (int i = 0; i < BungeeList.size(); i++) {
			if (!BungeeList[i]->isSetActive()) {

				BungeeList[i]->reset();
				break;
			}
		}

		break;
	}

}

void SpringParticleContainer::updateSpringContainer(float timeStep)
{
	for (int i = 0; i < SpringList.size(); i++) {
		if (SpringList[i]->isSetActive()) {
			//Check if expired	
				SpringList[i]->update(timeStep);
		}
	}

	for (int i = 0; i < ASpringList.size(); i++) {
		if (ASpringList[i]->isSetActive()) {
			//Check if expired	
			ASpringList[i]->update(timeStep);
		}
	}

	for (int i = 0; i < BungeeList.size(); i++) {
		if (BungeeList[i]->isSetActive()) {
			//Check if expired	
			BungeeList[i]->update(timeStep);
		}
	}


}

void SpringParticleContainer::draw()
{
	for (int i = 0; i < SpringList.size(); i++) {
		if (SpringList[i]->isSetActive()) {
			
			SpringList[i]->draw();
		}
	}

	for (int i = 0; i < ASpringList.size(); i++) {
		if (ASpringList[i]->isSetActive()) {
			
			ASpringList[i]->draw();
		}
	}

	for (int i = 0; i < BungeeList.size(); i++) {
		if (BungeeList[i]->isSetActive()) {
			
			SpringList[i]->draw();
		}
	}
}
