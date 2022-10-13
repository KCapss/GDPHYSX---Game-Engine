#pragma once
#include "Particle.h"
#include "Firework.h"

#include <vector>

using namespace std;

class FireworkRules{
public:
	FireworkRules();
	~FireworkRules();

	void setParameters(unsigned type, int minAge, int maxAge,
		glm::vec3 minVelocity, glm::vec3 maxVelocity,
		float damping);

	void init(unsigned payloadCount);
	void create(Firework* firework, Firework* parent = NULL) const; // avoid nalang these
	


	// It accept FireworkObject
	struct Payload {
		unsigned paramType;
		unsigned paramCount;

		void set(unsigned type, unsigned count) {
			Payload::paramType = type;
			Payload::paramCount = count;
		}
	};

	vector <Payload*> payloads;
	unsigned payloadCount;


	


		unsigned type;
		int minAge;
		int maxAge;

		glm::vec3 minVelocity;
		glm::vec3 maxVelocity;

		float damp;

		

		
		//Set number of payload per each firework

//Methods
		glm::vec3 randomVector(glm::vec3 minVector, glm::vec3 maxVector);



	
		
		
};

