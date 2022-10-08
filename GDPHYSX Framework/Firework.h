#pragma once
#include "Particle.h"
class Firework : public Particle
{
public:
	Firework();
	~Firework();

	enum fireworkTypes;

	//Methods
	bool updateFireworks(float deltaTime);
	void initFireworkRules();


private:
	//Methods





	//Parameters
	float age; // Default

////Rule Type Parameter
//	unsigned type;
//	float minAge;
//	float maxAge;
//
//	glm::vec3 minVelocity;
//	glm::vec3 maxVelocity;
//	
//	float damp;
//
//// PayLoad Parameter = insigned per each firework	
//	unsigned paramType;
//	unsigned paramCount;
//
//
////Next
//	unsigned payloadCount;
//	//Payload *payload //Set number of payload per each firework


//Template
	struct FireWorkRule {
		unsigned type;
		float minAge;
		float maxAge;

		glm::vec3 minVelocity;
		glm::vec3 maxVelocity;

		float damp;

		struct Payload {
			unsigned paramType;
			unsigned paramCount;
		};
		
		//Next
		unsigned payloadCount;
		Payload* payload; //Set number of payload per each firework
	};
	

};

