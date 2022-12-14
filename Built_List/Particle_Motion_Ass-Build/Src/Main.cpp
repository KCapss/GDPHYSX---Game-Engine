#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include <cstdlib>

#include "Particle.h"

using namespace std;

void applyForce(glm::vec3& position, int dir, float deltaTime);
void applyGravity(glm::vec3& position);

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

// Physics variables for input listener
bool isForceApplied = false;
bool isGravity = false;
bool didReset = false;
int dir = 0;
int useZ = 0;

int main(void)
{
    GLFWwindow* window;

    std::string path = "3D/ball.obj";
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> material;
    std::string warning, error;

    tinyobj::attrib_t attributes;

    bool success = tinyobj::LoadObj(&attributes,
        &shapes,
        &material,
        &warning,
        &error,
        path.c_str());

    std::vector<GLuint> mesh_indices;
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++)
    {
        mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);

    }

    std::fstream vertStream("Shaders/sample.vert");
    std::stringstream vertStrStream;

    vertStrStream << vertStream.rdbuf();
    std::string vertStr = vertStrStream.str();

    const char* vertSrc = vertStr.c_str();
    //std::cout << vertSrc << std::endl;

    std::fstream fragStream("Shaders/sample.frag");
    std::stringstream fragStrStream;

    fragStrStream << fragStream.rdbuf();
    std::string fragStr = fragStrStream.str();

    const char* fragSrc = fragStr.c_str();
    /*Defaul Parameters*/

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    float height = 800;
    float width = 800;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(width, height, "Kevin Capalar", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    gladLoadGL();

    glViewport(0, 0, width, height);

    //Load Shaders
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertSrc, NULL);
    glCompileShader(vertShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSrc, NULL);
    glCompileShader(fragShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);

    glLinkProgram(shaderProgram);

    //Buffer Setup
    GLuint VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(attributes.vertices) * attributes.vertices.size(),
        attributes.vertices.data(),
        GL_DYNAMIC_DRAW);

    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0
    );


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(mesh_indices) * mesh_indices.size(),
        mesh_indices.data(),
        GL_DYNAMIC_DRAW
    );


    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    //Animation
    float lastTime = glfwGetTime();


    //Initialize
    glm::vec3 bunnyMove(0, 0, 0),
        bunnyScaleAxis(3, 3, 3),
        bunnyRotateAxis(0, 0, 0);

    float bunnyRadiansx = 1.0f;
    float bunnyRadiansy = 1.0f;

    //Camera Setup
    glm::vec3 cameraPos = glm::vec3(0, 0, -100.0f);
    glm::mat4 cameraPositionMatrix = glm::translate(glm::mat4(1.0f),
        cameraPos * -1.0f);

    glm::vec3 WorldUp = glm::vec3(0, 1.0f, 0);
    glm::vec3 Center = glm::vec3(0, 3.0f, 0);
    glm::vec3 F = glm::normalize(glm::vec3(Center - cameraPos));
    glm::vec3 R = glm::normalize(glm::cross(F, WorldUp));
    glm::vec3 U = glm::normalize(glm::cross(R, F));

    glm::mat4 cameraOrientation = glm::mat4(
        glm::vec4(R, 0),
        glm::vec4(U, 0),
        glm::vec4((F * -1.0f), 0),
        glm::vec4(glm::vec3(0, 0, 0), 1.0f)
    );

    glm::mat4 viewMatrix = cameraOrientation * cameraPositionMatrix;

    // Seed random number generator
    srand((unsigned)time(NULL));

    // Key callback
    glfwSetKeyCallback(window, key_callback);

    // Set initial position
    glm::mat4 transform = glm::mat4(1.0f);

    // Instantiate Particle
    Particle* particle = new Particle(vec3{0.f, 0.f, -65.f}, 10.f);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        GLfloat currTime = glfwGetTime();
        float deltaTime = currTime - lastTime;

        particle->updateVelocity(vec3{0.f}, deltaTime);

        //Apply Linear Transformation
        glm::mat4 identity = glm::mat4(1.0f);

        glm::mat4 transform = glm::translate(identity, vec3(particle->position.x, particle->position.y, particle->position.z));

        if (didReset)
        {
            isForceApplied = false;
            particle->position = {0, 0, -65.f};
            particle->velocity = vec3{ 0.f };
            didReset = false;
        }

        // Toggle gravity
        if (isGravity)
        {
            particle->toogleGravity(true);
            //applyGravity(bunnyMove);
        }
        else if (!isGravity)
        {
            
            if (particle->checkGravityStatus()) {
                cout << "Halt Velocity" << endl;
                particle->toogleGravity(false);
                particle->velocity = vec3{ 0.f }; // when gravity is disabled so is velocity
            }
            particle->toogleGravity(false);
                
;        }

        // Apply Force
        if (isForceApplied) {
            applyForce(particle->velocity, dir, deltaTime);
            isForceApplied = false;
        }

        glm::mat4 projection = glm::perspective(glm::radians(60.0f),
            height / width,
            0.0f,
            100.0f);


        //Apply Shader Program
        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        glUniformMatrix4fv(transformLoc,
            1,
            GL_FALSE,
            glm::value_ptr(transform));

        unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
        glUniformMatrix4fv(projectionLoc,
            1,
            GL_FALSE,
            glm::value_ptr(projection));

        unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
        glUniformMatrix4fv(viewLoc,
            1,
            GL_FALSE,
            glm::value_ptr(viewMatrix));

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);

        //Draw the vertices of the object
        glDrawElements(GL_TRIANGLES,
            mesh_indices.size(),
            GL_UNSIGNED_INT,
            0);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);


        /* Poll for and process events */
        glfwPollEvents();
        lastTime = currTime;
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;


}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_W && action == GLFW_PRESS)
    {
        // Select random cardinal direction
        dir = rand() % 7;
        std::cout << "Direction is " << dir << std::endl;

        // check if +z, -z or no z will be used
        useZ = rand() % 30;
        std::cout << "Z use is " << useZ << std::endl;

        isForceApplied = true;
    }
    if (key == GLFW_KEY_E && action == GLFW_PRESS)
    {
        isGravity = !isGravity;
        
    }
    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        didReset = !didReset;
    }
}

void applyForce(glm::vec3& position, int dir, float deltaTime)
{

    float testSpeed = 1000.f * deltaTime;

    // Cardinal Direction
    // Move North
    if (dir == 0) {
        position.y += testSpeed;
    }
    // Move East
    else if (dir == 1) {
        position.x += testSpeed;
    }
    // Move South
    else if (dir == 2) {
        position.y -= testSpeed;
    }
    // Move West
    else if (dir == 3) {
        position.x -= testSpeed;
    }
    // Move NorthEast
    else if (dir == 4) {
        position.y += testSpeed;
        position.x += testSpeed;
    }
    // Move SouthEast
    else if (dir == 5) {
        position.y -= testSpeed;
        position.x += testSpeed;
    }
    // Move SouthWest
    else if (dir == 6) {
        position.y -= testSpeed;
        position.x -= testSpeed;
    }
    // Move NorthWest
    else if (dir == 7) {
        position.y += testSpeed;
        position.x -= testSpeed;
    }

    // Z Axis Use
    if (useZ >= 0 && useZ <= 9) // positive z
    {
        position.z += testSpeed;
    }
    else  if (useZ >= 10 && useZ <= 19) // negative z
    {
        position.z -= testSpeed;
    }
    // if 20 to 30, dont increment/decrement z
}

void applyGravity(glm::vec3& position)
{
    float gravitySpeed = 0.1f;

    position.y -= gravitySpeed;
}

/*
void updateInput(GLFWwindow* window, glm::vec3& position, glm::vec3& scale, glm::vec3& rotation, float* thetaX, float* thetaY, float time, bool* isMoving, int* dir, bool* isGravity, bool* didReset)
{
    bool wPressed = false;

    // Randomly select 1 of 4 directions, 0 - up, 1 - right, 2 - down, 3 - left
    bool wCurrentlyPressed = glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS;

    if(!wPressed && wCurrentlyPressed)
    {
        *dir = rand() % 4;
        std::cout << "Number is " << *dir << std::endl;
        *isMoving = !*isMoving;
    }
    wPressed = wCurrentlyPressed;

    // Apply Gravity
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        if (*isGravity == false)
            *isGravity = true;
        else if (*isGravity == true)
        {
            bunnyMove = { 0, 0, 0 };
            *isGravity = false;
        }
    }

    // Reset Position
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        *didReset = true;
    }


    //Translation (WASD)
    /*
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        //position.x -= 10.0f;
        *isMoving = true;
    }

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        position.x += 10.0f * time;
        *isMoving = !*isMoving;

    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        position.y += 10.0f * time;
        *isMoving = !*isMoving;

    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        position.y -= 10.0f * time;
        *isMoving = !*isMoving;
    }

    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) {
        position.z -= 10.0f * time;
        *isMoving = !*isMoving;
    }
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {
        position.z += 10.0f * time;
        *isMoving = !*isMoving;
    }
    */

    /*
    //Scaling(Q/E)
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        scale.x -= 0.5f * time;
        scale.y -= 0.5f * time;
        scale.z -= 0.5f * time;

    }

    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        scale.x += 0.5f * time;
        scale.y += 0.5f * time;
        scale.z += 0.5f * time;

    }

    //Rotation(Arrow Keys)
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        *thetaY += 30.0f * time;

    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        *thetaY -= 30.0f * time;

    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        *thetaX += 30.0f * time;

    }

    if (glfwGetKey(window, 262) == GLFW_PRESS) {
        *thetaX -= 30.0f * time;

    }

}
*/