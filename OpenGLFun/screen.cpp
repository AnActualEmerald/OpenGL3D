#include "screen.h"
#include "GL\glew.h"

Screen::Screen()
{
}


Screen::~Screen()
{
}


void Screen::drawRect(float x, float y, float width, float height)
{
	glPushMatrix();
	glBegin(GL_QUADS);
	{
		glVertex2f(x, y);
		glVertex2f(x + width, y);
		glVertex2f(x + width, y + height);
		glVertex2f(x, y + height);
	}
	glEnd();
	glPopMatrix();
}

void Screen::setColor(float r, float g, float b)
{
	glColor3f(r, g, b);
}