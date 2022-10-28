#include "AnchorSpringObject.h"

AnchorSpringObject::AnchorSpringObject(std::string name, ObjectType objType, GLFWwindow* currWindow): 
	Model(name, objType, currWindow)
{
    //Create an active spring
    this->aSpringPhysics = new ParticleAnchoredSpring(&anchorPos, 0.8f, 100.0f);
    this->particle = new Particle();


	//Debug Only Remove when not needed
    particle->setVelocity(vec3(0,0,0));
    particle->setDamping(0.95f);
    particle->toogleGravity(true);
	///

    particle->setMass(10.0f);
	
	//Model Rendering
    refPoint = new Model(name, objType, currWindow);
    refPoint->setInitialPos(anchorPos);
    refPoint->setInitialScale(vec3(5.0f));

}

void AnchorSpringObject::setStartPos(glm::vec3 Pos)
{
    particle->setPosition(Pos);

}

void AnchorSpringObject::retrieveSource(Light* light, PerspectiveCamera* perspCam, OrthographicCamera* orthoCam)
{
    this->light = light;
    this->perspCam = perspCam;
    this->orthoCam = orthoCam;

    refPoint->retrieveSource(light, perspCam, orthoCam);

}


void AnchorSpringObject::update(float timeStep)
{
	//aSpringPhysics->updateForce(particle, timeStep);

    if (this->isSetActive()) {

        if (this->tick >= maxTime)
            this->setActive(false);

        tick += timeStep;
        particle->updatePosition(timeStep);
        refPoint->update(timeStep);
       
    }
 
    

}

void AnchorSpringObject::draw()
{
    if (this->isSetActive()) {

        glBindVertexArray(0);
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

        refPoint->draw();
    }
}

void AnchorSpringObject::reset()
{
    this->tick = 0;
    this->setActive(true);
    particle->setVelocity(vec3(0, 0, 5.0f));
    particle->setPosition(vec3(0, 0, 0.1f));
}




