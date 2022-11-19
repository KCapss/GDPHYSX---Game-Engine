#include "ObjectContainer.h"

void ObjectContainer::addParticle(Particle* particle)
{
	particleContainer.push_back(particle);
}

void ObjectContainer::updateParticleContainer(float deltaTime)
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


				if (particleVel1 != vec3(0)) {
					//float distanceBetween = glm::distance(particle1Pos, particle2Pos);
					vec3 particleVelDif = particleVel1 - particleVel2;
					//vec3 particlePosVec = glm::normalize(particle1Pos - particle2Pos);
					//float seperateVel = glm::dot(particleVelDif, particlePosVec);
					//float seperateVel = glm::dot((particleVel1 - particleVel2), glm::normalize(particle1Pos - particle2Pos));
					//cout << "Distance: " << seperateVel << " \n";

					//Lenght
					float distance = glm::distance(particle1Pos, particle2Pos);
					//cout << "Distance: " << distance << " \n";
					if (abs(distance) <= 50.0f && particleVelDif != glm::vec3(0, 0, 0))
					{

						cout << "Collided\n";
						particleContact = new ParticleContact(particleContainer[i], particleContainer[j]);
						particleContact->resolve(deltaTime);
						delete particleContact;
					}

					//Particle is beneath or touching the floor
					else if (particleContainer[i]->getPosition().y <= floorDepth) {
						cout << "Floor Collided\n";

						glm::vec3 refPos = particleContainer[i]->getPosition();

						Particle* floorParticle = new Particle(glm::vec3(refPos.x, floorDepth - 1.0f, refPos.z), 0);
						particleContact = new ParticleContact(particleContainer[i], floorParticle);
						particleContact->resolve(deltaTime);
						delete particleContact;

					}


				}
				/*if (distanceBetween <= 10.0)
				{
					printf("Collide!");
				}*/
			}
		}
	}

}
