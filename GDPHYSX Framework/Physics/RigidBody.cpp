#include "RigidBody.h"

/**
 * Inline function that creates a transform matrix from a
 * position and orientation.
 */
static inline void _calculateTransformMatrix(glm::mat4& transformMatrix,
    const glm::vec3& position,
    const glm::quat& orientation)
{
    transformMatrix[0][0] = 1.0f - 2.0f * orientation.y * orientation.y - 
        2.0f * orientation.z * orientation.z;
    transformMatrix[0][1] = 2.0f * orientation.x * orientation.y -
        2.0f * orientation.w * orientation.z;
    transformMatrix[0][2] = 2.0f * orientation.x * orientation.z +
        2.0f * orientation.w * orientation.y;
    transformMatrix[0][3] = position.x;

    transformMatrix[1][0] = 2.0f * orientation.x * orientation.y +
        2.0f * orientation.w * orientation.z;
    transformMatrix[1][1] = 1 - 2.0f * orientation.x * orientation.x -
        2.0f * orientation.z * orientation.z;
    transformMatrix[1][2] = 2.0f * orientation.y * orientation.z -
        2.0f * orientation.w * orientation.x;
    transformMatrix[1][3] = position.y;

    transformMatrix[2][0] = 2.0f * orientation.x * orientation.z -
        2.0f * orientation.w * orientation.y;
    transformMatrix[2][1] = 2.0f * orientation.y * orientation.z +
        2.0f * orientation.w * orientation.x;
    transformMatrix[2][2] = 1 - 2.0f * orientation.x * orientation.x -
        2.0f * orientation.y * orientation.y;
    transformMatrix[2][3] = position.z;
}

RigidBody::RigidBody()
{
    this->setPosition(vec3(0));
    this->setMass(1);
    this->rotation = vec3(0);
    


}

void RigidBody::calculateDerivedData()
{
    glm::normalize(orientation);

    // Calculate the transform matrix for the body.
    _calculateTransformMatrix(transformMatrix, position, orientation);

    /*
    // Calculate the inertiaTensor in world space.
    _transformInertiaTensor(inverseInertiaTensorWorld,
        orientation,
        inverseInertiaTensor,
        transformMatrix);
    */
}

void RigidBody::integrate(float deltaTime)
{
    // Calculate linear acceleration from force inputs.
    lastFrameAcceleration = acceleration;
    lastFrameAcceleration += forceAccum * inverseMass;

    // Calculate angular acceleration from torque inputs.
    glm::vec3 angularAcceleration = inverseInertiaTensorWorld * torqueAccum;

    // Adjust velocities
    // Update linear velocity from both acceleration and impulse.
    velocity += lastFrameAcceleration * deltaTime;

    // Update angular velocity from both acceleration and impulse.
    rotation += angularAcceleration * deltaTime;

    // Impose drag.
    velocity *= powf(linearDamping, deltaTime);
    rotation *= powf(angularDamping, deltaTime);

    // Adjust positions
    // Update linear position.
    position += velocity * deltaTime;

    // Update angular position.
    orientation.x += rotation.x * deltaTime;
    orientation.y += rotation.y * deltaTime;
    orientation.z += rotation.z * deltaTime;
    orientation.w = 1.0f; // testing, can be changed

    // Normalise the orientation, and update the matrices with the new
    // position and orientation
    calculateDerivedData();

    clearAccumulators();
}

void RigidBody::setMass(const float mass)
{
    if (mass != 0)
    {
        inverseMass = 1.0f / mass;
    }
}

float RigidBody::getMass() const
{
    if (inverseMass == 0) {
        //return REAL_MAX;
        return inverseMass;
    }
    else {
        return 1.0f / inverseMass;
    }
}

void RigidBody::setInverseMass(const float inverseMass)
{
    RigidBody::inverseMass = inverseMass;
}

float RigidBody::getInverseMass() const
{
    return inverseMass;
}

bool RigidBody::hasFiniteMass() const
{
    return inverseMass >= 0.0f;
}

/**
 * Internal function that checks the validity of an inverse inertia tensor.
 */
static inline void _checkInverseInertiaTensor(const glm::mat3& iitWorld)
{
    // TODO: Perform a validity check in an assert.
}

void RigidBody::setInertiaTensor(const glm::mat3& inertiaTensor)
{
   inverseInertiaTensor = glm::inverse(inertiaTensor);
   _checkInverseInertiaTensor(inverseInertiaTensor);
}

void RigidBody::getInertiaTensor(glm::mat3 *inertiaTensor) const
{
    *inertiaTensor = glm::inverse(inverseInertiaTensor);
}

glm::mat3 RigidBody::getInertiaTensor() const
{
    glm::mat3 it;
    getInertiaTensor(&it);
    return it;
}

void RigidBody::getInertiaTensorWorld(glm::mat3* inertiaTensor) const
{
    *inertiaTensor = glm::inverse(inverseInertiaTensorWorld);
}

glm::mat3 RigidBody::getInertiaTensorWorld() const
{
    glm::mat3 it;
    getInertiaTensorWorld(&it);
    return it;
}

void RigidBody::setInverseInertiaTensor(const glm::mat3& inverseInertiaTensor)
{
    _checkInverseInertiaTensor(inverseInertiaTensor);
    RigidBody::inverseInertiaTensor = inverseInertiaTensor;
}

void RigidBody::getInverseInertiaTensor(glm::mat3* inverseInertiaTensor) const
{
    *inverseInertiaTensor = RigidBody::inverseInertiaTensor;
}

glm::mat3 RigidBody::getInverseInertiaTensor() const
{
    return inverseInertiaTensor;
}

void RigidBody::getInverseInertiaTensorWorld(glm::mat3* inverseInertiaTensor) const
{
    *inverseInertiaTensor = inverseInertiaTensorWorld;
}

glm::mat3 RigidBody::getInverseInertiaTensorWorld() const
{
    return inverseInertiaTensorWorld;
}

void RigidBody::clearAccumulators()
{
    // Clear accumulated force and torque
    forceAccum = glm::vec3(0, 0, 0);
    torqueAccum = glm::vec3(0, 0, 0);
}

void RigidBody::addForce(const vec3& force)
{
    forceAccum += force;
}

void RigidBody::addForceAtPoint(const vec3& force, const vec3& point)
{
    // Convert to coordinates relative to center of mass.
    glm::vec3 pt = point;
    pt -= position;

    forceAccum += force;
    //torqueAccum += pt % force;
}

glm::vec3 RigidBody::getPointInWorldSpace(const glm::vec3& point) const
{
    // Could have errors
    glm::vec4 vec4point = transformMatrix * glm::vec4(point.x, point.y, point.z, 1.0f);
    return glm::vec3(vec4point);
    
}

vec3 RigidBody::getDirectionInLocalSpace(const vec3& direction) const
{
    /* original code
    return transformMatrix.transformInverseDirection(direction);
    */
    glm::vec4 vec4point = glm::inverse(transformMatrix) * glm::vec4(direction.x, direction.y, direction.z, 1.0f);
    return glm::vec3(vec4point);
}

vec3 RigidBody::getDirectionInWorldSpace(const vec3& direction) const
{
    glm::vec4 vec4point = transformMatrix * glm::vec4(direction.x, direction.y, direction.z, 1.0f);
    return glm::vec3(vec4point);
}

void RigidBody::setVelocity(const vec3& velocity)
{
    RigidBody::velocity = velocity;
}

void RigidBody::setVelocity(const float x, const float y, const float z)
{
    velocity.x = x;
    velocity.y = y;
    velocity.z = z;
}

void RigidBody::getVelocity(vec3* velocity) const
{
    *velocity = RigidBody::velocity;
}

vec3 RigidBody::getVelocity() const
{
    return velocity;
}

void RigidBody::addVelocity(const vec3& deltaVelocity)
{
    velocity += deltaVelocity;
}

void RigidBody::setRotation(const vec3& rotation)
{
    RigidBody::rotation = rotation;
}

void RigidBody::setRotation(const float x, const float y, const float z)
{
    rotation.x = x;
    rotation.y = y;
    rotation.z = z;
}

void RigidBody::getRotation(vec3* rotation) const
{
    *rotation = RigidBody::rotation;
}

vec3 RigidBody::getRotation() const
{
    return rotation;
}

void RigidBody::addRotation(const vec3& deltaRotation)
{
    rotation += deltaRotation;
}

void RigidBody::getLastFrameAcceleration(vec3* linearAcceleration) const
{
    *linearAcceleration = lastFrameAcceleration;
}

vec3 RigidBody::getLastFrameAcceleration() const
{
    return lastFrameAcceleration;
}

void RigidBody::addForceAtBodyPoint(const vec3& force, const vec3& point)
{
    // Convert to coordinates relative to center of mass.
    glm::vec3 pt = getPointInWorldSpace(point);
    addForceAtPoint(force, pt);
}

void RigidBody::addTorque(const vec3& torque)
{
    torqueAccum += torque;
}

void RigidBody::setAcceleration(const vec3& acceleration)
{
    RigidBody::acceleration = acceleration;
}

void RigidBody::setAcceleration(const float x, const float y, const float z)
{
    acceleration.x = x;
    acceleration.y = y;
    acceleration.z = z;
}

void RigidBody::getAcceleration(vec3* acceleration) const
{
    *acceleration = RigidBody::acceleration;
}

vec3 RigidBody::getAcceleration() const
{
    return acceleration;
}

void RigidBody::setDamping(const float linearDamping, const float angularDamping)
{
    RigidBody::linearDamping = linearDamping;
    RigidBody::angularDamping = angularDamping;
}

void RigidBody::setLinearDamping(const float linearDamping)
{
    RigidBody::linearDamping = linearDamping;
}

float RigidBody::getLinearDamping() const
{
    return linearDamping;;
}

void RigidBody::setAngularDamping(const float angularDamping)
{
    RigidBody::angularDamping = angularDamping;
}

float RigidBody::getAngularDamping() const
{
    return angularDamping;
}

void RigidBody::setPosition(const vec3& position)
{
    RigidBody::position = position;
}

void RigidBody::setPosition(const float x, const float y, const float z)
{
    position.x = x;
    position.y = y;
    position.z = z;
}

void RigidBody::getPosition(vec3* position) const
{
    *position = RigidBody::position;
}

vec3 RigidBody::getPosition() const
{
    return position;
}

void RigidBody::setOrientation(const glm::quat& orientation)
{
    RigidBody::orientation = orientation;
    glm::normalize(RigidBody::orientation);
}

void RigidBody::setOrientation(const float r, const float i, const float j, const float k)
{
    orientation.x = r;
    orientation.y = i;
    orientation.z = j;
    orientation.w = k;
    glm::normalize(orientation);
}

void RigidBody::getOrientation(glm::quat* orientation) const
{
    *orientation = RigidBody::orientation;
}

glm::quat RigidBody::getOrientation() const
{
    return orientation;
}

void RigidBody::getOrientation(glm::mat3* matrix) const
{
    getOrientation(matrix);
}

void RigidBody::getOrientation(float matrix[9]) const
{
    matrix[0] = transformMatrix[0][0];
    matrix[1] = transformMatrix[0][1];
    matrix[2] = transformMatrix[0][2];

    matrix[3] = transformMatrix[1][0];
    matrix[4] = transformMatrix[1][1];
    matrix[5] = transformMatrix[1][2];

    matrix[6] = transformMatrix[2][0];
    matrix[7] = transformMatrix[2][1];
    matrix[8] = transformMatrix[2][2];
}

void RigidBody::getTransform(glm::mat4* transform) const
{
    // omitted
}

void RigidBody::getTransform(float matrix[16]) const
{
    // omitted

}

void RigidBody::getGLTransform(float matrix[16]) const
{
    // omitted

}

glm::mat4 RigidBody::getTransform() const
{
    return transformMatrix;
}

vec3 RigidBody::getPointInLocalSpace(const vec3& point) const
{
    glm::vec4 vec4point = glm::inverse(transformMatrix) * glm::vec4(point.x, point.y, point.z, 1.0f);
    return glm::vec3(vec4point);
}
