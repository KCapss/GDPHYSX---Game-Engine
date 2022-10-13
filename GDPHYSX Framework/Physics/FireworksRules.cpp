#include "FireworksRules.h"


FireworkRules::FireworkRules()
{

}

FireworkRules::~FireworkRules()
{
	//if (payloads != NULL) payloads;
}



void FireworkRules::setParameters(unsigned type, int minAge, int maxAge, glm::vec3 minVelocity, glm::vec3 maxVelocity, float damping)
{
	this->type = type;
	this->minAge = minAge;
	this->maxAge = maxAge;
	this->minVelocity = minVelocity;
	this->maxVelocity = maxVelocity;
	this->damp = damping;
}

void FireworkRules::init(unsigned payloadCount)
{
	FireworkRules::payloadCount = payloadCount;
	
	for (int i = 0; i < payloadCount; i++) {
		Payload* load = new Payload();
		payloads.push_back(load);
	}
	
}

void FireworkRules::create(Firework* firework, Firework* parent) const
{
		//firework->type = type;
		//firework -= (rand() % (maxAge - minAge)) + minAge;

		//glm::vec3 vel;
		//if (parent) {
		//	// The position and velocity are based on the parent.
		//	firework->setPosition(parent->getPosition());
		//	vel += parent->getVelocity();
		//}

		//else
		//{
		//	glm::vec3 start;
		//	int x = rand() % 3 - 1;
		//	start.x = 5.0f * x;
		//	firework->setPosition(start);
		//}

		//vel += vec3(rand() %10 - 5, rand() % 10 - 5, rand() % 10 - 5);
		//firework->setVelocity(vel);

		//// We use a mass of one in all cases (no point having fireworks
		//// with different masses, since they are only under the influence
		//// of gravity).
		//firework->setMass(1);

		//firework->setDamping(damp);

		//firework->setAcceleration(vec3(0,9.8f,0));
}



glm::vec3 FireworkRules::randomVector(glm::vec3 minVector, glm::vec3 maxVector)
{
	glm::vec3 randVector;
	float minX = 0, minY = 0, minZ = 0;
	float maxX = 0, maxY = 0, maxZ = 0;

	// Set minimum float 
	minX = minVector.x;
	minY = minVector.y;
	minZ = minVector.z;

	// Set maximum float 
	maxX = maxVector.x;
	maxY = maxVector.y;
	maxZ = maxVector.z;

	// Assign random floats to randVector
	randVector.x = minX + static_cast<float> (rand() / static_cast <float> (RAND_MAX / (maxX - minX)));
	randVector.y = minY + static_cast<float> (rand() / static_cast <float> (RAND_MAX / (maxY - minY)));
	randVector.z = minZ + static_cast<float> (rand() / static_cast <float> (RAND_MAX / (maxZ - minZ)));

	return randVector;

	// Source for getting randomized floats:
	// https://stackoverflow.com/questions/686353/random-float-number-generation
}
