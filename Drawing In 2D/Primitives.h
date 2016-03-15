#pragma once

#include<freeglut.h>

void setColor(float r,float g, float b)
{
	glColor3f(r, g, b);
}

void DisplayTriangle(float x, float y, float h,float w)
{
	glBegin(GL_TRIANGLES);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f((x + w) / 2, y + h);
	glEnd();
}


void DisplayRectangle(float x, float y, float h, float w)
{
	glBegin(GL_QUADS);
	glVertex2f(x, y);
	glVertex2f(x + w, y);
	glVertex2f(x + w, y + h);
	glVertex2f(x, y + h);
	glEnd();
}

void DisplayLine(float x1, float y1, float x2, float y2)
{
	glBegin(GL_LINES);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glEnd();
}


//Character


void PrintOnScreen(char *String, void * format,int x, int y)
{
	
	setColor(0, 1, 1);
	glRasterPos2f(x, y);
	char *c = String;
	
	while (*c != NULL)
	{
		glutBitmapCharacter(format, *c++);
	}
}