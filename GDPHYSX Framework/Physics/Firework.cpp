#include "Firework.h"


Firework::Firework() : Particle(){

}

Firework::~Firework() {
}

void Firework::updateFireworks(float deltaTime)
{
	this->updatePosition(deltaTime);

	this->age -= deltaTime;
	

}

unsigned int Firework::getType()
{
	return this->type;
}

int Firework::getAge()
{
	return this->age;
}

void Firework::setType(unsigned int type)
{
	this->type = type;
}

void Firework::setAge(int age)
{
	this->age = age;
}




