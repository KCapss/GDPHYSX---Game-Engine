#pragma once
#include "BallisticObject.h" 
#include "FireworkObject.h"
#include <vector>

using namespace std;

class BallisticContainer
{
public:
	//Constructor

	vector<BallisticObject*> getMagazine(); // Getter but rarely used

	void loadMagazine(BallisticObject* bullet);
	void loadFireworks(FireworkObject* fireworks);
	//void load Fireworks

//Loading the Ammo
	void updateBallisticContainer(float deltaTime);


//Action
	void fireMagazine(ShotTypes shotypes);
	void setLimit(unsigned maxCount);

//Update and Render
	void draw();
	void deleteBuffer();

private:
	vector<BallisticObject*> magazine; // holds all instantiated ballistics
	vector<FireworkObject*> divisoria; // holds all illegal fireworks
	int maxSize = 0;
	int activeSize = 0;
	unsigned limitSize = 0;

	//vector<FireworkObject*> firesticks;

	float ticks = 0;
	const float COOLDOWN = 0.2f;
	

};

