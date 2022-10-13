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
	FireworkRules* rule1 = new FireworkRules();
    rule1->init(1);
    rule1->setParameters(
        1, // type
        200, 300, // age range
        glm::vec3(-5, 35, -5), // min velocity
        glm::vec3(5, 50, 5), // max velocity
        0.9f // damping
    );
    rule1->payloads[0]->set(2, 50);

    rulesList.push_back(rule1);

    FireworkRules* rule2 = new FireworkRules();
    rule2->init(0);
    rule2->setParameters(
        1, // type
        200, 300, // age range
        glm::vec3(-5, 35, -5), // min velocity
        glm::vec3(5, 50, 5), // max velocity
        0.9f // damping
    );

    rulesList.push_back(rule2);

    //TODO List: Create a succedding rule for child instantiation "calling rule->init()"

}

//This called space.cpp
void FireworkObject::create(unsigned type, Firework* parent)
{
    //Create a firework based on the assigned type at declaration
    if (parent == NULL) {
        
        this->setType(type);
       
    }

    for (int i = 0; i < rulesList[type - 1]->payloads.size(); i++) {

        for (int j = 0; j < rulesList[type - 1]->payloads[i]->paramCount; j++) {

            FireworkObject* newFireworks = new FireworkObject(name, objType, window);
            newFireworks->retrieveSource(light, perspCam, orthoCam);

            newFireworks->setType(rulesList[type - 1]->payloads[i]->paramType);
            newFireworks->create(rulesList[type - 1]->payloads[i]->paramType, this);

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

    else {
        this->setPosition(vec3(0));
        this->setVelocity(vec3(0));
        this->setAcceleration(vec3(0));
    }
    this->applyRules(this);
    this->toogleGravity(true);
    this->setActive(true);
}

void FireworkObject::applyRules(FireworkObject* firework)
{
    int maxAge = rulesList[this->getType() - 1]->maxAge;
    int minAge = rulesList[this->getType() - 1]->minAge;
    glm::vec3 minVel = rulesList[this->getType() - 1]->minVelocity;
    glm::vec3 maxVel = rulesList[this->getType() - 1]->maxVelocity;
    float damping = rulesList[this->getType() - 1]->damp;

    glm::vec3 final = rulesList[this->getType() - 1]->randomVector(minVel, maxVel);
    
    firework->setAge((rand() % (maxAge - minAge)) + minAge);
    firework->addVelocity(final);
    //randf for velocity
    // 
    // use: firework->addVeloctiy(Output ng RANDF)
    // 
    //--- insert here
    firework->setMass(1.0f);
    firework->setDamping(damping);

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

    for (int i = 0; i < fireworkPayload.size(); i++) {
        fireworkPayload[i]->draw();
    }

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
