#include "FireworkObject.h"


FireworkObject::FireworkObject(std::string name, ObjectType objType, GLFWwindow* currWindow):
	FireworkRules(), Firework(), Model(name, objType, currWindow)
{

}

FireworkObject::~FireworkObject()
{
}

void FireworkObject::initFireworkRules()
{
}

void FireworkObject::update()
{

}
