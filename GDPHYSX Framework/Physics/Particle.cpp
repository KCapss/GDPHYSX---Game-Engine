#include "Particle.h"
#include <iostream>
#include <cmath>

using namespace std;

Particle::Particle()
{
    this->mass = 0.01f;
    this->position = vec3(0.0f);
    this->velocity = vec3(0.0f);
    this->acceleration = vec3(0.0f);

    this->damp = 1.0f;

    //Gravity
    this->isGravityOn = false;
}

Particle::Particle(vec3 Pos, float Mass)
{
    this->mass = Mass;
    this->position = vec3(Pos.x, Pos.y, Pos.z);
    this->velocity = vec3(0.0f);
    this->acceleration = vec3(0.0f);

    this->damp = 1.0f;

    //Gravity
    this->isGravityOn = false;
}

Particle::~Particle()
{
    delete this;
}



glm::mat4 Particle::computeTransform()
{
    return glm::mat4(1);
}

void Particle::setPosition(vec3 Pos)
{
    this->position = Pos;
}

void Particle::setVelocity(vec3 velocity)
{
    this->velocity = velocity;
}

void Particle::setAcceleration(vec3 acceleration)
{
    this->acceleration = acceleration;
}

void Particle::setDamping(float damp)
{
    this->damp = damp;
}

void Particle::addVelocity(vec3 addVeloctiy)
{
    this->velocity += addVelocity;
}

void Particle::setMass(float mass)
{
    //Initial Proposal
    this->mass = mass;

    //Can be later change to add or subract rather than replacing
}

vec3 Particle::getPosition()
{
    return this->position;
}

vec3 Particle::getVelocity()
{
    return this->velocity;
}

vec3 Particle::getAcceleraation()
{
    return this->acceleration;
}

float Particle::getMass()
{
    return this->mass;
}

void Particle::updatePosition(float deltaTime)
{
    this->integrator(deltaTime);
}

void Particle::updateVelocity(vec3 velocity, float deltaTime)
{

    //Assuming gravity is on
    if (isGravityOn) {
        this->velocity = (this->velocity + (vec3(0.f, GRAVITY, 0.f) * deltaTime)) + (velocity * deltaTime);
    }
    
    else {
        this->velocity = (this->velocity) + (velocity * deltaTime);
    }
    
    //cout << "velocity x: " << this->velocity.x << "\tvelocity y:" << this->velocity.y << "\tvelocity z: " << this->velocity.z << endl;
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
    //Initial Proposal
    //this->velocity +=  (Force / this->mass); // there can be an error if mass is 0

    float inverseMass = 0;
    //Using Inverse Mass
    if (this->mass != 0) {
        inverseMass = 1 / this->mass;
    }
    
    else {
        inverseMass = 0;
    }
    

    //New Method
    this->velocity += inverseMass * Force;
}

void Particle::toogleGravity(bool flag)
{
    this->isGravityOn = flag;
}

bool Particle::checkGravityStatus()
{
    return this->isGravityOn;
}


//Purpose:
/*
* 1) Update the Position = currPos + Vel(T) + Vel(T)^2 
* 2) Update the Velocity = currVel + (Sum of all acceleration & force)T
*/
void Particle::integrator(float deltaTime)
{
    //Updating Position:
    this->position = this->position + ((this->velocity * deltaTime));

    
  
    //Updating Velocity

    if(this->isGravityOn)
        this->velocity = (this->velocity * powf(this->damp, deltaTime)) + (vec3(0.0f, GRAVITY, 0.0f) + this->acceleration) * deltaTime;
    else
        this->velocity = (this->velocity * powf(this->damp, deltaTime)) + (this->acceleration) * deltaTime;
     //powf(deltaTime) will be edit later
    
     
}
