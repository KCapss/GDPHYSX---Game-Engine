#pragma once
#include "BallisticObject.h" 
#include <vector>

using namespace std;

class BallisticContainer
{
public:
	//Constructor

	vector<BallisticObject*> getMagazine(); // Getter but rarely used

	void loadMagazine(BallisticObject* bullet);
	//void load Fireworks

//Loading the Ammo
	void updateMagazine(float deltaTime);


//Action
	void fireMagazine(ShotTypes shotypes);
	void setLimit(unsigned maxCount);

//Update and Render
	void draw();
	void deleteBuffer();

private:
	vector<BallisticObject*> magazine; // holds all instantiated ballistics
	int maxSize = 0;
	int activeSize = 0;
	unsigned limitSize = 0;

	//vector<FireworkObject*> firesticks;

	float ticks = 0;
	const float COOLDOWN = 0.2f;
	

};

