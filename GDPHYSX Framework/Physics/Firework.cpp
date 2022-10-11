#include "Firework.h"

Firework::Firework() : Particle()
{
}

Firework::~Firework() {
}

bool Firework::updateFireworks(float deltaTime)
{
	this->updatePosition(deltaTime);

	this->age -= deltaTime;
	return (age < 0);

}

void Firework::initFireworkRules()
{
	//Fill up the details
	
	
}
