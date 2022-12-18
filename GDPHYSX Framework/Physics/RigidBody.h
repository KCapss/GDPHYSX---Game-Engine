#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Quaterions.h"

#include <iostream>

typedef glm::vec3 vec3;

class RigidBody
{
public:

    RigidBody();
    glm::quat orientation;

protected:
   
     /*
      Holds the inverse of the mass of the rigid body. 
      */
    float inverseMass;

    /*
    Holds mass
    */
    float mass;

    /*
     Holds the inverse of the body's inertia tensor. 
     */
    glm::mat3 inverseInertiaTensor;

    /*
     * Holds the amount of damping applied to linear
     */
    float linearDamping;

    /*
      Holds the amount of damping applied to angular
      motion. 
     */
    float angularDamping;

    /*
      Holds the linear position of the rigid body in
      world space.
     */
    vec3 position;


    /*
      Holds the linear velocity of the rigid body in
      world space.
     */
    vec3 velocity = vec3(0.0f);

    /*
      Holds the angular velocity, or rotation, or the
      rigid body in world space.
     */
    vec3 rotation = vec3(0.0f);

    /*
      Holds the angular acceleration
     */
    vec3 angularAcceleration = vec3(0.0f);

     /*
       Holds the inverse inertia tensor of the body in world
       space.
      */
    glm::mat3 inverseInertiaTensorWorld;

    /*
     Holds a transform matrix for converting body space into
     world space and vice versa.
     */
    glm::mat4 transformMatrix;

     /**
      * Holds the accumulated force to be applied at the next
      * integration step.
      */
    vec3 forceAccum = vec3(0.0f);

    /*
      Holds the accumulated torque to be applied at the next
      integration step.
     */
    vec3 torqueAccum = vec3(0.0f);

    /*
      Holds the acceleration of the rigid body.  
     */
    vec3 acceleration = vec3(0.0f);

    /**
     * Holds the linear acceleration of the rigid body, for the
     * previous frame.
     */
    vec3 lastFrameAcceleration = vec3(0.0f);


    /*External Resource for computing Quat*/
    vec3 pointImpact = vec3(0.0f);
    vec3 axisRotation = vec3(0.0f);
    float speed = 0;
    float theta = 0;
    glm::mat4 extraTransformMat = glm::mat4(1.0f);



public:

      /*
        Calculates internal data from state data. 
       */
    void calculateDerivedData();

    /*
      Integrates the rigid body forward in time by the given amount.
     */
    void integrate(float duration);

     /*
       Sets the mass of the rigid body.
      */
    void setMass(const float mass);
    float getMass() const;

    /*
     Sets the inverse mass of the rigid body.
     */
    void setInverseMass(const float inverseMass);
    float getInverseMass() const;

    /*
     Returns true if the mass of the body is not-infinite.
     */
    bool hasFiniteMass() const;

    /*
     Sets the intertia tensor for the rigid body.
     */
    void setInertiaTensor(const glm::mat3& inertiaTensor);


    /*
    *IMPORTANT:
    *For cuboid, set massand set length first
    */
    void setInertiaTensorCuboid(float dimensionx, float dimensiony, float dimensionz);

    /**
     Copies the current inertia tensor of the rigid body into
     the given matrix.
     */
    void getInertiaTensor(glm::mat3 *inertiaTensor) const;

    /*
     Gets a copy of the current inertia tensor of the rigid body.
     */
    glm::mat3 getInertiaTensor() const;

    /*
      Copies the current inertia tensor of the rigid body into
      the given matrix.
     */
    void getInertiaTensorWorld(glm::mat3* inertiaTensor) const;

    /*
      Gets a copy of the current inertia tensor of the rigid body.
     */
    glm::mat3 getInertiaTensorWorld() const;

    /*
      Sets the inverse intertia tensor for the rigid body.
     */
    void setInverseInertiaTensor(const glm::mat3& inverseInertiaTensor);

    /**
      Copies the current inverse inertia tensor of the rigid body
      into the given matrix.
     
      @param inverseInertiaTensor A pointer to a matrix to hold
      the current inverse inertia tensor of the rigid body. The
      inertia tensor is expressed in the rigid body's local
      space.
     */
    void getInverseInertiaTensor(glm::mat3* inverseInertiaTensor) const;

    /*
      Gets a copy of the current inverse inertia tensor of the
      rigid body.
     */
    glm::mat3 getInverseInertiaTensor() const;

    /*
      Copies the current inverse inertia tensor of the rigid body
      into the given matrix.
     */
    void getInverseInertiaTensorWorld(glm::mat3* inverseInertiaTensor) const;

    /*
      Gets a copy of the current inverse inertia tensor of the
      rigid body.
     */
    glm::mat3 getInverseInertiaTensorWorld() const;

    /*
      Sets both linear and angular damping in one function call.
     */
    void setDamping(const float linearDamping, const float angularDamping);

    /*
      Sets the linear damping for the rigid body.
     */
    void setLinearDamping(const float linearDamping);

    /*
      Gets the current linear damping value.
     */
    float getLinearDamping() const;

    /*
      Sets the angular damping for the rigid body.
    */
    void setAngularDamping(const float angularDamping);

    /*
      Gets the current angular damping value.
     */
    float getAngularDamping() const;

    /**
     * Sets the position of the rigid body.
     *
     * @param position The new position of the rigid body.
     */
    void setPosition(const vec3& position);

    /*
     * Sets the position of the rigid body by component.
     */
    void setPosition(const float x, const float y, const float z);

    /*
     * Fills the given vector with the position of the rigid body.
     */
    void getPosition(vec3* position) const;

    /*
      Gets the position of the rigid body.
     */
    vec3 getPosition() const;

    /*
      Gets a transformation representing the rigid body's
      position and orientation.
     */
    glm::mat4 getTransform() const;

    /**
     Converts the given point from world space into the body's
     local space.
     */
    vec3 getPointInWorldSpace(const vec3& point) const;

    /*
     Sets the velocity of the rigid body.
     */
    void setVelocity(const vec3& velocity);

    /*
      Sets the velocity of the rigid body by component. The
      velocity is given in world space.
     */
    void setVelocity(const float x, const float y, const float z);

    /*
      Fills the given vector with the velocity of the rigid body.
     */
    void getVelocity(vec3* velocity) const;

    /*
      Gets the velocity of the rigid body.
     */
    vec3 getVelocity() const;

    /*
      Applies the given change in velocity.
     */
    void addVelocity(const vec3& deltaVelocity);

    /*
      Sets the rotation of the rigid body.
     */
    void setRotation(const vec3& rotation);

    /*
      Sets the rotation of the rigid body by component. The
      rotation is given in world space.
     */
    void setRotation(const float x, const float y, const float z);

    /*
      Fills the given vector with the rotation of the rigid body.
     */
    void getRotation(vec3* rotation) const;

    /*
     * Gets the rotation of the rigid body.
     */
    vec3 getRotation() const;

    /**
      Applies the given change in rotation.
     */
    void addRotation(const vec3& deltaRotation);

     /*
       Fills the given vector with the current accumulated value
       for linear acceleration.
      */
    void getLastFrameAcceleration(vec3* linearAcceleration) const;

    /*
      Gets the current accumulated value for linear
      acceleration. 
     */
    vec3 getLastFrameAcceleration() const;

     /*
       Clears the forces and torques in the accumulators.
      */
    void clearAccumulators();

    /*
      Adds the given force to centre of mass of the rigid body.
     */
    void addForce(const vec3& force);

    /*
     Adds the given force to the given point on the rigid body.
     Both the force and the application point are given in world space. Because the
     force is not applied at the centre of mass, it may be split
     into both a force and torque.
     */
    void addForceAtPoint(const vec3& force, const vec3& point);

    /*
      Adds the given force to the given point on the rigid body.
     */
    void addForceAtBodyPoint(const vec3& force, const vec3& point);

    /*
      Adds the given torque to the rigid body.
     */
    void addTorque(const vec3& torque);

    /*
      Sets the constant acceleration of the rigid body.
     */
    void setAcceleration(const vec3& acceleration);

    /*
      Sets the constant acceleration of the rigid body by component.
     */
    void setAcceleration(const float x, const float y, const float z);

    /*
      Fills the given vector with the acceleration of the rigid body.
     */
    void getAcceleration(vec3* acceleration) const;

    /*
      Gets the acceleration of the rigid body.
     */
    vec3 getAcceleration() const;
};



