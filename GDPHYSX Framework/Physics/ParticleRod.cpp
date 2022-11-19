#include "ParticleRod.h"

ParticleRod::ParticleRod(Particle* p1, Particle* p2): ParticleLink()
{
    particle[0] = p1;
    particle[1] = p2;
}

unsigned ParticleRod::addContact(ParticleContact* contact, unsigned limit) const
{
    // Find the length of the rod
    float currentLen = currentLength();

    // Check if we're over-extended
    if (currentLen == length)
    {
        return 0;
    }

    // Otherwise return the contact
    contact->particle[0] = particle[0];
    contact->particle[1] = particle[1];

    // Calculate the normal
    glm::vec3 normal = glm::normalize(particle[1]->getPosition() - particle[0]->getPosition());
    

    // The contact normal depends on whether we're extending or compressing
    if (currentLen > length) {
        contact->contactNormal = normal;
        contact->penetration = currentLen - length;
    }
    else {
        contact->contactNormal = normal * -1.0f;
        contact->penetration = length - currentLen;
    }

    // Always use zero restitution (no bounciness)
    contact->restitution = 0;

    return 1;
}
