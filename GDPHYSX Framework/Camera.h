#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Camera
{
public:
	Camera();
	void updateCamera();

	//Getter Function	
	glm::vec3 getCameraPos();
	glm::mat4 getViewMatrix();

	


protected:
	//Components for viewMatrix
	glm::vec3 cameraPos;
	glm::vec3 WorldUp;
	glm::vec3 Center;

	glm::mat4 viewMatrix;
	
	//camera Going Forward
	glm::vec3 direction = glm::vec3(0, 0, -1.f); //default

};

