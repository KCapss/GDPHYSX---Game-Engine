#include "Shader.h"

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include "SwitchManager.h"


#include <vector>


Shader::Shader(std::string name)
{
    this->name = name;
    
}

void Shader::initialize()
{
   


    std::fstream vertStream("Shaders/" + this->name + ".vert");
    std::stringstream vertStrStream;

    vertStrStream << vertStream.rdbuf();
    std::string vertStr = vertStrStream.str();

    const char* vertSrc = vertStr.c_str();


    std::fstream fragStream("Shaders/" + this->name + ".frag");
    std::stringstream fragStrStream;

    fragStrStream << fragStream.rdbuf();
    std::string fragStr = fragStrStream.str();

    const char* fragSrc = fragStr.c_str();

   
    GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertShader, 1, &vertSrc, NULL);
    glCompileShader(vertShader);

    GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragShader, 1, &fragSrc, NULL);
    glCompileShader(fragShader);

    this->shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertShader);
    glAttachShader(shaderProgram, fragShader);

    glLinkProgram(shaderProgram);
}

GLuint Shader::getShaderProg()
{
    return this->shaderProgram;
}

void Shader::transformUpdate(glm::mat4 transform)
{
    unsigned int transformLoc = glGetUniformLocation(this->shaderProgram, "transform");
    glUniformMatrix4fv(transformLoc,
        1,
        GL_FALSE,
        glm::value_ptr(transform));

}

void Shader::projectionUpdate(glm::mat4 projection)
{
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");
    glUniformMatrix4fv(projectionLoc,
        1,
        GL_FALSE,
        glm::value_ptr(projection));

}

void Shader::viewUpdate(glm::mat4 viewMatrix)
{
    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    glUniformMatrix4fv(viewLoc,
        1,
        GL_FALSE,
        glm::value_ptr(viewMatrix));
}

void Shader::textureUpdate(GLuint texture, string varName, int layer)
{
    GLuint tex0Loc = glGetUniformLocation(shaderProgram, varName.c_str());  
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(tex0Loc, layer);
}

void Shader::LightUpdate(Light *refLight)
{
    float activeLight = SwitchManager::getInstance()->isShipLightActive();
    //cout << activeLight << endl;
    GLuint lightTypeAddress = glGetUniformLocation(shaderProgram, "lightType");
    glUniform1f(lightTypeAddress, activeLight);

    GLuint lightLumensAddress = glGetUniformLocation(shaderProgram, "lumens");
    glUniform1f(lightLumensAddress, refLight->getLumens());

    GLuint lightPosAddress = glGetUniformLocation(shaderProgram, "lightPos");
    glUniform3fv(lightPosAddress, 1, glm::value_ptr(refLight->getLightPos()));

    GLuint lightColorAddress = glGetUniformLocation(shaderProgram, "lightColor");
    glUniform3fv(lightColorAddress, 1, glm::value_ptr(refLight->getLightColor()));

    GLuint ambientColorAddress = glGetUniformLocation(shaderProgram, "ambientColor");
    glUniform3fv(ambientColorAddress, 1, glm::value_ptr(refLight->getAmbientColor()));

    GLuint ambientStrAddress = glGetUniformLocation(shaderProgram, "ambientStr");
    glUniform1f(ambientStrAddress, refLight->getAmbientStr());

    GLuint specStrAddress = glGetUniformLocation(shaderProgram, "specStr");
    glUniform1f(specStrAddress, refLight->getSpecStr());

    GLuint specPhongAddress = glGetUniformLocation(shaderProgram, "specPhong");
    glUniform1f(specPhongAddress, refLight->getSpecPhong());

    
}

void Shader::cameraUpdatePos(glm::vec3 cameraPos)
{
    GLuint cameraPosAddress = glGetUniformLocation(shaderProgram, "cameraPos");
    glUniform3fv(cameraPosAddress, 1, glm::value_ptr(cameraPos));
}
