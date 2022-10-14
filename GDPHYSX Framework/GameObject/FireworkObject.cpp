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
    rule1->init(2);
    rule1->setParameters(
        1, // type
        150, 450, // age range
        glm::vec3(-5, 200, -5), // min velocity
        glm::vec3(5, 240, 5), // max velocity
        0.1f // damping
    );
    rule1->payloads[0]->set(3, 5);
    rule1->payloads[1]->set(5, 5);
    rulesList.push_back(rule1);

    FireworkRules* rule2 = new FireworkRules();
    rule2->init(1);
    rule2->setParameters(
        2, // type
        150, 300, // age range
        glm::vec3(-5, 20, -5), // min velocity
        glm::vec3(5, 40, 5), // max velocity
        0.8f // damping
    );
    rule2->payloads[0]->set(4, 2);
    rulesList.push_back(rule2);

    FireworkRules* rule3 = new FireworkRules();
    rule3->init(0);
    rule3->setParameters(
        3, // type
        150, 450, // age range
        glm::vec3(-50, -50, -50), // min velocity
        glm::vec3(50, 50, 50), // max velocity
        0.1f // damping
    );
    rulesList.push_back(rule3);

    FireworkRules* rule4 = new FireworkRules();
    rule4->init(0);
    rule4->setParameters(
        4, // type
        75, 150, // age range
        glm::vec3(-200, 50, -50), // min velocity
        glm::vec3(200, 50, 50), // max velocity
        0.2f // damping
    );
    rulesList.push_back(rule4);

    FireworkRules* rule5 = new FireworkRules();
    rule5->init(1);
    rule5->setParameters(
        5, // type
        150, 300, // age range
        glm::vec3(-200, 20, -50), // min velocity
        glm::vec3(200, 180, 50), // max velocity
        0.01f // damping
    );
    rule5->payloads[0]->set(3, 5);
    rulesList.push_back(rule5);

    FireworkRules* rule6 = new FireworkRules();
    rule6->init(0);
    rule6->setParameters(
        6, // type
        450, 750, // age range
        glm::vec3(-50, 50, -50), // min velocity
        glm::vec3(50, 100, 50), // max velocity
        0.95f // damping
    );
    rulesList.push_back(rule6);

    FireworkRules* rule7 = new FireworkRules();
    rule7->init(1);
    rule7->setParameters(
        7, // type
        600, 750, // age range
        glm::vec3(-50, 500, -50), // min velocity
        glm::vec3(50, 600, 50), // max velocity
        0.01f // damping
    );
    rule7->payloads[0]->set(8, 10);
    rulesList.push_back(rule7);

    FireworkRules* rule8 = new FireworkRules();
    rule8->init(0);
    rule8->setParameters(
        8, // type
        75, 150, // age range
        glm::vec3(-10, -10, -10), // min velocity
        glm::vec3(10, 10, 10), // max velocity
        0.01f // damping
    );
    rulesList.push_back(rule8);

    FireworkRules* rule9 = new FireworkRules();
    rule9->init(0);
    rule9->setParameters(
        8, // type
        450, 750, // age range
        glm::vec3(-150, 100, -50), // min velocity
        glm::vec3(150, 150, 50), // max velocity
        0.95f // damping
    );
    rulesList.push_back(rule9);
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
