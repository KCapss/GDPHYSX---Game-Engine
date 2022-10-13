#pragma once
#include "Particle.h"
class Firework : public Particle
{
public:
	Firework();
	~Firework();

//Methods
	void updateFireworks(float deltaTime);
	
	//Getters
	unsigned int getType();
	int getAge();

	//Setters
	void setType(unsigned int type);
	void setAge(int age);


private:
	unsigned int type = 0; //Fireworks types
	int age = 0; // Default



};
