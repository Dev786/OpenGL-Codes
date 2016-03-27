#pragma once
#include<math.h>
#include<freeglut.h>


//Player

class position
{
public:float x;
	   float y;
};


class bullet {

public: float x;
		float y;
		float originalX;
		float originalY;
		bool dead;
		bool ready;

		bullet()
		{
			this->x = 0;
			this->y = 0;
			this->originalX = 0;
			this->originalY = 0;
		}

		bullet(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		void instantiate(float x, float y)
		{
			this->x = x;
			this->y = y;
		}
		void drawBullet()
		{
			
			for (int i = 0; i < 360; i++)
			{
				float ang = (3.14 / 180)*i;
				float xP = x + cos(ang);
				float yP = y + sin(ang);

				glBegin(GL_LINES);
				glVertex2f(x, y);
				glVertex2f(xP,yP);
				glEnd();
			}
		}

		void shot(int sHeight)
		{
			y++;
			if (y > (sHeight+10))
			{
				dead = 0;
			}
		}

		void reset()
		{

		}

};





class stack
{
private: bullet b[30];
		 int tos = -1;

public:	 void instatiateBullet(float x, float y)
	{
		for (int i = 0; i < 30; i++)
		{
			b[i].instantiate(x, y);
		}
	}

		 void pushBullet(float x, float y)
		 {
			 
			 for (int i = 0; i < 30; i++)
			 {
				 if (b[i].dead)
				 {
					 b[i].instantiate(x, y);
					 b[i].dead = false;
					 b[i].ready;
					 ++tos;
				 }
			 }
		 }

		 void popBullet()
		 {
			 for (int i = 0; i < 30; i++)
			 {
				 if (b[i].ready)
				 {
					 tos--;
				 }
			 }
		 }
};




class player
{
private: position playerPos;
		 float width;
		 float fireX;
		 float fireY;
		 float height;
		 bool insB;
		 int i = 0;
		 bullet b;

public: player()
		{
			playerPos.x = 0;
			playerPos.y = 0;
			width = 0;
			height = 0;
			insB = false;
		}
		player(position pos, float width, float height)
		{
			this->playerPos.x = pos.x;
			this->playerPos.y = pos.y;
			this->width = width;
			this->height = height;
		}

		void drawPlayer()
		{

			glPushMatrix();
	
			glTranslatef(this->playerPos.x,this->playerPos.y,0);

			if (insB&&i == 1)
			{
				b.instantiate(0, height + 4);
				b.drawBullet();
				b.shot(500);
				if (b.dead)
				{
					insB = false;
				}
			}

			glColor3f(1, 0, 0);
			glBegin(GL_QUADS);
			glVertex2f(-width, -height);
			glVertex2f(width, -height);
			glVertex2f(width, height);
			glVertex2f(-width, height);

			glVertex2f(-4, height);
			glVertex2f(4, height);
			glVertex2f(4, height+4);
			glVertex2f(-4, height+4);
			glEnd();

			glPopMatrix();
			
		}

		void initialisePlayer(position playerPos, float width, float height)
		{
			this->playerPos.x = playerPos.x;
			this->playerPos.y = playerPos.y;
			this->width = width;
			this->height = height;
		}

		void MovePlayer(int x, int y)
		{
			this->playerPos.x += x;
			this->playerPos.y += y;
		}


		void shot()
		{
			insB = true;
			this->i = 1;
		}

};