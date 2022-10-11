#include "OrthographicCamera.h"
#include <iostream>

using namespace std;

//Constructor = creating projection comp and set defined var.
OrthographicCamera::OrthographicCamera()
{
	//Pre-Defined Settings == Defined by the xand y axis of the map
	//The Outline would prefer to be squarish
	this->projection = glm::ortho(
		-1000.0f,  //LeftMost
		1000.0f,  //RightMost
		-1000.0f,  //bottomMost
		1000.0f,  //topMost 
		0.01f,  //Z-Near
		140000.0f   //Z-Far = can be adjusted 
	);

	this->cameraPos = glm::vec3(15.0f, 15.0f, 3.0f);
	this->distance = 100000.0f;
	updateCamera();
}

glm::mat4 OrthographicCamera::getProjection()
{
	return this->projection;
}

//update the pos of the based on the ship pos
void OrthographicCamera::updatePosition(glm::vec3 shipPos)
{

	//Set this as Center
	this->Center = shipPos;
	this->cameraPos = glm::vec3(shipPos.x, shipPos.y - distance, shipPos.z);

	
	updateCamera();
}

//retrieve the position of the ship and panning on top with offset
void OrthographicCamera::camPanning(GLFWwindow* window, glm::vec3 shipPos)
{
	//Insert Solution Here
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		this->zOffset += PANNING_SPEED;
	}

	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		this->zOffset += -PANNING_SPEED;
	}

	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		//cout << xOffset << endl;
		this->xOffset += PANNING_SPEED;
	}

	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		this->xOffset += -PANNING_SPEED;
	}

	//Pos-update
	this->cameraPos = glm::vec3(shipPos.x + xOffset, shipPos.y + distance, shipPos.z + zOffset);
	//this->cameraPos = glm::vec3(shipPos.x, shipPos.y + distance, shipPos.z);
	this->Center = glm::vec3(shipPos.x + xOffset, shipPos.y, shipPos.z + zOffset + 0.01f);



	//Any after change for the cam and center should these, for updatiing view matrix;
	updateCamera();
}

//Reset the offset
void OrthographicCamera::camPanningReset()
{
	this->xOffset = 0;
	this->zOffset = 0;
}
