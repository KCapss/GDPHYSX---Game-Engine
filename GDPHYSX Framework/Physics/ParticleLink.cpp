#include "ParticleLink.h"
#include <iostream>

using namespace std;

ParticleLink::ParticleLink() : ParticleContact()
{

}

float ParticleLink::currentLength() const
{
	//Get the magnitude of two connected particle
	glm::vec3 particleDiff = particle[0]->getPosition() - particle[1]->getPosition();

	//cout << "Lenght: " << particleDiff.length() << endl;
	return particleDiff.length();
}
