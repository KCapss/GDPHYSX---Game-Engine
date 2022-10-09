#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <iostream>
#include <vector>


//Class include
#include "Shader.h"
#include "Light.h"
#include "PerspectiveCamera.h" 
#include "OrthographicCamera.h"

enum ObjectType {
	NoTexture = 0,
	WithTexture = 1,
	SkyboxObj = 2,
	TextureAndNormals = 3
};

enum ActiveCam { Perspective = 1, Orthographic = 2 };


//This is class for general purpose in using for planet and debris
//but can be used as a Base class for player and skybox
class Model
{

public:
	Model(); //Empty 
	Model(std::string name, ObjectType objType, GLFWwindow *currWindow); //Universal Constructor of the Class

	//Setup Function
	void retrieveSource(Light* light, PerspectiveCamera* perspCam, OrthographicCamera* orthoCam); // All model have same sources
	void setInitialPos(glm::vec3 pos); //Debri Pre defined starting Pos
	void setInitialRotation(glm::vec3 objRot);
	void setInitialScale(glm::vec3 objScale);



	//Initialization Process
	virtual void loadObj();
	virtual void loadTexture();
	virtual void loadBuffer();
	//void loadShaders();


//Getter Function
	//Camera
	glm::vec3 retrieveCamPos();
	glm::mat4 retrieveCamMat();
	glm::mat4 retrieveCamProj();


	//EdgeCase Process
	/*void loadSkyboxtexture();*/

//Compute Properties
	void updateLight();

//Process
	//Switch Function
	void update();
	void draw();

	//Removing Buffer after program ends
	void deAllocate();


protected:
	//Obj information = Default
	std::string name{};
	GLFWwindow* window;


	ObjectType objType = ObjectType::NoTexture;
	ActiveCam  currCam = Perspective;
	

	//class container
	Light* light;
	Shader* shader;
	PerspectiveCamera* perspCam;
	OrthographicCamera* orthoCam;

	

protected:
	//Obj Vertex data
	std::vector<GLfloat> fullVertexData{};
	unsigned char* tex_bytes;
	GLuint texture = 0;

	//Buffer
	GLuint VAO, VBO;

	
	
protected:
	//Obj Properties
	glm::vec3 objPosition = glm::vec3(0.0f);
	glm::vec3 objScale = glm::vec3(1.0f);
	glm::vec3 objRotation = glm::vec3(0.f);

	//Animation
	GLuint currTime;
	float lastTime = 0;
	float deltaTime = 0;

	
	

};

