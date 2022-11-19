#include "CubeObject.h"

CubeObject::CubeObject(std::string name, ObjectType objType, GLFWwindow* currWindow) :
	Model(name, objType, currWindow), ParticleRod()
{
	//Purpose Generate Edges
}

void CubeObject::init(int l, int w, int h, float scaleMag)
{
	for (int i = 0; i < EDGE_SIZE; i++) {
		ParticleObject* edgeParticle = new ParticleObject(this->name, this->objType, this->window);
		edgeParticle->retrieveSource(this->light, this->perspCam, this->orthoCam);
		edgeParticle->setInitialScale(vec3(scaleMag));

		//Determine which position of the particle 
		//1 = Create a function that automatically returns the position of the 
		//particle depending on the index

		this->EdgeList.push_back(edgeParticle);
	}

	//Create a Function that automatically connect the particle (Particle Rod);


}

//Purpose is to add all particle to detect collision
//Add all possible pair for contacts;
void CubeObject::addListContact(ObjectContainer refContainer)
{
	//Add all particle inisde the object container
	for (int i = 0; i < EDGE_SIZE; i++) {
		refContainer.addParticle((Particle*)EdgeList[i]);
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
	
		unsigned int copy = addContact(ContactList[i], 1);
	}

}

void CubeObject::draw()
{
	for (int i = 0; i < EdgeList.size(); i++) {
		EdgeList[i]->draw();
	}
}


