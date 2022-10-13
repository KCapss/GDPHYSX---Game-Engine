#include "BallisticObject.h"

BallisticObject::BallisticObject(std::string name, ObjectType objType, GLFWwindow* currWindow) :
	Model(name, objType, currWindow), Ballistic()
{
    this->setActive(false); //Disable Object

    //Debug Purposes
    this->defaultPos = vec3(0);
}

void BallisticObject::update(float timeStep)
{

	if (this->isSetActive()) {
		this->updatePosition(timeStep);
	}
}

void BallisticObject::draw()
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

void BallisticObject::onActivate(ShotTypes shotType)
{
    this->setShotType(shotType);
    this->setActive(true);
    this->setPosition(this->defaultPos);

    cout << "Shot Activated" << endl;
}

void BallisticObject::onReset()
{
    this->setActive(false);
    this->setShotType(ShotTypes::UNUSED);
   
;}
