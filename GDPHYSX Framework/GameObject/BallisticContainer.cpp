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

void BallisticContainer::loadFireworks(FireworkObject* fireworks)
{
	divisoria.push_back(fireworks);
	cout << "Exolision loaded" << endl;
	maxSize++;
}

void BallisticContainer::updateBallisticContainer(float deltaTime)
{
	for (int i = 0; i < magazine.size(); i++)
	{
		if (magazine[i]->getShotType() != ShotTypes::UNUSED)
		{
			// Run physics
			magazine[i]->integrator(deltaTime);
			magazine[i]->updateBallistic(deltaTime);


	/*	 Now checks if out of bounds or is past its age*/
	if (magazine[i]->getPosition().y < -2000.0f ||
				magazine[i]->getAge() <= 0 ||
				magazine[i]->getPosition().z > 2000.0f)
			{
				// Set to unused if invalid
				//magazine[i]->setShotType(ShotTypes::UNUSED);
				cout << "Shot Disabled" << endl;
				magazine[i]->onReset();
			}
		}
	}

	for (int i = 0; i < divisoria.size(); i++) {
		if (divisoria[i]->IsReady()) {
			//Update:
			divisoria[i]->updateFireworkObject(deltaTime);

			//Checker
			if (!divisoria[i]->isPayloadActive()) {
				cout << "fireworks gone" << endl;
				divisoria[i]->setReady(false);
			}
			
		}
	}

	this->ticks += deltaTime;
}

void BallisticContainer::fireMagazine(ShotTypes shotypes)
{
	//Check what kind of bullets


	//Problem: There is no fixed interval
	if ((limitSize >= this->activeSize) && ( ticks >= COOLDOWN ) ){

		cout << "Shot Fired" << endl;

		if (shotypes != ShotTypes::FIREWORK) {
			for (int i = 0; i < magazine.size(); i++) {
				if (magazine[i]->getShotType() == ShotTypes::UNUSED) {
					magazine[i]->onActivate(shotypes);
					break;
				}
			}
		}

		else if (shotypes == ShotTypes::FIREWORK) {
			for (int i = 0; i < divisoria.size(); i++) {
				if (!divisoria[i]->IsReady()) {
					cout << "Boom" << endl;

					divisoria[i]->setReady(true);
					divisoria[i]->activate(NULL);
					break;
				}
			}
		}

		ticks = 0;
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

	for (int i = 0; i < divisoria.size(); i++) {
		if (divisoria[i]->getType() != 0) {
			divisoria[i]->draw();
		}
	}
}

void BallisticContainer::deleteBuffer()
{

	for (int i = 0; i < magazine.size(); i++)
	{
			magazine[i]->deAllocate();
	}

	for (int i = 0; i < divisoria.size(); i++) {
			divisoria[i]->deAllocate();
	}
}
