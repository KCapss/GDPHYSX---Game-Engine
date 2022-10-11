#pragma once
#include "BallisticObject.h" 
#include <vector>

using namespace std;

class BallisticContainer
{
public:

	//Constructor


	//
	vector<BallisticObject*> getMagazine(); // Getter but rarely used

	void loadMagazine(BallisticObject* bullet);
	void updateMagazine(float deltaTime);
	void draw();
	void deleteBuffer();

private:
	vector<BallisticObject*> magazine; // holds all instantiated ballistics

	

};

