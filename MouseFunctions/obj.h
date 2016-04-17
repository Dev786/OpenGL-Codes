#pragma once
#include<math.h>
#include<freeglut.h>


class object
{
public: int x, y;

		object(int x, int y)
		{
			this->x = x;
			this->y = y;

		}
		void move(int i,int nextX)
		{
			int temp = this->x;

			while (this->x!=nextX) {
				
				this->x += i;

			}
		}
		void draw()
		{
			glLoadIdentity();
			glBegin(GL_QUADS);
			glVertex2f(this->x, this->y);
			glVertex2f(this->x+40, this->y);
			glVertex2f(this->x+40, this->y+40);
			glVertex2f(this->x, this->y + 40);
			glEnd();

			glFlush();
		}

};