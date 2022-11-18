#include "Space.h"
#include "ObjectTextureManager.h"


//Constructor with defined dimension
Space::Space(int length, int width)
{
    ObjectTextureManager::getInstance()->loadAll();

    lightSrc = new Light(glm::vec3(-10.0f, 0, 0));
    mainCam = new PerspectiveCamera(length, width);
    alterCam = new OrthographicCamera();

    this->lengthDim = length;
    this->widthDim = width;




}

//Create the window and set the defined dimension along with its view range
bool Space::initializeWindow()
{
    //Init Lib
    if (!glfwInit())
        return true;

    //Init Window
    this->window = glfwCreateWindow(lengthDim, widthDim, "GDPHYSX Game Engine", NULL, NULL);
    if (!this->window)
    {
        glfwTerminate();
        return true;
    }

    glfwMakeContextCurrent(this->window);
    gladLoadGL();

    //Initialize ViewPort
    glViewport(0, 0, lengthDim, widthDim);

    return false;
}

/*Initialize all obj
retrieve their source AND
customize their position*/
void Space::initializeObj()
{
    //Create the Managers First
    pfGenManager = new ParticleForceRegistry();

    //Instantiate all obj
    skybox = new Skybox("skybox");
    player = new Player("ship", this->window);
    planet = new ParticleObject("ball", NoTexture, this->window);


    //projectile = new BallisticObject("ball", NoTexture, this->window);
    //fireworksObject = new FireworkObject("ball", NoTexture, this->window);
    projectileContainer = new BallisticContainer();
    objectContainer = new ObjectContainer();
    springContainer = new SpringParticleContainer(pfGenManager);
    


    //Remove when not needed
    refParticle = new ParticleObject("ball", NoTexture, this->window);
    testParticle = new ParticleObject("ball", NoTexture, this->window);
    /*ASpringObject = new AnchorSpringObject("ball", NoTexture, this->window);
    springObject = new SpringObject("ball", NoTexture, this->window);
    bungeeObject = new BungeeObject("ball", NoTexture, this->window);*/

    //Reference Particle
    refParticle->retrieveSource(lightSrc, mainCam, alterCam);
    refParticle->setPosition(vec3(0));
    refParticle->setInitialScale(vec3(3.0f));
//    refParticle->setInitialScale(vec3(1.0f));

    // Test particle for collision
    testParticle->retrieveSource(lightSrc, mainCam, alterCam);
    testParticle->setPosition(vec3(0, -100.0f, 0.f));
    testParticle->setInitialScale(vec3(10.0f));
//    testParticle->setInitialScale(vec3(1.0f));

    testParticle->setMass(0.0f);
    objectContainer->addParticle((Particle*)testParticle);
 
    projectileContainer->setLimit(5);
    projectileInit(1);
    springInit(3);

    //Retrieve their source
    skybox->retrieveSource(lightSrc, mainCam, alterCam);
    player->retrieveSource(lightSrc, mainCam, alterCam);
    planet->retrieveSource(lightSrc, mainCam, alterCam);
    //projectile->retrieveSource(lightSrc, mainCam, alterCam);
    //fireworksObject->retrieveSource(lightSrc, mainCam, alterCam);
    //debriRetrieveSource();


    //Player Setup
    player->setInitialPos(glm::vec3(0.5f, 0, 50.0f));
    player->setInitialRotation(glm::vec3(180.0f, 0, 0));
    player->setInitialScale(glm::vec3(30.5f));

    player->recomputeTransform();

    //planet Setup
    //planet->setInitialPos(glm::vec3(0.5f, 0, 15000.f));
    planet->setInitialRotation(glm::vec3(0, 0, 0));
    planet->setInitialScale(glm::vec3(20.0f));

    //debriSetup();


    //Physic Game Object Holder
   /* projectile->setInitialScale(glm::vec3(100.0f));
    projectile->onActivate(ShotTypes::PISTOL); 
    projectileContainer->loadMagazine(projectile)*/; //load Bullet

    /*fireworksObject->setInitialScale(glm::vec3(5.0f));
    fireworksObject->create(1, NULL);
    projectileContainer->loadFireworks(fireworksObject);*/
    //projectileContainer->loadMagazine(projectile);

    

    ////Spring Force
    //springObject->retrieveSource(lightSrc, mainCam, alterCam);
    //springObject->init((Particle*)refParticle, 1.0f, 10.0f);
    //springObject->setStartPos(vec3(0, 0, 5.0f));
    //springObject->setInitialScale(vec3(5.0f));

    //bungeeObject->retrieveSource(lightSrc, mainCam, alterCam);
    //bungeeObject->init((Particle*)refParticle, 1.2f, 10.0f);
    //bungeeObject->setStartPos(vec3(0, 10.0f, 0));
    //bungeeObject->setInitialScale(vec3(20.0f));



    //ASpringObject->retrieveSource(lightSrc, mainCam, alterCam);
    //ASpringObject->setStartPos(glm::vec3(0.00f, 0.01f, 0.0f));
    //ASpringObject->setInitialRotation(glm::vec3(0, 0, 0));
    //ASpringObject->setInitialScale(glm::vec3(10.0f));

}






void Space::projectileInit(int size)
{
    for (int i = 0; i < size; i++) {
        BallisticObject* projectile = new BallisticObject("ball", NoTexture, this->window);
        projectile->retrieveSource(this->lightSrc, this->mainCam, this->alterCam);

        //Debug = Change sizable
        projectile->setInitialScale(glm::vec3(10.0f));
//         projectile->setInitialScale(glm::vec3(1.0f));

        //Onactive () - Optional::
        projectileContainer->loadMagazine(projectile);
        objectContainer->addParticle(projectile); // for testing collision
    }

    for (int i = 0; i < size; i++) {

        FireworkObject* fireworks = new FireworkObject("ball", NoTexture, this->window);
        fireworks->retrieveSource(this->lightSrc, this->mainCam, this->alterCam);

        fireworks->setInitialScale(glm::vec3(5.0f));
        fireworks->create(1, NULL);
        projectileContainer->loadFireworks(fireworks);
    }
}

void Space::springInit(int size)
{
    for (int i = 0; i < size; i++) {

        SpringObject *copySpring = new SpringObject("ball", NoTexture, this->window);
        copySpring->retrieveSource(lightSrc, mainCam, alterCam);
        copySpring->init((Particle*)refParticle, 1.0f, 10.0f);
        copySpring->setStartPos(vec3(0, 0, 5.0f));
        copySpring->setInitialScale(vec3(10.0f));
       

        springContainer->loadSpring(copySpring);

    }

    for (int i = 0; i < size; i++) {
        AnchorSpringObject* copyASpring = new AnchorSpringObject("ball", NoTexture, this->window);
        copyASpring->retrieveSource(lightSrc, mainCam, alterCam);
        copyASpring->setStartPos(glm::vec3(0.00f, 0.01f, 0.0f));
        copyASpring->setStartPos(vec3(0, 0, 5.0f));
        copyASpring->setInitialScale(vec3(10.0f));
       

        springContainer->loadAnchor(copyASpring);
    }
    
    for (int i = 0; i < size; i++) {
        BungeeObject* copyBungee = new BungeeObject("ball", NoTexture, this->window);
        copyBungee->retrieveSource(lightSrc, mainCam, alterCam);
        copyBungee->init((Particle*)refParticle, 1.0f, 10.0f);
        copyBungee->setStartPos(vec3(0, 0, 5.0f));
        copyBungee->setInitialScale(vec3(10.0f));
       

        springContainer->loadBungee(copyBungee);
        
    }

}

void Space::input()
{
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
    {
        cout << "1 Pressed!" << endl;
        shotType = ShotTypes::PISTOL;
    }
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
    {
       // cout << "2 Pressed!" << endl;
        shotType = ShotTypes::ARTILLERY;
    }
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
    {
        //cout << "3 Pressed!" << endl;
        shotType = ShotTypes::FIREBALL;
    }
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
    {
       // cout << "4 Pressed!" << endl;
        shotType = ShotTypes::LASER;
    }
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
    {
        //cout << "5 Pressed!" << endl;
        shotType = ShotTypes::FIREWORK;
    }
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
    {
        //cout << "6 Pressed!" << endl;
        springTypes = 6;
    }
    if (glfwGetKey(window, GLFW_KEY_7) == GLFW_PRESS)
    {
        //cout << "7 Pressed!" << endl;
        springTypes = 7;
    }
    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
    {
        //cout << "8 Pressed!" << endl;
        springTypes = 8;
    }

    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
    {
        //cout << "Left Button Pressed!" << endl;
        projectileContainer->fireMagazine(shotType);  // == disable for this assignment
        //springContainer->fire(springTypes);
       
    }
}

//Update all active object
void Space::update(float deltaTime)
{
    //Skybox
    skybox->update();

    //player
    player->update();

    //Debris
    planet->update(deltaTime);

    //Manager
    pfGenManager->updateForces(deltaTime);
    
    //Physics Object
    objectContainer->updateParticleContainer(deltaTime);
    projectileContainer->updateBallisticContainer(deltaTime);
    springContainer->updateSpringContainer(deltaTime);

    refParticle->update(deltaTime);
    testParticle->update(deltaTime);
    //ASpringObject->update(deltaTime);
    //springObject->update(deltaTime);
    //bungeeObject->update(deltaTime);

    //special Case = reference object acting as point light
    planet->updateLight();

    // Keyboard press and Mouse button press
    input();

}


//Draw Function
void Space::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Skybox
    skybox->draw();

    //Player
    //player->draw();

    //Planet
    //planet->draw();

    projectileContainer->draw();
    springContainer->draw();
    
    refParticle->draw();
    testParticle->draw();
    /*springObject->draw();
    ASpringObject->draw();
    bungeeObject->draw();*/

    

    /* Swap front and back buffers */
    glfwSwapBuffers(this->window);

    /* Poll for and process events */
    glfwPollEvents();
}

//Delete all buffer
void Space::deleteBuffer()
{
    //Skybox
    skybox->deAllocate();

    //Player
    player->deAllocate();
    planet->deAllocate();


    //Physics Object
    projectileContainer->deleteBuffer();

    glfwTerminate();
}
