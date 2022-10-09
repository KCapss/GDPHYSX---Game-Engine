#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Light.h"
#include <string>
using namespace std;

//#include

//Class
//Get for Transform
//Projection && View Matrix
//Texture
//Normals


#include <string>
class Shader
{

public:
	Shader(std::string name);
	void initialize();
	
	//Getter
	GLuint getShaderProg();

	//Setter
//Vertex Shader
	void transformUpdate(glm::mat4 transform);

	//Part of Camera
	void projectionUpdate(glm::mat4 projection);
	void viewUpdate(glm::mat4 viewMatrix);
	

//Fragment Shader
	void textureUpdate(GLuint texture, string varName, int layer);
	void LightUpdate(Light *refLight); //Retrieve Light Class;
	void cameraUpdatePos(glm::vec3 cameraPos);

//Normal Map
	//To be Discuss Next Meeting


private:
	std::string name;

	GLuint shaderProgram;



};

