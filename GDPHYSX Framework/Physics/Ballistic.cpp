#include "Ballistic.h"

Ballistic::Ballistic() : Particle()
{

}

Ballistic::Ballistic(vec3 Pos, float mass) : Particle(Pos, mass)
{

}

void Ballistic::setShotType(ShotTypes chosenShotType)
{
	switch (chosenShotType)
	{
		case PISTOL:
			this->setMass(2.0f);
			this->setVelocity(vec3(0.0f, 0.0f, 100.0f));
			this->setAcceleration(vec3(0.0f, -1.0f, 0.0f));
			this->setDamping(0.99f);
			break;
		case ARTILLERY:
			this->setMass(200.0f);
			this->setVelocity(vec3(0.0f, 100.0f, 40.0f));
			this->setAcceleration(vec3(0.0f, -40.0f, 0.0f));
			this->setDamping(0.99f);
			break;
		case FIREBALL:
			this->setMass(1.0f);
			this->setVelocity(vec3(0.0f, 0.0f, 30.0f));
			this->setAcceleration(vec3(0.0f, 5.6f, 0.0f));
			this->setDamping(0.9f);
			break;
		case LASER:
			this->setMass(0.1f);
			this->setVelocity(vec3(0.0f, 0.0f, 300.0f));
			this->setAcceleration(vec3(0.0f, 0.0f, 0.0f));
			this->setDamping(0.90f);
			break;
		case UNUSED:
			// Placeholder
			break;
	}

	this->currentShotType = chosenShotType; // set shot type
}

ShotTypes Ballistic::getShotType()
{
	return currentShotType;
}

void Ballistic::updateBallistic(float deltaTime)
{
	// Check how long object has been active by 
	// counting down age
	age = age - deltaTime;
}

float Ballistic::getAge() {
	return this->age;
}
