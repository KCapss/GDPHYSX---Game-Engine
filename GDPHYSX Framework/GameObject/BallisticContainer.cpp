#include "BallisticContainer.h"

vector<BallisticObject*> BallisticContainer::getMagazine()
{
	return magazine;
}

void BallisticContainer::loadMagazine(BallisticObject* bullet)
{
	magazine.push_back(bullet);
	cout << "Bullet loaded" << endl;
}

void BallisticContainer::updateMagazine(float deltaTime)
{
	for (int i = 0; i < magazine.size(); i++)
	{
		if (magazine[i]->getShotType() != ShotTypes::UNUSED)
		{
			// Run physics
			magazine[i]->integrator(deltaTime);

			// Check if particle is invalid,
			// still need to add a way to measure duration of life
			//if (magazine[i]->getPosition().y < -20.0f ||
			//	magazine[i]->getPosition().z < 200.0f)
			//{
			//	// Set to unused if invalid
			//	//magazine[i]->setShotType(ShotTypes::UNUSED);
			//	cout << "Shot Disabled" << endl;
			//	magazine[i]->onReset();
			//}
		}
	}
}

void BallisticContainer::draw()
{
	for (int i = 0; i < magazine.size(); i++)
	{
		if (magazine[i]->getShotType() != ShotTypes::UNUSED)
		{
			magazine[i]->draw();
		}
	}
}

void BallisticContainer::deleteBuffer()
{

	for (int i = 0; i < magazine.size(); i++)
	{
		if (magazine[i]->getShotType() != ShotTypes::UNUSED)
		{
			magazine[i]->deAllocate();
		}
	}
}
