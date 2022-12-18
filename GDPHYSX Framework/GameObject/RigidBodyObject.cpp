#include "RigidBodyObject.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

RigidBodyObject::RigidBodyObject(std::string name, ObjectType objType, GLFWwindow* currWindow) : Model(name, objType, currWindow), RigidBody()
{
	//Insert if needed

}

void RigidBodyObject::update(float timeStep)
{
    adjustTransFormMat(timeStep);

}

void RigidBodyObject::draw()
{
    glBindVertexArray(0);
    
    //Apply Linear Transformation (Default)
    glm::mat4 identity = glm::mat4(1.0f);
    glm::mat4 transform = identity;
    

    transform = glm::translate(transform, this->getPosition());
    transform[0].x = 0;
    transform[1].y = 0;
    transform[2].z = 0;
    transform[3].w = 0;

    transform = this->extraTransformMat + transform;
    transform[3].w = 1;

   
    transform = glm::scale(transform, objScale);


    glUseProgram(shader->getShaderProg());
    glBindVertexArray(VAO); // Render on the active
    shader->transformUpdate(transform);

    shader->projectionUpdate(retrieveCamProj());
    shader->viewUpdate(retrieveCamMat());

    if (objType == NoTexture) {
        //shader->LightUpdate(light);
    }

    if (objType == WithTexture) {
        glActiveTexture(GL_TEXTURE0);
        shader->textureUpdate(texture, "tex0", 0);
        shader->LightUpdate(light);
        shader->cameraUpdatePos(perspCam->getCameraPos());
    }

    glUseProgram(shader->getShaderProg());

    glBindVertexArray(VAO); // Render on the active
    glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 8);

}

bool RigidBodyObject::isParticleInside(vec3 pointPos)
{
    float halfL = length / 2.0f;

    return (
        pointPos.x >= this->getPosition().x - halfL &&
        pointPos.x <= this->getPosition().x + halfL &&
        pointPos.y >= this->getPosition().y - halfL &&
        pointPos.y <= this->getPosition().y + halfL &&
        pointPos.z >= this->getPosition().z - halfL &&
        pointPos.z <= this->getPosition().z + halfL
        );
        
}

void RigidBodyObject::setLength(float length)
{
    this->length = length;
    this->setInitialScale(vec3(this->length * (3.0f/4.0f)));
}

float RigidBodyObject::getLength()
{
    return length;
}

void RigidBodyObject::adjustTransFormMat(float timeStep)
{
    if(speed != 0){
        Quaterions calc;
        extraTransformMat = calc.getRotationMatrix(this->objPosition, this->axisRotation, theta);

        theta += speed * 1000 * timeStep;
    }
}
