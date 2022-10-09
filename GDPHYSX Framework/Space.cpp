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
    this->window = glfwCreateWindow(lengthDim, widthDim, "GDGRAP01- Space Exploration", NULL, NULL);
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
    //Instantiate all obj
    skybox = new Skybox("skybox");
    player = new Player("ship", this->window);
    planet = new Model("planet", NoTexture, this->window);
    debriInitialize();


    //Retrieve their source
    skybox->retrieveSource(lightSrc, mainCam, alterCam);
    player->retrieveSource(lightSrc, mainCam, alterCam);
    planet->retrieveSource(lightSrc, mainCam, alterCam);
    debriRetrieveSource();


    //Player Setup
    player->setInitialPos(glm::vec3(0.5f, 0, 50.0f));
    player->setInitialRotation(glm::vec3(180.0f, 0, 0));
    player->setInitialScale(glm::vec3(30.5f));

    player->recomputeTransform();

    //planet Setup
    planet->setInitialPos(glm::vec3(0.5f, 0, 15000.f));
    planet->setInitialRotation(glm::vec3(0, 0, 0));
    planet->setInitialScale(glm::vec3(250.0f));

    debriSetup();


}

void Space::debriInitialize()
{


    tower = new Model("tower", WithTexture, this->window);
    spaceRock = new Model("spaceRock", WithTexture, this->window);
    statue = new Model("statue", WithTexture, this->window);
    statue2 = new Model("statue2", WithTexture, this->window);
    generators = new Model("generator", WithTexture, this->window);

}

void Space::debriRetrieveSource()
{
    tower->retrieveSource(lightSrc, mainCam, alterCam);
    generators->retrieveSource(lightSrc, mainCam, alterCam);
    spaceRock->retrieveSource(lightSrc, mainCam, alterCam);
    statue->retrieveSource(lightSrc, mainCam, alterCam);
    statue2->retrieveSource(lightSrc, mainCam, alterCam);
}

void Space::debriSetup()
{
    //Sample Setup



    tower->setInitialPos(glm::vec3(-300.f, -500.f, 14000.0f));
    tower->setInitialRotation(glm::vec3(0.f, 240.f, 0.f));
    tower->setInitialScale(glm::vec3(0.01f));

    statue->setInitialPos(glm::vec3(-100.f, 500, 10500.0f));
    statue->setInitialRotation(glm::vec3(0, 220.f, 0.f));
    statue->setInitialScale(glm::vec3(0.5f));


    statue2->setInitialPos(glm::vec3(0.5f, 0, 9000.0f));
    statue2->setInitialRotation(glm::vec3(0, -220.f, 0));
    statue2->setInitialScale(glm::vec3(0.4f));

    generators->setInitialPos(glm::vec3(300.f, 0, 4500.0f));
    generators->setInitialRotation(glm::vec3(0, 0, 0));
    generators->setInitialScale(glm::vec3(10.f));

    spaceRock->setInitialPos(glm::vec3(-500.f, 1200.f, 14500.0f));
    spaceRock->setInitialRotation(glm::vec3(0, 0, 0));
    spaceRock->setInitialScale(glm::vec3(0.5f));


}

void Space::drawDebri()
{

    tower->draw();
    statue2->draw();
    statue->draw();
    spaceRock->draw();
    generators->draw();


}

void Space::deleteDebri()
{
    tower->deAllocate();
    generators->deAllocate();
    spaceRock->deAllocate();
    statue->deAllocate();
    statue2->deAllocate();
}

//Update all active object
void Space::update()
{
    //Skybox
    skybox->update();

    //player
    player->update();

    //Debris
    planet->update();

    //special Case = reference object acting as point light
    planet->updateLight();

}


//Draw Function
void Space::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //Skybox
    skybox->draw();

    //Player
    player->draw();

    //Planet
    planet->draw();

    drawDebri();

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


    //All Debris
    deleteDebri();
    glfwTerminate();
}
