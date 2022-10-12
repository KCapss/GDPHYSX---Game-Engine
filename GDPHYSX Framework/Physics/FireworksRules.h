#pragma once
#include "Particle.h"
#include "Firework.h"

class FireworkRules{
public:
	FireworkRules();
	~FireworkRules();

	void setParameters(unsigned type, int minAge, int maxAge,
		glm::vec3& minVelocity, glm::vec3& maxVelocity,
		float damping);

	void init(unsigned payloadCount);
	void create(Firework* firework, Firework* parent = NULL) const;

private:
		unsigned type;
		int minAge;
		int maxAge;

		glm::vec3 minVelocity;
		glm::vec3 maxVelocity;

		float damp;

		struct Payload {
			unsigned paramType;
			unsigned paramCount;

			void set(unsigned type, unsigned count) {
				Payload::paramType = type;
				Payload::paramCount = count;
			}
		};

		//Next
		unsigned payloadCount;
		Payload* payloads; //Set number of payload per each firework

//Methods
		



	
		
		
};

