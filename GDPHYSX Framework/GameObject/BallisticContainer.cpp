#include "BallisticContainer.h"

vector<BallisticObject*> BallisticContainer::getMagazine()
{
	return magazine;
}

void BallisticContainer::loadMagazine(BallisticObject* bullet)
{
	magazine.push_back(bullet);
	cout << "Bullet loaded" << endl;
	maxSize++;
}

void BallisticContainer::updateMagazine(float deltaTime)
{
	for (int i = 0; i < magazine.size(); i++)
	{
		if (magazine[i]->getShotType() != ShotTypes::UNUSED)
		{
			// Run physics
			magazine[i]->integrator(deltaTime);

		/*	 Check if particle is invalid,
			 still need to add a way to measure duration of life*/
			if (magazine[i]->getPosition().y < -2000.0f ||
				magazine[i]->getPosition().z < 200000.0f)
			{
				// Set to unused if invalid
				//magazine[i]->setShotType(ShotTypes::UNUSED);
				cout << "Shot Disabled" << endl;
				magazine[i]->onReset();
			}
		}
	}
}

void BallisticContainer::fireMagazine(ShotTypes shotypes)
{
	//Check what kind of bullets


	//Problem: There is no fixed interval
	if (limitSize <= this->activeSize) {

		if (shotypes != ShotTypes::FIREWORK) {
			for (int i = 0; i < magazine.size(); i++) {
				if (magazine[i]->getShotType() == ShotTypes::UNUSED) {
					magazine[i]->onActivate(shotypes);
					break;
				}
			}
		}

		else if (shotypes == ShotTypes::FIREWORK) {
			//PlaceHolder for accessing fireworks
		}

	}


}

void BallisticContainer::setLimit(unsigned maxCount)
{
	this->limitSize = maxCount;
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
			magazine[i]->deAllocate();
	}
}
