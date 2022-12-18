#include "BallisticContainer.h"

vector<BallisticObject*> BallisticContainer::getMagazine()
{
	return magazine;
}

void BallisticContainer::loadMagazine(BallisticObject* bullet)
{
	magazine.push_back(bullet);
	
	maxSize++;
}

void BallisticContainer::loadFireworks(FireworkObject* fireworks)
{
	fireworkBox.push_back(fireworks);
	
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


	/*	 Now checks if out of bounds or is past its age or collides with RB*/
	if (magazine[i]->getPosition().y < -2000.0f ||
				magazine[i]->getAge() <= 0 ||
				magazine[i]->getPosition().z > 2000.0f || magazine[i]->isHit)
			{
				// Set to unused if invalid
				magazine[i]->onReset();
			}
		}
	}

	for (int i = 0; i < fireworkBox.size(); i++) {
		if (fireworkBox[i]->IsReady()) {
			//Update:
			fireworkBox[i]->updateFireworkObject(deltaTime);

			//Checker
			if (!fireworkBox[i]->isPayloadActive()) {
				
				fireworkBox[i]->setReady(false);
			}
			
		}
	}

	this->ticks += deltaTime;
}

void BallisticContainer::fireMagazine(ShotTypes shotypes)
{
	//Check what kind of bullets
	if ((limitSize >= this->activeSize) && ( ticks >= COOLDOWN ) ){

		

		if (shotypes != ShotTypes::FIREWORK) {
			for (int i = 0; i < magazine.size(); i++) {
				if (magazine[i]->getShotType() == ShotTypes::UNUSED) {
					magazine[i]->onActivate(shotypes);
					break;
				}
			}
		}

		else if (shotypes == ShotTypes::FIREWORK) {
			for (int i = 0; i < fireworkBox.size(); i++) {
				if (!fireworkBox[i]->IsReady()) {
					

					fireworkBox[i]->setReady(true);
					fireworkBox[i]->activate(NULL);
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

	for (int i = 0; i < fireworkBox.size(); i++) {
		if (fireworkBox[i]->getType() != 0) {
			fireworkBox[i]->draw();
		}
	}
}

void BallisticContainer::deleteBuffer()
{

	for (int i = 0; i < magazine.size(); i++)
	{
			magazine[i]->deAllocate();
	}

	for (int i = 0; i < fireworkBox.size(); i++) {
			fireworkBox[i]->deAllocate();
	}
}
