#pragma once
#include "Particle.h"
class Firework : public Particle
{
public:
	Firework();
	~Firework();

	unsigned type; //Fireworks types
	
	//Methods
	bool updateFireworks(float deltaTime);
	int age; // Default

protected:

private:

};
