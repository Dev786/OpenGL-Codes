#pragma once
#include<freeglut.h>
#include<math.h>
void drawtorr(float x, float z,int radius,float y)
{

	glColor3f(1, 0, 1);
	int up = y;
	for (int i = 0; i <= 10; i++)
	{
		
		for (int j = 0; j <= 360; j++)
		{
			float ang = j*(3.14 / 180);
			float xC = x + radius*cos(ang);
			float zC = z + radius*sin(ang);
			glBegin(GL_POINTS);
			glVertex3f(xC, up, zC);
			glEnd();
		}
		up+=1;
	}

	glColor3f(1, 1, 1);
}


void cuboid(float width, float height,float depth)
{
	
	glBegin(GL_QUADS);

	//front face
	glVertex3f(-width, -height, -depth);
	glVertex3f(width, -height, -depth);
	glVertex3f(width, height, -depth);
	glVertex3f(-width, height, -depth);


	//back face
	glVertex3f(-width, -height, depth);
	glVertex3f(width, -height, depth);
	glVertex3f(width, height, depth);
	glVertex3f(-width, height, depth);

	//left face
	glVertex3f(-width, -height, -depth);
	glVertex3f(-width, -height, depth);
	glVertex3f(-width, height, depth);
	glVertex3f(-width, height, -depth);


	//Right face
	glVertex3f(width, -height, -depth);
	glVertex3f(width, -height, depth);
	glVertex3f(width, height, depth);
	glVertex3f(width, height, -depth);


	//Top face
	glVertex3f(-width, height, -depth);
	glVertex3f(width, height, -depth);
	glVertex3f(width, height, depth);
	glVertex3f(-width, height, depth);

	//Bottom face
	glVertex3f(-width, -height, -depth);
	glVertex3f(width, -height, -depth);
	glVertex3f(width, -height, depth);
	glVertex3f(-width, -height, depth);
	glEnd();

	
}




class RoboBase
{
private: float x;
		 float y;
		 int r = 10;

public: void drawBase(float x, float y,float z)
	{

		float width = 100;
		float height = 50;
		float depth = 100;

		glLoadIdentity();
		glPushMatrix();
		glTranslatef(0, height+10, 0);
		cuboid(70,100,50 );
		glLoadIdentity();
		glPushMatrix();
		glTranslatef(x, y, z);
		cuboid(width, height, depth);
		drawtorr(0, 0, 80,height);
		glPopMatrix();

		glPopMatrix();

		r += 4;
		
	}
};