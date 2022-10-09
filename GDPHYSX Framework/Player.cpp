#include "Player.h"

#include "SwitchManager.h"
#include "ObjectTextureManager.h"

#include "tiny_obj_loader.h"
#include "stb_image.h"


//Constructor
Player::Player(std::string name, GLFWwindow *window): Model(name, ObjectType::TextureAndNormals, window)
{
	//Majority of the process will be on the base on the base class for now
    loadObj();
    loadTexture();
    loadBuffer();

    currTime = glfwGetTime();
    lastTime = currTime;
    SwitchManager::getInstance()->initialize();
}

/*This function recompute the transform Matrix*/
void Player::recomputeTransform()
{
    this->shipTransform = glm::translate(this->shipTransform, objPosition);
    shipTransform = glm::scale(shipTransform, objScale);

    shipTransform = glm::rotate(shipTransform, glm::radians(objRotation.x), glm::vec3(0, 1, 0));
    shipTransform = glm::rotate(shipTransform, glm::radians(objRotation.y), glm::vec3(1, 0, 0));
    shipTransform = glm::rotate(shipTransform, glm::radians(objRotation.z), glm::vec3(0, 0, 1));
}


/*This function camera state and switches accordingly*/
void Player::cameraSwitch()
{
    float ticks = 2.5f;
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS && ticks < glfwGetTime()) {
		this->currCam = SwitchManager::getInstance()->changeCam(currCam);

		//Special Effect for cursor
		if (SwitchManager::getInstance()->isPerspectiveActive(currCam)) {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
			
		}

		else {
			glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            orthoCam->camPanningReset();
            //orthoCam->updatePosition(glm::vec3(this->shipTransform * glm::vec4(0,0,0,1)));
            orthoCam->updatePosition(glm::vec3(0, 0, 1));
		}

		SwitchManager::getInstance()->updateCurrCam(currCam);
        glfwSetTime(0);
	}

}

/*This function Light state and switches accordingly*/
void Player::lightSwitch()
{
    float tick = 0.7f;
    float timer = glfwGetTime();


	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS && tick < timer) {
		SwitchManager::getInstance()->changeLightSource();
        glfwSetTime(0.0f);
	}
}


//Object Initialize
void Player::loadObj()
{
    std::string path = ObjectTextureManager::getInstance()->getObjPath(this->name);
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

    //Normal Map
    std::vector<glm::vec3> tangents;
    std::vector<glm::vec3> bitangents;

    for (int i = 0; i < shapes[0].mesh.indices.size(); i += 3) {
        tinyobj::index_t vData1 = shapes[0].mesh.indices[i];
        tinyobj::index_t vData2 = shapes[0].mesh.indices[i + 1];
        tinyobj::index_t vData3 = shapes[0].mesh.indices[i + 2];

        glm::vec3 v1 = glm::vec3(
            attributes.vertices[vData1.vertex_index * 3],
            attributes.vertices[(vData1.vertex_index * 3) + 1],
            attributes.vertices[(vData1.vertex_index * 3) + 2]
        );

        glm::vec3 v2 = glm::vec3(
            attributes.vertices[vData2.vertex_index * 3],
            attributes.vertices[(vData2.vertex_index * 3) + 1],
            attributes.vertices[(vData2.vertex_index * 3) + 2]
        );

        glm::vec3 v3 = glm::vec3(
            attributes.vertices[vData3.vertex_index * 3],
            attributes.vertices[(vData3.vertex_index * 3) + 1],
            attributes.vertices[(vData3.vertex_index * 3) + 2]
        );

        glm::vec2 uv1 = glm::vec2(
            attributes.texcoords[vData1.texcoord_index * 2],
            attributes.texcoords[(vData1.texcoord_index * 2) + 1]
        );

        glm::vec2 uv2 = glm::vec2(
            attributes.texcoords[vData2.texcoord_index * 2],
            attributes.texcoords[(vData2.texcoord_index * 2) + 1]
        );

        glm::vec2 uv3 = glm::vec2(
            attributes.texcoords[vData3.texcoord_index * 2],
            attributes.texcoords[(vData3.texcoord_index * 2) + 1]
        );

        glm::vec3 deltaPos1 = v2 - v1;
        glm::vec3 deltaPos2 = v3 - v1;

        glm::vec2 deltaUV1 = uv2 - uv1;
        glm::vec2 deltaUV2 = uv3 - uv1;

        float r = 1.0f / ((deltaUV1.x * deltaUV2.y) - (deltaUV1.y * deltaUV2.x));
        glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
        glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

        tangents.push_back(tangent);
        tangents.push_back(tangent);
        tangents.push_back(tangent);

        bitangents.push_back(bitangent);
        bitangents.push_back(bitangent);
        bitangents.push_back(bitangent);


    }

    //Full Vertex Data
    for (int i = 0; i < shapes[0].mesh.indices.size(); i++) {
        tinyobj::index_t vData = shapes[0].mesh.indices[i];

        int pos_offset = (vData.vertex_index * 3);
        int normal_offset = (vData.normal_index * 3);

        //For vertex position
        fullVertexData.push_back(  //For X
            attributes.vertices[
                pos_offset
            ]);

        fullVertexData.push_back(  //For y
            attributes.vertices[
                pos_offset + 1
            ]);

        fullVertexData.push_back(  //For z
            attributes.vertices[
                pos_offset + 2
            ]);

        //Normal Map (Contains 3 float)

        fullVertexData.push_back(  //Component A
            attributes.normals[
                normal_offset
            ]);

        fullVertexData.push_back( //Component B
            attributes.normals[
                normal_offset + 1
            ]);

        fullVertexData.push_back(  //Component C
            attributes.normals[
                normal_offset + 2
            ]);

        //UV Coordinate

        fullVertexData.push_back(   // For U
            attributes.texcoords[
                vData.texcoord_index * 2
            ]
        );
        fullVertexData.push_back(   // For V
            attributes.texcoords[
                (vData.texcoord_index * 2) + 1
            ]
        );

        //Tangents
        fullVertexData.push_back(
            tangents[i].x
        );

        fullVertexData.push_back(
            tangents[i].y
        );

        fullVertexData.push_back(
            tangents[i].z
        );

        //Bitangents
        fullVertexData.push_back(
            bitangents[i].x
        );

        fullVertexData.push_back(
            bitangents[i].y
        );

        fullVertexData.push_back(
            bitangents[i].z
        );


    }

    //For Shaders
    this->shader->initialize();
}

//Texture Initialize and with Normal
void Player::loadTexture()
{
    int img_width, img_height, colorChannel;
    stbi_set_flip_vertically_on_load(true);


    std::string texturePath = ObjectTextureManager::getInstance()->getTexturePath(this->name);
    this->tex_bytes =
        stbi_load(texturePath.c_str(),
            &img_width,
            &img_height,
            &colorChannel,
            0);

    //Generate Texture
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glGenTextures(1, &this->texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->texture);



    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB, //RGB since no alpha channel in JPG file
        img_width,
        img_height,
        0,
        GL_RGB, //RGB since no alpha channel in JPG file
        GL_UNSIGNED_BYTE,
        tex_bytes
    );

    //GenerateMipMap for performance
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(this->tex_bytes);


//Normal Texture
    int normImg_width, normImg_height, normColorChannel;
    stbi_set_flip_vertically_on_load(true);


    std::string normPath = ObjectTextureManager::getInstance()->getTexturePath(this->name + "Normal");
    this->norm_bytes =
        stbi_load(normPath.c_str(),
            &normImg_width,
            &normImg_height,
            &normColorChannel,
            0);

    //Generate Texture
    glGenTextures(1, &this->normTexture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, this->normTexture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGB, //RGB since no alpha channel in JPG file
        normImg_width,
        normImg_height,
        0,
        GL_RGB, //RGB since no alpha channel in JPG file
        GL_UNSIGNED_BYTE,
        norm_bytes
    );

    //GenerateMipMap for performance
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(this->norm_bytes);
}

//Buffer Inititalize
void Player::loadBuffer()
{
    //Buffer Setup

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GLfloat) * fullVertexData.size(),
        //Data of the Array
        fullVertexData.data(),
        GL_DYNAMIC_DRAW
    );

    //For Vertex Position
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        14 * sizeof(float),
        (void*)0
    );

    GLintptr normPtr = 3 * sizeof(GLfloat);
    GLintptr uvPtr = 6 * sizeof(GLfloat);
    GLintptr tangentPtr = 8 * sizeof(GLfloat);
    GLintptr bitangentPtr = 11 * sizeof(GLfloat);

    //Normal Pointer
    glVertexAttribPointer(
        1, //Normal
        3, //x,y,z
        GL_FLOAT,
        GL_TRUE,
        14 * sizeof(float),
        (void*)normPtr
    );

    //UV Map
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        14 * sizeof(float),
        (void*)uvPtr
    );

    glVertexAttribPointer(
        3,
        3,
        GL_FLOAT,
        GL_FALSE,
        14 * sizeof(float),
        (void*)tangentPtr
    );

    glVertexAttribPointer(
        4,
        3,
        GL_FLOAT,
        GL_FALSE,
        14 * sizeof(float),
        (void*)bitangentPtr
    );


    glEnableVertexAttribArray(4);  //Bitangent
    glEnableVertexAttribArray(3);  //Tangent
    glEnableVertexAttribArray(2);  //UV MAP
    glEnableVertexAttribArray(1);  //Normal Map
    glEnableVertexAttribArray(0);  //Vertex Pos

    //Bind Everything
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}


/*This Function compute the vector of the light where 
it is supposed to be shining upon*/
void Player::updateLightForward()
{
    glm::vec3 origShipPos = this->shipTransform * glm::vec4(0, 0, 0, 1);

    glm::mat4 shipForwardMat = glm::translate(this->shipTransform, glm::vec3(0, 0, 1));
    glm::vec3 shipForwardPos = shipForwardMat * glm::vec4(0, 0, 0, 1);

    glm::vec3 lightForwardPos = glm::normalize(shipForwardPos - origShipPos);

    light->setLightPos(lightForwardPos);
    
    
}

/*Player Movement Control and update*/
void Player::playerMovement()
{
    currTime = glfwGetTime();
    deltaTime = currTime - lastTime;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        shipTransform = glm::translate(shipTransform, glm::vec3(0, 0, -0.5f));
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        shipTransform = glm::translate(shipTransform, glm::vec3(0, 0, 0.5f));
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        shipTransform = glm::rotate(shipTransform, glm::radians(SHIP_ROTATION_SPEED), glm::vec3(0, 1.f, 0));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        shipTransform = glm::rotate(shipTransform, glm::radians(SHIP_ROTATION_SPEED), glm::vec3(0, -1.f, 0));
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        shipTransform = glm::rotate(shipTransform, glm::radians(SHIP_ROTATION_SPEED), glm::vec3(1.0f, 0, 0));
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        shipTransform = glm::rotate(shipTransform, glm::radians(SHIP_ROTATION_SPEED), glm::vec3(-1.0f, 0, 0));
    }

    lastTime = currTime;
    
}

// Handle Camera State function
void Player::updateCamera()
{
	cameraSwitch();
	if (currCam == Perspective) {
        perspCam->RotateCam(this->window, this->shipTransform);
        perspCam->newCamPos(this->shipTransform);
	}

    else if (currCam == Orthographic) {
        orthoCam->camPanning(this->window, glm::vec3(this->shipTransform * glm::vec4(0, 0, 0, 1)));
       // orthoCam->camPanning(this->window, glm::vec3(0, 0, 1));
    }
    
}


// Handle Light State function
void Player::updateLight()
{
    lightSwitch();
    if (SwitchManager::getInstance()->isShipLightActive()) {
        this->updateLightForward();
    }

}

//Update Function
void Player::update()
{
    /*Prevent Any Movement if Orthographic was on*/
    if (currCam == Perspective) {
        playerMovement();
    }
    updateLight();
	updateCamera();

}

//Draw Function
void Player::draw()
{
    float time = glfwGetTime();

    //Shader use
    glUseProgram(shader->getShaderProg());
    shader->transformUpdate(this->shipTransform);

    shader->projectionUpdate(retrieveCamProj());
    shader->viewUpdate(retrieveCamMat());
    
    glActiveTexture(GL_TEXTURE0);
    shader->textureUpdate(texture, "tex0", 0);
    glActiveTexture(GL_TEXTURE1);
    shader->textureUpdate(normTexture, "norm_tex", 1);

    shader->LightUpdate(light);
    shader->cameraUpdatePos(perspCam->getCameraPos());

    glUseProgram(shader->getShaderProg());

    //Draw of Obj
    glBindVertexArray(VAO); // Render on the active
    glDrawArrays(GL_TRIANGLES, 0, fullVertexData.size() / 14);
   

}