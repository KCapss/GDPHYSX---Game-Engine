#include "ObjectContainer.h"

void ObjectContainer::addParticle(Particle* particle)
{
	particleContainer.push_back(particle);
}

void ObjectContainer::updateParticleContainer()
{
	for (int i = 0; i < particleContainer.size(); i++)
	{
		for (int j = 0; j < particleContainer.size(); j++)
		{
			if (i != j) // Don't check distance between particle and itself
			{
				glm::vec3 particle1Pos = particleContainer[i]->getPosition();
				glm::vec3 particle2Pos = particleContainer[j]->getPosition();

				glm::vec3 particleVel1 = particleContainer[i]->getVelocity();
				glm::vec3 particleVel2 = particleContainer[j]->getVelocity();

				//float distanceBetween = glm::distance(particle1Pos, particle2Pos);
				float seperateVel = glm::dot((particleVel1 - particleVel2), glm::normalize(particle1Pos - particle2Pos));
				cout << "Distance: " << seperateVel << " \n";

				if (seperateVel <= 20.0f && seperateVel >= -20.0f)
				{
					cout << "Collided\n";
					particleContact = new ParticleContact(particleContainer[i], particleContainer[j]);
					delete particleContact;
				}

				/*if (distanceBetween <= 10.0)
				{
					printf("Collide!");
				}*/
			}
		}
	}

}
