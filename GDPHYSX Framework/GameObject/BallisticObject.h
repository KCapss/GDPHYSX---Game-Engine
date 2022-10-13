#pragma once
#include "../Model.h"
#include "../Physics/Ballistic.h"



class BallisticObject: public Model, public Ballistic
{
public:
	//Constructor
	BallisticObject(std::string name, ObjectType objType, GLFWwindow* currWindow);

	void update(float timeStep);
	void draw();

	void onActivate(ShotTypes shotType);
	void onReset();

private:
	//Debug
	glm::vec3 defaultPos;

};

