#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

typedef glm::vec3 vec3;

class RigidBody
{
public:

    RigidBody();

    // ... Other RigidBody code as before ...


protected:
   
     /*
      Holds the inverse of the mass of the rigid body. 
      */
    float inverseMass;

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
      motion.  Damping is required to remove energy added
      through numerical instability in the integrator.
     */
    float angularDamping;

    /*
      Holds the linear position of the rigid body in
      world space.
     */
    vec3 position;

    /*
      Holds the angular orientation of the rigid body in
      world space.
     */
    glm::quat orientation;

    /*
      Holds the linear velocity of the rigid body in
      world space.
     */
    vec3 velocity;

    /*
      Holds the angular velocity, or rotation, or the
      rigid body in world space.
     */
    vec3 rotation;

     /*
       Holds the inverse inertia tensor of the body in world
       space. The inverse inertia tensor member is specified in
       the body's local space.
      */
    glm::mat3 inverseInertiaTensorWorld;

    /*
     Holds a transform matrix for converting body space into
     world space and vice versa. This can be achieved by calling
     the getPointIn*Space functions.
     */
    glm::mat4 transformMatrix;

     /**
      * Holds the accumulated force to be applied at the next
      * integration step.
      */
    vec3 forceAccum;

    /*
      Holds the accumulated torque to be applied at the next
      integration step.
     */
    vec3 torqueAccum;

    /*
      Holds the acceleration of the rigid body.  This value
      can be used to set acceleration due to gravity (its primary
      use), or any other constant acceleration.
     */
    vec3 acceleration;

    /**
     * Holds the linear acceleration of the rigid body, for the
     * previous frame.
     */
    vec3 lastFrameAcceleration;

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
      * Sets the mass of the rigid body.
      */
    void setMass(const float mass);
    float getMass() const;

    /*
     * Sets the inverse mass of the rigid body.
     */
    void setInverseMass(const float inverseMass);
    float getInverseMass() const;

    /*
     Returns true if the mass of the body is not-infinite.
     */
    bool hasFiniteMass() const;

    /**
     * Sets the intertia tensor for the rigid body.
     *
     * @param inertiaTensor The inertia tensor for the rigid
     * body. This must be a full rank matrix and must be
     * invertible.
     *
     * @warning This invalidates internal data for the rigid body.
     * Either an integration function, or the calculateInternals
     * function should be called before trying to get any settings
     * from the rigid body.
     */
    void setInertiaTensor(const glm::mat3& inertiaTensor);


    /*
    *IMPORTANT:
    *For cuboid, set massand set length first
    */
    void setInertiaTensorCuboid(float dimensionx, float dimensiony, float dimensionz);

    /**
     * Copies the current inertia tensor of the rigid body into
     * the given matrix.
     *
     * @param inertiaTensor A pointer to a matrix to hold the
     * current inertia tensor of the rigid body. The inertia
     * tensor is expressed in the rigid body's local space.
     */
    void getInertiaTensor(glm::mat3 *inertiaTensor) const;

    /**
     * Gets a copy of the current inertia tensor of the rigid body.
     *
     * @return A new matrix containing the current intertia
     * tensor. The inertia tensor is expressed in the rigid body's
     * local space.
     */
    glm::mat3 getInertiaTensor() const;

    /**
     * Copies the current inertia tensor of the rigid body into
     * the given matrix.
     *
     * @param inertiaTensor A pointer to a matrix to hold the
     * current inertia tensor of the rigid body. The inertia
     * tensor is expressed in world space.
     */
    void getInertiaTensorWorld(glm::mat3* inertiaTensor) const;

    /**
     * Gets a copy of the current inertia tensor of the rigid body.
     *
     * @return A new matrix containing the current intertia
     * tensor. The inertia tensor is expressed in world space.
     */
    glm::mat3 getInertiaTensorWorld() const;

    /**
     * Sets the inverse intertia tensor for the rigid body.
     *
     * @param inverseInertiaTensor The inverse inertia tensor for
     * the rigid body. This must be a full rank matrix and must be
     * invertible.
     *
     * @warning This invalidates internal data for the rigid body.
     * Either an integration function, or the calculateInternals
     * function should be called before trying to get any settings
     * from the rigid body.
     */
    void setInverseInertiaTensor(const glm::mat3& inverseInertiaTensor);

    /**
     * Copies the current inverse inertia tensor of the rigid body
     * into the given matrix.
     *
     * @param inverseInertiaTensor A pointer to a matrix to hold
     * the current inverse inertia tensor of the rigid body. The
     * inertia tensor is expressed in the rigid body's local
     * space.
     */
    void getInverseInertiaTensor(glm::mat3* inverseInertiaTensor) const;

    /**
     * Gets a copy of the current inverse inertia tensor of the
     * rigid body.
     *
     * @return A new matrix containing the current inverse
     * intertia tensor. The inertia tensor is expressed in the
     * rigid body's local space.
     */
    glm::mat3 getInverseInertiaTensor() const;

    /**
     * Copies the current inverse inertia tensor of the rigid body
     * into the given matrix.
     *
     * @param inverseInertiaTensor A pointer to a matrix to hold
     * the current inverse inertia tensor of the rigid body. The
     * inertia tensor is expressed in world space.
     */
    void getInverseInertiaTensorWorld(glm::mat3* inverseInertiaTensor) const;

    /**
     * Gets a copy of the current inverse inertia tensor of the
     * rigid body.
     *
     * @return A new matrix containing the current inverse
     * intertia tensor. The inertia tensor is expressed in world
     * space.
     */
    glm::mat3 getInverseInertiaTensorWorld() const;

    /**
     * Sets both linear and angular damping in one function call.
     *
     * @param linearDamping The speed that velocity is shed from
     * the rigid body.
     *
     * @param angularDamping The speed that rotation is shed from
     * the rigid body.
     *
     * @see setLinearDamping
     * @see setAngularDamping
     */
    void setDamping(const float linearDamping, const float angularDamping);

    /**
     * Sets the linear damping for the rigid body.
     *
     * @param linearDamping The speed that velocity is shed from
     * the rigid body.
     *
     * @see setAngularDamping
     */
    void setLinearDamping(const float linearDamping);

    /**
     * Gets the current linear damping value.
     *
     * @return The current linear damping value.
     */
    float getLinearDamping() const;

    /**
     * Sets the angular damping for the rigid body.
     *
     * @param angularDamping The speed that rotation is shed from
     * the rigid body.
     *
     * @see setLinearDamping
     */
    void setAngularDamping(const float angularDamping);

    /**
     * Gets the current angular damping value.
     *
     * @return The current angular damping value.
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

    /**
     * Gets the position of the rigid body.
     *
     * @return The position of the rigid body.
     */
    vec3 getPosition() const;

    /**
     * Sets the orientation of the rigid body.
     *
     * @param orientation The new orientation of the rigid body.
     *
     * @note The given orientation does not need to be normalised,
     * and can be zero. This function automatically constructs a
     * valid rotation glm::quat with (0,0,0,0) mapping to
     * (1,0,0,0).
     */
    void setOrientation(const glm::quat& orientation);

    /**
     * Sets the orientation of the rigid body by component.
     *
     * @param r The float component of the rigid body's orientation
     * glm::quat.
     *
     * @param i The first complex component of the rigid body's
     * orientation glm::quat.
     *
     * @param j The second complex component of the rigid body's
     * orientation glm::quat.
     *
     * @param k The third complex component of the rigid body's
     * orientation glm::quat.
     *
     * @note The given orientation does not need to be normalised,
     * and can be zero. This function automatically constructs a
     * valid rotation glm::quat with (0,0,0,0) mapping to
     * (1,0,0,0).
     */
    void setOrientation(const float r, const float i,
        const float j, const float k);

    /**
     * Fills the given glm::quat with the current value of the
     * rigid body's orientation.
     *
     * @param orientation A pointer to a glm::quat to receive the
     * orientation data.
     */
    void getOrientation(glm::quat* orientation) const;

    /**
     * Gets the orientation of the rigid body.
     *
     * @return The orientation of the rigid body.
     */
    glm::quat getOrientation() const;

    /**
     * Fills the given matrix with a transformation representing
     * the rigid body's orientation.
     *
     * @note Transforming a direction vector by this matrix turns
     * it from the body's local space to world space.
     *
     * @param matrix A pointer to the matrix to fill.
     */
    void getOrientation(glm::mat3* matrix) const;

    /**
     * Fills the given matrix data structure with a transformation
     * representing the rigid body's orientation.
     *
     * @note Transforming a direction vector by this matrix turns
     * it from the body's local space to world space.
     *
     * @param matrix A pointer to the matrix to fill.
     */
    void getOrientation(float matrix[9]) const;

    /**
     * Fills the given matrix with a transformation representing
     * the rigid body's position and orientation.
     *
     * @note Transforming a vector by this matrix turns it from
     * the body's local space to world space.
     *
     * @param transform A pointer to the matrix to fill.
     */
    void getTransform(glm::mat4* transform) const;

    /**
     * Fills the given matrix data structure with a
     * transformation representing the rigid body's position and
     * orientation.
     *
     * @note Transforming a vector by this matrix turns it from
     * the body's local space to world space.
     *
     * @param matrix A pointer to the matrix to fill.
     */
    void getTransform(float matrix[16]) const;

    /**
     * Fills the given matrix data structure with a
     * transformation representing the rigid body's position and
     * orientation. The matrix is transposed from that returned
     * by getTransform. This call returns a matrix suitable
     * for applying as an OpenGL transform.
     *
     * @note Transforming a vector by this matrix turns it from
     * the body's local space to world space.
     *
     * @param matrix A pointer to the matrix to fill.
     */
    void getGLTransform(float matrix[16]) const;

    /**
     * Gets a transformation representing the rigid body's
     * position and orientation.
     *
     * @note Transforming a vector by this matrix turns it from
     * the body's local space to world space.
     *
     * @return The transform matrix for the rigid body.
     */
    glm::mat4 getTransform() const;

    /**
     * Converts the given point from world space into the body's
     * local space.
     *
     * @param point The point to covert, given in world space.
     *
     * @return The converted point, in local space.
     */
    vec3 getPointInLocalSpace(const vec3& point) const;

    /**
     * Converts the given point from world space into the body's
     * local space.
     *
     * @param point The point to covert, given in local space.
     *
     * @return The converted point, in world space.
     */
    vec3 getPointInWorldSpace(const vec3& point) const;

    /**
     * Converts the given direction from world space into the
     * body's local space.
     *
     * @note When a direction is converted between frames of
     * reference, there is no translation required.
     *
     * @param direction The direction to covert, given in world
     * space.
     *
     * @return The converted direction, in local space.
     */
    vec3 getDirectionInLocalSpace(const vec3& direction) const;

    /**
     * Converts the given direction from world space into the
     * body's local space.
     *
     * @note When a direction is converted between frames of
     * reference, there is no translation required.
     *
     * @param direction The direction to covert, given in local
     * space.
     *
     * @return The converted direction, in world space.
     */
    vec3 getDirectionInWorldSpace(const vec3& direction) const;

    /**
     * Sets the velocity of the rigid body.
     *
     * @param velocity The new velocity of the rigid body. The
     * velocity is given in world space.
     */
    void setVelocity(const vec3& velocity);

    /**
     * Sets the velocity of the rigid body by component. The
     * velocity is given in world space.
     *
     * @param x The x coordinate of the new velocity of the rigid
     * body.
     *
     * @param y The y coordinate of the new velocity of the rigid
     * body.
     *
     * @param z The z coordinate of the new velocity of the rigid
     * body.
     */
    void setVelocity(const float x, const float y, const float z);

    /**
     * Fills the given vector with the velocity of the rigid body.
     *
     * @param velocity A pointer to a vector into which to write
     * the velocity. The velocity is given in world local space.
     */
    void getVelocity(vec3* velocity) const;

    /**
     * Gets the velocity of the rigid body.
     *
     * @return The velocity of the rigid body. The velocity is
     * given in world local space.
     */
    vec3 getVelocity() const;

    /**
     * Applies the given change in velocity.
     */
    void addVelocity(const vec3& deltaVelocity);

    /**
     * Sets the rotation of the rigid body.
     *
     * @param rotation The new rotation of the rigid body. The
     * rotation is given in world space.
     */
    void setRotation(const vec3& rotation);

    /**
     * Sets the rotation of the rigid body by component. The
     * rotation is given in world space.
     *
     * @param x The x coordinate of the new rotation of the rigid
     * body.
     *
     * @param y The y coordinate of the new rotation of the rigid
     * body.
     *
     * @param z The z coordinate of the new rotation of the rigid
     * body.
     */
    void setRotation(const float x, const float y, const float z);

    /**
     * Fills the given vector with the rotation of the rigid body.
     *
     * @param rotation A pointer to a vector into which to write
     * the rotation. The rotation is given in world local space.
     */
    void getRotation(vec3* rotation) const;

    /**
     * Gets the rotation of the rigid body.
     *
     * @return The rotation of the rigid body. The rotation is
     * given in world local space.
     */
    vec3 getRotation() const;

    /**
     * Applies the given change in rotation.
     */
    void addRotation(const vec3& deltaRotation);


    /**
     * @name Retrieval Functions for Dynamic Quantities
     *
     * These functions provide access to the acceleration
     * properties of the body. The acceleration is generated by
     * the simulation from the forces and torques applied to the
     * rigid body. Acceleration cannot be directly influenced, it
     * is set during integration, and represent the acceleration
     * experienced by the body of the previous simulation step.
     */
     /*@{*/

     /**
      * Fills the given vector with the current accumulated value
      * for linear acceleration. The acceleration accumulators
      * are set during the integration step. They can be read to
      * determine the rigid body's acceleration over the last
      * integration step. The linear acceleration is given in world
      * space.
      *
      * @param linearAcceleration A pointer to a vector to receive
      * the linear acceleration data.
      */
    void getLastFrameAcceleration(vec3* linearAcceleration) const;

    /**
     * Gets the current accumulated value for linear
     * acceleration. The acceleration accumulators are set during
     * the integration step. They can be read to determine the
     * rigid body's acceleration over the last integration
     * step. The linear acceleration is given in world space.
     *
     * @return The rigid body's linear acceleration.
     */
    vec3 getLastFrameAcceleration() const;

    /*@}*/


    /**
     * @name Force, Torque and Acceleration Set-up Functions
     *
     * These functions set up forces and torques to apply to the
     * rigid body.
     */
     /*@{*/

     /**
      * Clears the forces and torques in the accumulators. This will
      * be called automatically after each intergration step.
      */
    void clearAccumulators();

    /*
      Adds the given force to centre of mass of the rigid body.
      The force is expressed in world-coordinates.
     */
    void addForce(const vec3& force);

    /**
     * Adds the given force to the given point on the rigid body.
     * Both the force and the
     * application point are given in world space. Because the
     * force is not applied at the centre of mass, it may be split
     * into both a force and torque.
     *
     * @param force The force to apply.
     *
     * @param point The location at which to apply the force, in
     * world-coordinates.
     */
    void addForceAtPoint(const vec3& force, const vec3& point);

    /**
     * Adds the given force to the given point on the rigid body.
     * The direction of the force is given in world coordinates,
     * but the application point is given in body space. This is
     * useful for spring forces, or other forces fixed to the
     * body.
     *
     * @param force The force to apply.
     *
     * @param point The location at which to apply the force, in
     * body-coordinates.
     */
    void addForceAtBodyPoint(const vec3& force, const vec3& point);

    /**
     * Adds the given torque to the rigid body.
     * The force is expressed in world-coordinates.
     *
     * @param torque The torque to apply.
     */
    void addTorque(const vec3& torque);

    /**
     * Sets the constant acceleration of the rigid body.
     *
     * @param acceleration The new acceleration of the rigid body.
     */
    void setAcceleration(const vec3& acceleration);

    /**
     * Sets the constant acceleration of the rigid body by component.
     *
     * @param x The x coordinate of the new acceleration of the rigid
     * body.
     *
     * @param y The y coordinate of the new acceleration of the rigid
     * body.
     *
     * @param z The z coordinate of the new acceleration of the rigid
     * body.
     */
    void setAcceleration(const float x, const float y, const float z);

    /**
     * Fills the given vector with the acceleration of the rigid body.
     *
     * @param acceleration A pointer to a vector into which to write
     * the acceleration. The acceleration is given in world local space.
     */
    void getAcceleration(vec3* acceleration) const;

    /**
     * Gets the acceleration of the rigid body.
     *
     * @return The acceleration of the rigid body. The acceleration is
     * given in world local space.
     */
    vec3 getAcceleration() const;
};



