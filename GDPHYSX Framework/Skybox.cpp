#include "Skybox.h"


#include "tiny_obj_loader.h"
#include "stb_image.h"

#include <iostream>
#include <fstream>
#include <sstream>

Skybox::Skybox(std::string name)
{
    this->name = name;
    shader = new Shader(this->name);

    shader->initialize();
   
    loadValues();
   
    this->loadBuffer();
    this->loadTexture();
    
}

void Skybox::loadValues()
{
    float skyboxVertices[] {
        -1.f, -1.f, 1.f, //0
        1.f, -1.f, 1.f,  //1
        1.f, -1.f, -1.f, //2
        -1.f, -1.f, -1.f,//3
        -1.f, 1.f, 1.f,  //4
        1.f, 1.f, 1.f,   //5
        1.f, 1.f, -1.f,  //6
        -1.f, 1.f, -1.f  //7
    };
    

    for (int i = 0; i < sizeof(skyboxVertices) / 4; i++) {
        this->skyboxVertices[i] = skyboxVertices[i];
    }

   

    //Skybox Indices
    unsigned int skyboxIndices[]{
        1,2,6,
        6,5,1,

        0,4,7,
        7,3,0,

        4,5,6,
        6,7,4,

        0,3,2,
        2,1,0,

        0,1,5,
        5,4,0,

        3,7,6,
        6,2,3
    };


    for (int i = 0; i < sizeof(skyboxIndices) / 4; i++) {
        this->skyboxIndices[i] = skyboxIndices[i];
    }

    //Manually Edit the location or retrieve the file as vector of string
    std::string faceSkybox[]{
        "3D/Skybox/right.png",
        "3D/Skybox/left.png",
        "3D/Skybox/up.png",
        "3D/Skybox/down.png",
        "3D/Skybox/front.png",
        "3D/Skybox/back.png"
    };

    for (int i = 0; i < 6; i++) {
        this->faceSkybox[i] = faceSkybox[i];
    }

}

void Skybox::loadTexture()
{
    
    glGenTextures(1, &skyboxTex);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    for (unsigned int i = 0; i < 6; i++) {
        int w, h, skyCChannel;
        stbi_set_flip_vertically_on_load(false);
        unsigned char* data = stbi_load(faceSkybox[i].c_str(), &w, &h, &skyCChannel, 0);

        if (data) {
            glTexImage2D(
                GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, //R, L, T, B, F, B
                0,
                GL_RGBA,
                w,
                h,
                0,
                GL_RGBA,
                GL_UNSIGNED_BYTE,
                data
            );

            stbi_image_free(data);
        }
    }
    stbi_set_flip_vertically_on_load(true);

}

void Skybox::loadBuffer()
{
    
   
    glGenVertexArrays(1, &this->skyVAO);
    glGenBuffers(1, &this->skyVBO);
    glGenBuffers(1, &this->skyEBO);

    glBindVertexArray(this->skyVAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->skyVBO);
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(skyboxVertices),
        &skyboxVertices,
        GL_STATIC_DRAW);

    glVertexAttribPointer(0,
        3,
        GL_FLOAT,
        GL_FALSE,
        3 * sizeof(float),
        (void*)0);

    

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->skyEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,
        sizeof(GL_INT) * 36,
        &skyboxIndices,
        GL_STATIC_DRAW);

    
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


}

void Skybox::update()
{
    this->perspCam->updateCamera();
    this->orthoCam->updateCamera();
}

void Skybox::draw()
{
    glDepthMask(GL_FALSE);
    glDepthFunc(GL_LEQUAL);
    glm::mat4 projection;
    projection = glm::perspective(glm::radians(60.0f),
            800.0f / 800.0f,
            0.01f,
            100.0f);

    glUseProgram(shader->getShaderProg());
    glm::mat4 sky_view = glm::mat4(1.0f);
    sky_view = glm::mat4(glm::mat3(retrieveCamMat()));

    shader->viewUpdate(sky_view);
    shader->projectionUpdate(perspCam->getProjection());


    //glUseProgram(skyboxShader);
    glBindVertexArray(skyVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, skyboxTex);

    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
    glDepthMask(GL_TRUE);
    glDepthFunc(GL_LESS);



}

void Skybox::deAllocate()
{
    glDeleteBuffers(1, &skyVAO);
    glDeleteBuffers(1, &skyVBO);
    glDeleteBuffers(1, &skyEBO);
}





