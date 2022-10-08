#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

typedef glm::vec3 vec3;

class Particle
{
public:
	//Default Constructor & Destructor
	Particle();
	Particle(vec3 Pos, float Mass);
	~Particle();

	
	//Setter
	glm::mat4 computeTransform(); //Place Holder

	virtual void setPosition(vec3 Pos);
	virtual void setVelocity(vec3 velocity);
	virtual void setAcceleration(vec3 acceleration);

	
	void setMass(float mass);

	//Getter
	virtual	vec3 getPosition();
	float getMass();

	//Physics == Debuging
	void updatePosition(float deltaTime);
	void updateVelocity(vec3 velocity, float deltaTime);
	void updateAcceleration(vec3 acceleration);


	//Physics Application
	void applyForce(vec3 Force);


	

	//Constant Force
	void toogleGravity(bool flag);
	bool checkGravityStatus();



	


private:

	//InClass Method
	void integrator(float deltaTime);
	

	//Properties
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;
	

	bool isGravityOn;
	float mass;
	float damp;



	const float GRAVITY = -9.8f;
};
