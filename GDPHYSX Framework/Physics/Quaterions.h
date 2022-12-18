#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <cmath>
enum Axis {
	X = 0,
	Y = 1,
	Z = 2
};


class Quaterions
{
public:
	
	//Quarterions
	glm::vec3 getQuarterion(glm::vec3 normalObjPos, Axis axis, float theta);
	glm::mat4 getRotationMatrix(glm::vec3 normalObjPos, glm::vec3 axisRotation, float theta);
	float retrieveSpeed(glm::vec3 Center, glm::vec3 PointContact);

	//EulerAngle
	glm::vec3 computeEuler(glm::vec3 rotationMatrix, glm::vec3 objPos);
	glm::mat4 computeMatEuler(glm::vec3 rotVec, glm::mat4 rotationMatrix, Axis axis);

private:
	
};

