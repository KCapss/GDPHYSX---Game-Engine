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
				float distanceBetween = glm::distance(particle1Pos, particle2Pos);

				if (distanceBetween <= 10.0)
				{
					printf("Collide!");
				}
			}
		}
	}

}
