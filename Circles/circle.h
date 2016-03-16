#pragma once
#include<freeglut.h>

void circle(float centerX, float centerY, float Radius)
{

	glClearColor(1, 1, 1, 0); //set the backgroung to black

	glPointSize(2);
	int ch = rand() % 3;

	for (float r = 0; r <= 360; r+=0.5)
	{
		float rad = (3.14 / 180)*r;
		float x = Radius*cos(rad)+centerX;
		float y = Radius*sin(rad)+centerY;
		/*glBegin(GL_LINES);
		glVertex2f(centerX, centerY);
		glVertex2f(x, y);
		glEnd();
		*/
		glBegin(GL_POINTS);
		glVertex2f(x, y);
		glEnd();

		
			glFlush();
	}

}


void TooManycircle(float centerX, float centerY, float Radius)
{

	glClearColor(1, 1, 1, 0); //set the backgroung to black

	for (float r = 0; r <= 360; r+=30)
	{
		

		float rad = (3.14 / 180)*r;
		float x = Radius*cos(rad)+centerX;
		float y = Radius*sin(rad)+centerY;
		circle(x, y, 0.5);
			glEnd();

	}
}