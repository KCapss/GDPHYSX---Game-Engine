#include "Model.h"

#include "SwitchManager.h"
#include "ObjectTextureManager.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//Empty Base Constructor
Model::Model()
{
    //option as base class
}

//Standard Base Constructor
Model::Model(std::string name, ObjectType objType, GLFWwindow* currWindow)
{
	this->name = name;
	this->objType = objType;
    this->window = currWindow;
    
    shader = new Shader(this->name);

    if (this->objType != SkyboxObj && this->objType != TextureAndNormals) {
        loadObj();
        if (this->objType != NoTexture) {
            loadTexture();
        }
        loadBuffer();
    }

}

/*This function use for retrieving source that will
be useful as extended class*/
void Model::retrieveSource(Light* light, PerspectiveCamera* perspCam, OrthographicCamera* orthoCam)
{
    this->light = light;
    this->perspCam = perspCam;
    this->orthoCam = orthoCam;
}


void Model::setInitialPos(glm::vec3 pos)
{
    this->objPosition = pos;
}

void Model::setInitialRotation(glm::vec3 objRot)
{
    this->objRotation = objRot;
}

void Model::setInitialScale(glm::vec3 objScale)
{
    this->objScale = objScale;
}

//Object Initialize without normals
void Model::loadObj()
{
    //Iniitalize obj points
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


    }

    //For Shaders
    shader->initialize();
}


//Texture without normals initialize;
void Model::loadTexture()
{
    //Initialize for Texture (JPG)
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
    glEnable(GL_DEPTH_TEST);
}

//Buffer Initialize
void Model::loadBuffer()
{
    //Initialize the new buffer
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(
        GL_ARRAY_BUFFER,
        sizeof(GLfloat) * fullVertexData.size(),
        fullVertexData.data(),  //Data of the Array
        GL_DYNAMIC_DRAW
    );

    //For Vertex Position
    glVertexAttribPointer(
        0,
        3,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)0
    );

    GLintptr normPtr = 3 * sizeof(GLfloat);
    GLintptr uvPtr = 6 * sizeof(GLfloat);

    //Normal Pointer
    glVertexAttribPointer(
        1, //Normal
        3, //x,y,z
        GL_FLOAT,
        GL_TRUE,
        8 * sizeof(float),
        (void*)normPtr //Offset from the start
    );

    //UV Map
    glVertexAttribPointer(
        2,
        2,
        GL_FLOAT,
        GL_FALSE,
        8 * sizeof(float),
        (void*)uvPtr //Offset from the start
    );

    if (objType != ObjectType::SkyboxObj) {
        if (objType != ObjectType::NoTexture) {
            glEnableVertexAttribArray(2);  //UV MAP
            glEnableVertexAttribArray(1);  //Normal Map
        }

        glEnableVertexAttribArray(0);  //Vertex Pos
    }
    

    //Bind Everything
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}


//Getter Function
glm::vec3 Model::retrieveCamPos()
{
    if (SwitchManager::getInstance()->retrieveCurrCam() == ActiveCam::Perspective) {
        return this->perspCam->getCameraPos();
    }

    else if (SwitchManager::getInstance()->retrieveCurrCam() == ActiveCam::Orthographic) {
        return this->orthoCam->getCameraPos();
    }
}

glm::mat4 Model::retrieveCamMat()
{
    if (SwitchManager::getInstance()->retrieveCurrCam() == ActiveCam::Perspective) {
        return this->perspCam->getViewMatrix();
    }

    else if (SwitchManager::getInstance()->retrieveCurrCam() == ActiveCam::Orthographic) {
        return this->orthoCam->getViewMatrix();
        cout << "OrthoCam" << endl;
    }
}

glm::mat4 Model::retrieveCamProj()
{
    if (SwitchManager::getInstance()->retrieveCurrCam() == ActiveCam::Perspective) {
        return this->perspCam->getProjection();
    }

    else if (SwitchManager::getInstance()->retrieveCurrCam() == ActiveCam::Orthographic) {
        return this->orthoCam->getProjection();
    }
}


/*This function will reference the one who called as reference of their point light*/
void Model::updateLight()
{
    if (!SwitchManager::getInstance()->isShipLightActive() && objType != ObjectType::TextureAndNormals)
    {
        light->setLightPos(this->objPosition);
    }
}

//update function
void Model::update()
{
    this->perspCam->updateCamera();
    this->orthoCam->updateCamera();
}

//
void Model::draw()
{
    glBindVertexArray(0);
    float time = glfwGetTime();
    //Apply Linear Transformation (Default)
    glm::mat4 identity = glm::mat4(1.0f);
    glm::mat4 transform = glm::translate(identity, this->objPosition);

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
   

    //Retrieve Delta Time Later
}

void Model::deAllocate()
{
    //delete vertex && buffers
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
}
