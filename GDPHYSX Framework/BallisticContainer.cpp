#include "BallisticContainer.h"

vector<Ballistic*> BallisticContainer::getMagazine()
{
	return magazine;
}

void BallisticContainer::loadMagazine(Ballistic* bullet)
{
	magazine.push_back(bullet);
}

void BallisticContainer::updateMagazine(float deltaTime)
{
	for (int i = 0; i < magazine.size(); i++)
	{
		if (magazine[i]->getShotType() != shotType::UNUSED)
		{
			// Run physics
			magazine[i]->integrator(deltaTime);

			// Check if particle is invalid,
			// still need to add a way to measure duration of life
			if (magazine[i]->getPosition().y < 0.0f ||
				magazine[i]->getPosition().z < 200.0f)
			{
				// Set to unused if invalid
				magazine[i]->setShotType(shotType::UNUSED);
			}
		}
	}
}
