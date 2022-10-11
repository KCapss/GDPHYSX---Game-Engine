#pragma once
#include "../Model.h"
#include "../Physics/Particle.h"

class ParticleObject: public Model, public Particle
{
public:
	//Constructor
	ParticleObject(std::string name, ObjectType objType, GLFWwindow* currWindow);

	
	
	void update(float timeStep);
	void draw();

private:

};

