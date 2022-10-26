#include "AnchorSpringObject.h"

AnchorSpringObject::AnchorSpringObject(std::string name, ObjectType objType, GLFWwindow* currWindow): 
	Model(name, objType, currWindow)
{
    //Create an active spring
    this->aSpring = new ParticleAnchoredSpring(&anchorPos, 0.000002f, 1.0f);
    this->particle = new Particle();


	//Debug Only Remove when not needed
    particle->setVelocity(vec3(0,0, 1.0f));
    particle->setDamping(0.01f);
    //particle->toogleGravity(true);
	///

    particle->setMass(1.0f);
	
	

}

void AnchorSpringObject::setStartPos(glm::vec3 Pos)
{
    particle->setPosition(Pos);

}

void AnchorSpringObject::update(float timeStep)
{
	//aSpring->updateForce(particle, timeStep);
    particle->updatePosition(timeStep);

}

void AnchorSpringObject::draw()
{
    glBindVertexArray(0);
    //float time = glfwGetTime();
    //Apply Linear Transformation (Default)
    glm::mat4 identity = glm::mat4(1.0f);
    glm::mat4 transform = glm::translate(identity, particle->getPosition());

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

