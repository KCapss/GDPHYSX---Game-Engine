#include "LineRenderer.h"

LineRenderer::LineRenderer(glm::vec3 P1, glm::vec3 P2)
{
	this->P1 = P1;
	this->P2 = P2;
}

void LineRenderer::updatePos(glm::vec3 P1, glm::vec3 P2)
{
	this->P1 = P1;
	this->P2 = P2;

}

void LineRenderer::draw()
{
	glBegin(GL_LINE);
	glVertex3f(P1.x, P1.y, P1.z);
	glVertex3f(P2.x, P2.y, P2.z);
	glEnd;

}
