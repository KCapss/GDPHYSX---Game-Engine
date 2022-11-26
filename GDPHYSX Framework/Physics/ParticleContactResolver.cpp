#include "ParticleContactResolver.h"

ParticleContactResolver::ParticleContactResolver(unsigned iterations) :
	iterations(iterations)
{
	ParticleContactResolver::iterations = iterations;
}

void ParticleContactResolver::setIterations(unsigned iterations)
{

}

void ParticleContactResolver::resolveContacts(ParticleContact* contactArray, unsigned numContacts, float timeStep)
{
    unsigned i;

    iterationsUsed = 0;
    while (iterationsUsed < iterations)
    {
        // Find the contact with the largest closing velocity;
        float max = 28.0f;//REAL_MAX;
        unsigned maxIndex = numContacts;
        for (i = 0; i < numContacts; i++)
        {
            float sepVel = contactArray[i].calculateSeparatingVelocity();

            if (sepVel < max &&
                (sepVel < 0 || contactArray[i].penetration > 0))
            {
                max = sepVel;
                maxIndex = i;
            }
        }

        // Do we have anything worth resolving?
        if (maxIndex == numContacts) break;

        // Resolve this contact
        contactArray[maxIndex].resolve(timeStep);

        // Update the interpenetrations for all particles
        vec3* move = contactArray[maxIndex].particleMovement;
        for (i = 0; i < numContacts; i++)
        {
            if (contactArray[i].particle[0] == contactArray[maxIndex].particle[0])
            {
                contactArray[i].penetration -= glm::dot(move[0], contactArray[i].contactNormal);
            }
            else if (contactArray[i].particle[0] == contactArray[maxIndex].particle[1])
            {
                contactArray[i].penetration -= glm::dot(move[1], contactArray[i].contactNormal);
            }
            if (contactArray[i].particle[1])
            {
                if (contactArray[i].particle[1] == contactArray[maxIndex].particle[0])
                {
                    contactArray[i].penetration += glm::dot(move[0], contactArray[i].contactNormal);
                }
                else if (contactArray[i].particle[1] == contactArray[maxIndex].particle[1])
                {
                    contactArray[i].penetration += glm::dot(move[1], contactArray[i].contactNormal);
                }
            }
        }

        iterationsUsed++;
    }
}
