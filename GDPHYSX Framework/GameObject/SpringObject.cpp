#include "SpringObject.h"

SpringObject::SpringObject(std::string name, ObjectType objType, GLFWwindow* currWindow) : Model(name, objType, currWindow)
{
    this->particle = new Particle();

    //Debug Only Remove when not needed
    particle->setVelocity(vec3(0, 0, 0.1f));
    particle->setDamping(0.95f);
    particle->toogleGravity(true);
    ///

    particle->setMass(10.0f);
}

void SpringObject::init(Particle* other, float springConst, float restLength)
{
    this->springPhysics = new ParticleSpring(other, springConst, restLength);
}

void SpringObject::setStartPos(glm::vec3 Pos)
{
    this->particle->setPosition(Pos);
}

void SpringObject::update(float timeStep)
{
    if (this->isSetActive()) {

        if (this->tick >= maxTime)
            this->setActive(false);

        tick += timeStep;
        this->particle->updatePosition(timeStep);
       
    }
   
   
}

void SpringObject::draw()
{
    if (this->isSetActive()) {
        glBindVertexArray(0);

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
}

void SpringObject::reset()
{
    this->tick = 0;
    this->setActive(true);
    particle->setVelocity(vec3(0, 0, 5.0f));
    particle->setPosition(vec3(0, 0, 0.1f));
}
