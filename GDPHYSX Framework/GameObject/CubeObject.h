#pragma once
//Object Primitives
#include "ParticleObject.h"
#include "../Physics/ParticleRod.h"

//Object Contact
#include "ObjectContainer.h"

#include <vector>


class CubeObject : public Model, public ParticleRod
{
public:
	CubeObject(std::string name, ObjectType objType, GLFWwindow* currWindow);
	//RetrieveSource
	//SetScale
	void init(float l, float w, float h, float scaleMag);
	void addListContact(ObjectContainer *refContainer);



	void update(float timeStep);
	void draw();



protected:
	std::vector <ParticleObject*> EdgeList;
	std::vector <ParticleContact*> ContactList;
	int const EDGE_SIZE = 8;

private:

	glm::vec3 setupEdge(int index);

	float length;
	float width;
	float height;



};

