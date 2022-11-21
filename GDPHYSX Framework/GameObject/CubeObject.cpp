#include "CubeObject.h"

CubeObject::CubeObject(std::string name, ObjectType objType, GLFWwindow* currWindow) :
	Model(name, objType, currWindow)
{
	//Purpose Generate Edges
	this->resolver = new ParticleContactResolver(2);


}

void CubeObject::init(float l, float w, float h, vec3 Pos, float scaleMag)
{
	this->length = l;
	this->width = w;
	this->height = h;
	this->Pos = Pos;

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
	for (int i = 0; i < EdgeList.size(); i++) {
		for (int j = 0; j < EdgeList.size() - i; j++) {
			
			if (i != i+j) {
				//Particle
				//cout << "Left: " << i << "Right: " << i + j << endl;

				//Create Contact
				ParticleContact* pairContact = new ParticleContact(EdgeList[i], EdgeList[i + j]);
				ContactList.push_back(pairContact);

				//Create Rod
				ParticleRod* rodCopy = new ParticleRod(EdgeList[i], EdgeList[i + j]);
				RodList.push_back(rodCopy);
				
				
					//refContainer->addPairContact

				//Create the renderer part;
				LineRenderer* lineCopy = new LineRenderer(EdgeList[i]->getPosition(), EdgeList[i + j]->getPosition());
				LineRendererList.push_back(lineCopy);

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
	
		unsigned int copy = RodList[i]->addContact(ContactList[i], 1);
	}


	//Enable Them to see how contact resolver works
	for (int iteration = 0; iteration < 3; iteration++) {
		for (int i = 0; i < ContactList.size(); i++) {
			resolver->resolveContacts(ContactList[i], 1, timeStep);
		}
	}
	

	for (int i = 0; i < ContactList.size(); i++) {

		LineRendererList[i]->updatePos(ContactList[i]->particle[0]->getPosition(),
			ContactList[i]->particle[1]->getPosition());
	}

}

void CubeObject::draw()
{
	for (int i = 0; i < EdgeList.size(); i++) {
		EdgeList[i]->draw();
	}

	for (int i = 0; i < LineRendererList.size(); i++) {

		LineRendererList[i]->draw();
	}
}

glm::vec3 CubeObject::setupEdge(int index)
{
	glm::vec3 finalPos = vec3(0);

	switch (index) {
	case 0:
		finalPos = glm::vec3(-this->length, this->height, this->width) + Pos;
		break;
	case 1:
		finalPos = glm::vec3(this->length, this->height, this->width) + Pos;
		break;
	case 2:
		finalPos = glm::vec3(-this->length, -this->height, this->width) + Pos;
		break;
	case 3:
		finalPos = glm::vec3(this->length, -this->height, this->width) + Pos;
		break;
	case 4:
		finalPos = glm::vec3(-this->length, this->height, -this->width) + Pos;
		break;
	case 5:
		finalPos = glm::vec3(this->length, this->height, -this->width) + Pos;
		break;
	case 6:
		finalPos = glm::vec3(-this->length, -this->height, -this->width) + Pos;
		break;
	case 7:
		finalPos = glm::vec3(this->length, -this->height, -this->width) + Pos;
		break;

	default:
		cout << "Error in setup" << endl;

	}


	return finalPos;
}


