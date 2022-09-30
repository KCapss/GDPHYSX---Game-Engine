#include "Particle.h"
#include <iostream>

using namespace std;

Particle::Particle()
{
    this->mass = 0;
    this->position = vec3(0.0f);
    this->velocity = vec3(0.0f);
    this->acceleration = vec3(0.f, -9.8f, 0.f);
}

Particle::Particle(vec3 Pos, float Mass)
{
    this->mass = Mass;
    this->position = vec3(0.0f);
    this->velocity = vec3(0.0f);
    this->acceleration = vec3(0.f, -9.8f, 0.f);
}



glm::mat4 Particle::computeTransform()
{
    return glm::mat4(1);
}

void Particle::setMass(float mass)
{
    this->mass = mass;
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
    this->velocity = (this->velocity + (GRAVITY * deltaTime));

    
    cout << "velocity y:" << this->velocity.y << endl;
    updatePosition(deltaTime);
}

void Particle::updateAcceleration(vec3 acceleration)
{
    //acceleration constant = gravity
    this->acceleration = acceleration;
}

void Particle::applyForce(vec3 Force)
{
    this->acceleration = Force / this->mass;
}
