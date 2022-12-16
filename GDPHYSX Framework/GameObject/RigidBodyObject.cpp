#include "RigidBodyObject.h"

RigidBodyObject::RigidBodyObject(std::string name, ObjectType objType, GLFWwindow* currWindow) : Model(name, objType, currWindow), RigidBody()
{
	//Insert if needed

}

void RigidBodyObject::update(float timeStep)
{

}

void RigidBodyObject::draw()
{
    glBindVertexArray(0);
    //float time = glfwGetTime();
    //Apply Linear Transformation (Default)
    glm::mat4 identity = glm::mat4(1.0f);
    glm::mat4 transform = glm::translate(identity, this->getPosition());

    transform = glm::scale(transform, objScale);

    //Default
   /* transform = glm::rotate(transform, glm::radians(objRotation.x), glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, glm::radians(objRotation.y), glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, glm::radians(objRotation.z), glm::vec3(0, 0, 1));*/

    
    //With Rigid Bodies
    transform = glm::rotate(transform, glm::radians(this->rotation.x), glm::vec3(0, 1, 0));
    transform = glm::rotate(transform, glm::radians(this->rotation.y), glm::vec3(1, 0, 0));
    transform = glm::rotate(transform, glm::radians(this->rotation.z), glm::vec3(0, 0, 1));




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
