#include "CubeObject.h"

CubeObject::CubeObject(std::string name, ObjectType objType, GLFWwindow* currWindow) :
	Model(name, objType, currWindow), ParticleRod()
{
	//Purpose Generate Edges
}

void CubeObject::init(float l, float w, float h, float scaleMag)
{
	this->length = l;
	this->width = w;
	this->height = h;

	for (int i = 0; i < EDGE_SIZE; i++) {
		ParticleObject* edgeParticle = new ParticleObject(this->name, this->objType, this->window);
		edgeParticle->retrieveSource(this->light, this->perspCam, this->orthoCam);
		edgeParticle->setInitialScale(vec3(scaleMag));

		//Determine which position of the particle 
		//1 = Create a function that automatically returns the position of the 
		//particle depending on the index
		edgeParticle->setPosition(this->setupEdge(i));


		this->EdgeList.push_back(edgeParticle);
	}

	//Create a Function that automatically connect the particle (Particle Rod);


}

//Purpose is to add all particle to detect collision
//Add all possible pair for contacts;
void CubeObject::addListContact(ObjectContainer *refContainer)
{
	//Add all particle inisde the object container
	for (int i = 0; i < EDGE_SIZE; i++) {
		refContainer->addParticle((Particle*)EdgeList[i]);
	}


	//Connect the Rods in pairs location
	for (int i = 0; i < EDGE_SIZE; i++) {
		for (int j = 0; j < EDGE_SIZE - i; j++) {
			
			if (i != j) {
				//Particle
				ParticleContact* pairContact = new ParticleContact(EdgeList[i], EdgeList[i + j]);
				ContactList.push_back(pairContact);
					//refContainer->addPairContact

			}
		}
	}



}

void CubeObject::update(float timeStep)
{

	for (int i = 0; i < EdgeList.size(); i++) {
		EdgeList[i]->update(timeStep);
	}

	for (int i = 0; i < ContactList.size(); i++) {
	
		//unsigned int copy = addContact(ContactList[i], 1);
	}

}

void CubeObject::draw()
{
	for (int i = 0; i < EdgeList.size(); i++) {
		EdgeList[i]->draw();
	}
}

glm::vec3 CubeObject::setupEdge(int index)
{
	glm::vec3 finalPos = vec3(0);

	switch (index) {
	case 0:
		finalPos = glm::vec3(-this->length, this->height, this->width);
		break;
	case 1:
		finalPos = glm::vec3(this->length, this->height, this->width);
		break;
	case 2:
		finalPos = glm::vec3(-this->length, -this->height, this->width);
		break;
	case 3:
		finalPos = glm::vec3(this->length, -this->height, this->width);
		break;
	case 4:
		finalPos = glm::vec3(-this->length, this->height, -this->width);
		break;
	case 5:
		finalPos = glm::vec3(this->length, this->height, -this->width);
		break;
	case 6:
		finalPos = glm::vec3(-this->length, -this->height, -this->width);
		break;
	case 7:
		finalPos = glm::vec3(this->length, -this->height, -this->width);
		break;

	default:
		cout << "Error in setup" << endl;

	}


	return finalPos;
}


