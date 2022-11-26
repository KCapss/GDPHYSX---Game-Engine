#pragma once
//Object Primitives
#include "ParticleObject.h"
#include "../Physics/ParticleRod.h"
#include "../Physics/ParticleContactResolver.h"

#include "../Render/LineRenderer.h"

//Object Contact
#include "ObjectContainer.h"

#include <vector>


class CubeObject : public Model
{
public:
	CubeObject(std::string name, ObjectType objType, GLFWwindow* currWindow);
	//RetrieveSource
	//SetScale
	void init(float l, float w, float h, vec3 Pos, float scaleMag);
	void addListContact(ObjectContainer *refContainer);



	void update(float timeStep);
	void draw();



protected:
	//List
	std::vector <ParticleObject*> EdgeList;
	std::vector <ParticleContact*> ContactList;
	std::vector <ParticleRod*> RodList;

	//Renderer
	std::vector<LineRenderer*> LineRendererList;

	//Resolver
	ParticleContactResolver* resolver;
	int const EDGE_SIZE = 8;

private:

	glm::vec3 setupEdge(int index);
	glm::vec3 Pos;
	float length;
	float width;
	float height;



};

