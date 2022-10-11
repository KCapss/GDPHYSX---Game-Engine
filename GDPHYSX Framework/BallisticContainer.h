#pragma once
#include "Ballistic.h" 
#include <vector>

using namespace std;

class BallisticContainer
{
public:
	vector<Ballistic*> getMagazine();
	void loadMagazine(Ballistic* bullet);
	void updateMagazine(float deltaTime);

private:
	vector<Ballistic*> magazine; // holds all instantiated ballistics
	

};

