#include "LineRenderer.h"

LineRenderer::LineRenderer(glm::vec3 P1, glm::vec3 P2, float Length)
{
	this->P1 = P1;
	this->P2 = P2;
	this->length = Length;
}

void LineRenderer::updatePos(glm::vec3 P1, glm::vec3 P2)
{
	this->P1 = P1;
	this->P2 = P2;

}

void LineRenderer::draw()
{
	//Plan #1
	//Render them using glLines
	glBegin(GL_LINE);
	glVertex3f(P1.x, P1.y, P1.z);
	glVertex3f(P2.x, P2.y, P2.z);
	glEnd;
	
	//glRasterPos3fv

	//Plan #2
	//Hard Code Everything

	/*glm::vec3 Center = ((P1 + P2)/ 0.5f);
	GLfloat  cXPos = Center.x;
	GLfloat  cYPos = Center.y;
	GLfloat  cZPos = Center.z;

	GLfloat halfLength = length * 0.5f;	

	GLfloat vertices[4] = {

	}*/

}
