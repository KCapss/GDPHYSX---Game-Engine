#include "ParticleObject.h"

ParticleObject::ParticleObject(std::string name, ObjectType objType, GLFWwindow* currWindow) :
	Model(name, objType, currWindow), Particle()
{

//Debug
	//Automatically Enable During Runtime; == Particle
    this->setMass(1.0f);
    this->setVelocity(vec3(0));
    this->toogleGravity(true);
    //this->setVelocity(vec3(0, 0, 100.f));

    
}

void ParticleObject::update(float timeStep)
{
    if (isHit)
        setActive(false);

    if (this->isSetActive()) {
        this->updatePosition(timeStep);
    }
	
}

void ParticleObject::draw()
{
    if (this->isSetActive()) {
        glBindVertexArray(0);
        //float time = glfwGetTime();
        //Apply Linear Transformation (Default)
        glm::mat4 identity = glm::mat4(1.0f);
        glm::mat4 transform = glm::translate(identity, this->getPosition());

        transform = glm::scale(transform, objScale);

        transform = glm::rotate(transform, glm::radians(objRotation.x), glm::vec3(0, 1, 0));
        transform = glm::rotate(transform, glm::radians(objRotation.y), glm::vec3(1, 0, 0));
        transform = glm::rotate(transform, glm::radians(objRotation.z), glm::vec3(0, 0, 1));




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
}
