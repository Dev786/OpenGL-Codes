#pragma once
#include<math.h>
#include<freeglut.h>

class car {

private:int ang = 0;
public: car() {};
		void drawCar()
		{

			glPushMatrix();
			glScalef(1.5, 1.5, 1.5);
			glBegin(GL_QUADS);
			//front
			glColor3f(1, 0, 0);
			glVertex3f(-100, -10, -50);
			glVertex3f(100, -10, -50);
			glVertex3f(100, 10, -50);
			glVertex3f(-100, 10, -50);

			//back
			glVertex3f(-100, -10, 50);
			glVertex3f(100, -10, 50);
			glVertex3f(100, 10, 50);
			glVertex3f(-100, 10, 50);


			//left
			glVertex3f(-100, -10, -50);
			glVertex3f(-100, -10, 50);
			glVertex3f(-100, 10, 50);
			glVertex3f(-100, 10, -50);

			//right
			glVertex3f(100, -10, -50);
			glVertex3f(100, -10, 50);
			glVertex3f(100, 10, 50);
			glVertex3f(100, 10, -50);

			//top
			glColor3f(0.5, 0.5, 0.5);
			glVertex3f(-100, 10, -50);
			glVertex3f(100, 10, -50);
			glVertex3f(100, 10, 50);
			glVertex3f(-100, 10, 50);

			//bottom
			glColor3f(0.5, 0.5, 0.5);
			glVertex3f(100, -10, -50);
			glVertex3f(100, -10, 50);
			glVertex3f(-100, -10, 50);
			glEnd();

			

			//top part
			glColor3f(1, 1, 0);
			
			glBegin(GL_QUADS);

			glVertex3f(-75, 10,-50);
			glVertex3f(75, 10, -50);
			glVertex3f(50, 30, -50);
			glVertex3f(-55, 30, -50);

			glVertex3f(-75, 10, 50);
			glVertex3f(75, 10, 50);
			glVertex3f(50, 30, 50);
			glVertex3f(-55, 30, 50);

			glEnd();

			
			glColor3f(1, 1, 1);

			//Glass
			glBegin(GL_QUADS);

			glVertex3f(-75, 10, -50);
			glVertex3f(-75, 10, 50);
			glVertex3f(-55, 30, 50);
			glVertex3f(-55, 30, -50);

			glVertex3f(75, 10, -50);
			glVertex3f(75, 10, 50);
			glVertex3f(50, 30, 50);
			glVertex3f(50, 30, -50);
			glEnd();


			//roof
			glColor3f(0.5, 0.5, 0.5);
			glBegin(GL_QUADS);
			glVertex3f(-55, 30, -50);
			glVertex3f(-55, 30, 50);
			glVertex3f(50, 30, 50);
			glVertex3f(50, 30, -50);
			glEnd();

			

			//head lights
			glColor3f(0.5, 0.5, 0.5);
			glBegin(GL_QUADS);
			glVertex3f(100, -10, -50);
			glVertex3f(100, -10, 50);
			glVertex3f(100, 10, 50);
			glVertex3f(100, 10, -50);
			glEnd();

			//hlight small
			glColor3f(0, 1, 0);
			glBegin(GL_QUADS);
			glVertex3f(100, -2.5, -25);
			glVertex3f(100, -2.5, 25);
			glVertex3f(100, 2.5, 25);
			glVertex3f(100, 2.5, -25);
			glEnd();

			//Wheels
			glColor3f(1, 1, 1);
			wheels(-60, -10, -50,15);
			wheels(60, -10, -50, 15);
			wheels(-60, -10, 50, 15);
			wheels(60, -10, 50, 15);

			glPopMatrix();
		

			
		}

		void drawCarFloor()
		{

			drawCar();
			glColor3f(0, 1, 1);
			glPushMatrix();
			glScalef(1.5, 1.5, 1.5);
			floor();
			glPopMatrix();
		}
		void floor()
		{
			glBegin(GL_QUADS);
			glVertex3f(-200, -25, -200);
			glVertex3f(200, -25, -200);
			glVertex3f(200, -25, 200);
			glVertex3f(-200, -25, 200);
			glEnd();
		}
		void wheels(float x, float y,int z,float r)
		{
			for (float i = 0; i <= 360; i+=0.25)
			{
				float angr = i*(3.14 / 180);
				float xR = x+r * cos(angr);
				float yR = y+r * sin(angr);
				
				glBegin(GL_LINES);
				glVertex3f(x, y, z);
				glVertex3f(xR, yR, z);
				glEnd();
			}
		}


		
};