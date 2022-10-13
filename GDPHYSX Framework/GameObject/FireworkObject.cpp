#include "FireworkObject.h"


FireworkObject::FireworkObject(std::string name, ObjectType objType, GLFWwindow* currWindow):
	FireworkRules(), Firework(), Model(name, objType, currWindow)
{
	this->setActive(false);
    this->initFireworkRules();

}

FireworkObject::~FireworkObject()
{
}

void FireworkObject::initFireworkRules()
{
	//Create a FireWork Rules Class
	FireworkRules* rule = new FireworkRules();
    rule->init(0);
    rule->setParameters(
        1, // type
        1, 3, // age range
        glm::vec3(-5, 25, -5), // min velocity
        glm::vec3(5, 28, 5), // max velocity
        0.1 // damping
    );

   /* rule->payloads[0].set(1, 5);
    rule->payloads[1].set(1, 5);*/


    //TODO List: Create a succedding rule for child instantiation "calling rule->init()"

}

//This called space.cpp
void FireworkObject::create(unsigned type, Firework* parent)
{
    //Create a firework based on the assigned type at declaration
    if (parent == NULL) {
        
        this->setType(type);
       
    }

    for (int i = 0; i < rulesList[type - 1].payloads.size(); i++) {

        for (int j = 0; j < rulesList[type - 1].payloads[i]->paramCount; j++) {

            FireworkObject* newFireworks = new FireworkObject(name, objType, window);
            newFireworks->retrieveSource(light, perspCam, orthoCam);

            newFireworks->setType(rulesList[type - 1].payloads[i]->paramType);
            newFireworks->create(rulesList[type - 1].payloads[i]->paramType, this);

            this->fireworkPayload.push_back(newFireworks);
        }

    }
    


}

void FireworkObject::activate(FireworkObject* parent)
{
    if(parent != NULL){
        this->setPosition(parent->getPosition());
        this->setVelocity(parent->getVelocity());
        this->setAcceleration(parent->getAcceleraation());

    }

    this->rulesList[this->getType() - 1].applyRules(this);
    this->toogleGravity(true);
    this->setActive(true);
}

void FireworkObject::updateFireworkObject(float deltaTime)
{
    for (int i = 0; i < fireworkPayload.size(); i++) {
        fireworkPayload[i]->updateFireworkObject(deltaTime);
    }

    if (this->isSetActive()) {

        this->updateFireworks(deltaTime);
        this->tick += deltaTime;
        //Activate its child


        if (this->getAge() <= tick) {
            for (int i = 0; i < fireworkPayload.size(); i++) {
                fireworkPayload[i]->activate(this);
            }
            this->setActive(false);
            this->toogleGravity(false);
            this->tick = 0;
        }

    }



}

void FireworkObject::draw()
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
