#pragma once
#include<iostream>
#include<freeglut.h>

using namespace std;


class DCube
{
public: float x, y, z;
		float d;

public: DCube(float x, float y, float z,float d)
	{
		this->x = x;
		this->z = z;
		this->y = y;
		this->d = d;
	}

	void drawCube()
	{

		glPushMatrix();
		glTranslatef(x, y, z);
		glRotatef(-20, 0, 1, 0);
		glRotatef(-10, 1, 0, 0);

		glBegin(GL_QUADS);
	
		glColor3f(1, 0, 0);
		//front face
		glVertex3f(x - d, y - d, z + d);
		glVertex3f(x - d, y + d, z + d);
		glVertex3f(x + d, y + d, z + d);
		glVertex3f(x + d, y - d, z + d);


		glColor3f(0, 0, 1);
		//back face
		glVertex3f(x - d, y - d, z - d);
		glVertex3f(x - d, y + d, z - d);
		glVertex3f(x + d, y + d, z - d);
		glVertex3f(x + d, y - d, z - d);


		glColor3f(0, 1, 0);
		//Left face
		glVertex3f(x - d, y + d, z + d);
		glVertex3f(x - d, y - d, z + d);
		glVertex3f(x - d, y - d, z - d);
		glVertex3f(x - d, y + d, z - d);


		glColor3f(0, 1, 1);
		//Right face
		glVertex3f(x + d, y + d, z + d);
		glVertex3f(x + d, y - d, z + d);
		glVertex3f(x + d, y - d, z - d);
		glVertex3f(x + d, y + d, z - d);
	

		glColor3f(1, 1, 0);
		//Top face
		glVertex3f(x - d, y + d, z + d);
		glVertex3f(x - d, y + d, z - d);
		glVertex3f(x + d, y + d, z - d);
		glVertex3f(x + d, y + d, z + d);


		glColor3f(1, 0, 1);
		//Bottom face
		glVertex3f(x - d, y - d, z + d);
		glVertex3f(x - d, y - d, z - d);
		glVertex3f(x + d, y - d, z - d);
		glVertex3f(x + d, y - d, z + d);

		glEnd();

		glPopMatrix();
	}

	void Movecube(float x, float y, float z)
	{
		this->x += x;
		this->y += y;
		this->z += z;

		glFlush();
	}

	
};