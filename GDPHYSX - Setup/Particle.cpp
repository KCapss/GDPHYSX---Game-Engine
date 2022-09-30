#include "Particle.h"
#include <iostream>

using namespace std;

Particle::Particle()
{
    this->mass = 0;
    this->position = vec3(0.0f);
    this->velocity = vec3(0.0f);
    this->acceleration = vec3(0.0f);

    //Gravity
    this->isGravityOn = false;
}

Particle::Particle(vec3 Pos, float Mass)
{
    this->mass = Mass;
    this->position = vec3(0.0f);
    this->velocity = vec3(0.0f);
    this->acceleration = vec3(0.0f);

    //Gravity
    this->isGravityOn = false;
}



glm::mat4 Particle::computeTransform()
{
    return glm::mat4(1);
}

void Particle::setMass(float mass)
{
    //Initial Proposal
    this->mass = mass;

    //Can be later change to add or subract rather than replacing
}

float Particle::getMass()
{
    return this->mass;
}

void Particle::updatePosition(float deltaTime)
{
    //cout << "positiion y: " << this->position.y << endl;
    this->position = (this->position + (this->velocity * deltaTime));
    
}

void Particle::updateVelocity(vec3 velocity, float deltaTime)
{

    //Assuming gravity is on
    if (isGravityOn) {
        this->velocity = (this->velocity + (GRAVITY * deltaTime)) + (velocity * deltaTime);
    }
    
    else {
        this->velocity = (this->velocity) + (velocity * deltaTime);
    }
    
    cout << "velocity y:" << this->velocity.y << endl;
    updatePosition(deltaTime);
}

void Particle::updateAcceleration(vec3 acceleration)
{
    //initial Proposal
    this->acceleration = acceleration;
}


//Still testing for error if it applied on multiple iteration
void Particle::applyForce(vec3 Force)
{

    this->velocity +=  (Force / this->mass); // there can be an error if mass is 0
}

void Particle::toogleGravity(bool flag)
{


    this->isGravityOn = flag;
}
