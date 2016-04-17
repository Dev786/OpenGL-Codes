#pragma once

#include<iostream>
#include<freeglut.h>

class stackElement
{
private: char *text;
		 float width;
		 float height;
		 

public: 
	float x;
	float y;
	stackElement();
	void setXY(int x, int y);
	void push(int x, int y,char *c);
	void pop();
	char * element;
	void setWH(int w, int h);
	void render();
};


stackElement::stackElement()
{
	this->x = 0;
	this->y = 0;
}

void stackElement::push(int x, int y,char *c)
{
	
	this->x = x;
	this->y = y;
	this->element = c;
}




void stackElement::setWH(int w, int h)
{
	this->width = w;
	this->height = h;
}

void stackElement::render()
{

	glPushMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	glTranslatef(x, y, 0);
	glColor3f(1, 1, 1);
	glBegin(GL_QUADS);
	glVertex2f(-width, -height);
	glVertex2f(width, -height);
	glVertex2f(width, height);
	glVertex2f(-width, height);
	glEnd();
	
glColor3f(1, 1, 1);

glRasterPos2i(-2, -5);

for (int i = 0; i < strlen(element); i++)
{
	glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,element[i]);
}

	glPopMatrix();


}