#include "Quaterions.h"
#include <cmath>
#include <math.h>
#include <iostream>

using namespace std;

glm::vec3 Quaterions::getQuarterion(glm::vec3 normalObjPos, Axis axis, float theta)
{
	glm::vec3 axisVector = glm::vec3(0);
	glm::vec4 objectPos(glm::vec3(normalObjPos), 1.0f); //Make it into Vector4

	//Determine which axis to rotate;
	if (axis == X)
		axisVector = glm::vec3(1.0f, 0, 0);

	else if (axis == Y)
		axisVector = glm::vec3(0, 1.0f, 0);

	else if (axis == Z)
		axisVector = glm::vec3(0, 0, 1.0f);


	//get the value of ABCD first
	float A = cos(glm::radians(theta/2.0f));
	float B = axisVector.x * sin(glm::radians(theta/2.0f));
	float C = axisVector.y * sin(glm::radians(theta/2.0f));
	float D = axisVector.z * sin(glm::radians(theta/2.0f));

	//Defaul Matrix Formula for Quat
	glm::mat4x4 QuaterionMatrix(
		(pow(A, 2) + pow(B, 2) - pow(C, 2) - pow(D, 2)), (2 * B * C) + (2 * A * D), (2 * B * D) - (2 * A * C), 0,
		(2 * B * C) - (2 * A * D), (pow(A, 2) - pow(B, 2) + pow(C, 2) - pow(D, 2)), (2 * C * D) + (2 * A * B), 0,
		(2 * B * D) + (2 * A * D), (2 * C * D) - (2 * A * B), (pow(A, 2) - pow(B, 2) - pow(C, 2) + pow(D, 2)), 0,
		0, 0, 0, 1

	);
	
	//Compute the Quaternion Matrix
	glm::vec4 vector4 = objectPos * QuaterionMatrix;
	glm::vec3 finalVec = glm::vec3(vector4); //Compress it into vector 3


	return finalVec;
}

glm::mat4 Quaterions::getRotationMatrix(glm::vec3 normalObjPos, glm::vec3 axisRotation, float theta)
{
	glm::vec3 axisVector = axisRotation;
	axisVector = glm::normalize(axisVector);

	glm::vec4 (glm::vec3(normalObjPos), 1.0f); //Make it into Vector4

	
	//get the value of ABCD first
	float A = cos(glm::radians(theta / 2.0f));
	float B = axisVector.x * sin(glm::radians(theta / 2.0f));
	float C = axisVector.y * sin(glm::radians(theta / 2.0f));
	float D = axisVector.z * sin(glm::radians(theta / 2.0f));

	//Defaul Matrix Formula for Quat
	glm::mat4 QuaterionMatrix(
		(pow(A, 2) + pow(B, 2) - pow(C, 2) - pow(D, 2)), (2 * B * C) + (2 * A * D), (2 * B * D) - (2 * A * C), 0,
		(2 * B * C) - (2 * A * D), (pow(A, 2) - pow(B, 2) + pow(C, 2) - pow(D, 2)), (2 * C * D) + (2 * A * B), 0,
		(2 * B * D) + (2 * A * D), (2 * C * D) - (2 * A * B), (pow(A, 2) - pow(B, 2) - pow(C, 2) + pow(D, 2)), 0,
		0, 0, 0, 1

	);

	return QuaterionMatrix;
}

float Quaterions::retrieveSpeed(glm::vec3 Center, glm::vec3 PointContact)
{
	////Normalize first for easire computation
	//glm::vec3 pointContact = glm::normalize(PointContact);
	//glm::vec3 center = glm::normalize(Center);

	//Upper Half
	float dotProduct = glm::dot(PointContact, Center );

	//Lower Half (Product of their magnitude
	float magnitude = glm::length(PointContact) * glm::length(Center); //Double Check Later

	//Combine
	//Convert first into radians
	float decimalForm = dotProduct / magnitude;
	float degrees = acosf(decimalForm);

	degrees = fmodf(degrees, 90.0f);

	if (degrees != degrees) {
		degrees = 0;
	}

	return degrees;
}



glm::vec3 Quaterions::computeEuler(glm::vec3 rotationMatrix, glm::vec3 objPos)
{

	//Setup the identity
	glm::mat4 identity = glm::mat4(1.0f);
	glm::mat4 transform = glm::translate(identity, glm::vec3(0, 0, 0)); // At Origin

	//Compute the linear transformation matrix
	transform = glm::rotate(transform, glm::radians(rotationMatrix.x), glm::vec3(1, 0, 0)); //x-axis
	transform = glm::rotate(transform, glm::radians(rotationMatrix.y), glm::vec3(0, 1, 0)); //y-axis
	transform = glm::rotate(transform, glm::radians(rotationMatrix.z), glm::vec3(0, 0, 1)); //z-axis
	
	//Apply to the Transformation Matrix to the Vertex (glm::vec4)
	glm::vec4 vec4 = transform * glm::vec4(objPos, 1.0f);
	glm::vec3 finalPos = glm::normalize(glm::vec3(vec4)); 


	return finalPos;
}

glm::mat4 Quaterions::computeMatEuler(glm::vec3 rotVec, glm::mat4 rotationMatrix, Axis axis)
{
	//Setup the identity
	
	glm::mat4 RotationMatrix = glm::mat4(1.0f);

	//Compute the linear transformation matrix
	if(axis == X)
		RotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotVec.x), glm::vec3(1, 0, 0)); //x-axis

	if (axis == Y)
		RotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotVec.y), glm::vec3(0, 1, 0)); //y-axis

	if(axis == Z)
		RotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotVec.z), glm::vec3(0, 0, 1)); //z-axis
	
	//Apply to the Transformation Matrix to the Vertex (glm::vec4)
	


	return RotationMatrix;
}
