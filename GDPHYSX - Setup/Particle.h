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
	//Default Constructor
	Particle();
	Particle(vec3 Pos, float Mass);
	
	//Method
	glm::mat4 computeTransform(); 

	void setMass(float mass);
	float getMass();

	//Physics
	void updatePosition(float deltaTime);
	void updateVelocity(vec3 velocity, float deltaTime);
	void updateAcceleration(vec3 acceleration);
	void applyForce(vec3 Force);

	//Properties
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec3 acceleration;

	bool isGravityOn;
	const float GRAVITY = 9.8f;

private:
	
	float mass;


};

