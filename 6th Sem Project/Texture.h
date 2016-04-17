#pragma once
#include<iostream>
#include<math.h>
#include<freeglut.h>
#include<IL\il.h>



class position3f
{

public:
	position3f()
	{
		this->x = 0;
		this->y = 0;
		this->z = 0;
	}
	float x;
	float y;
	float z;
};

class color4f
{
public:
	color4f()
	{
		this->r = 1;
		this->g = 1;
		this->b = 1;
		this->fade = 0;
	}
	float r;
	float g;
	float b;
	float fade;
};



class Particles
{
public:	
	Particles()
	{
		this->x = (rand() % 1000) + 240;
		y = 300;
		flag = 0;
	}
	float x;
	float y;
	float z;
	float flag;
	float oa;

	float xi;
	float yi;
	float zi;

	float xg;
	float yg;
	float zg;
	int grav;
	float LifeTime ;
	float velocity;
	float Life;
	float time;

	float r;
	float g;
	float b;

	float angle;

	int rad = 0;

	void reset()
	{
		x = 1366/2;
		y = 768/2;
		LifeTime = 1;
		this->time = 0.0001;
	}

	void setXY()
	{

		x = 1366 / 2;
		y = 768 / 2;
		this->angle = rand() % 180 + 80;
		this->velocity = 0.5;
		this->grav = 1;
		this->time = 0.00001;

	}

	void project()
	{
		this->x += this->velocity*cos(this->angle);
		this->y -= -(this->velocity*sin(this->angle)) + this->grav*time;
		this->time+= 0.00001;
		if (y < 0&&x>500)
		{
			reset();
		}
	}

	void bdayXY(float x, float y,float r)
	{
		this->x = x;
		this->y = y;
		this->angle= rand()%360;
		this->r = r;
		this->oa = angle;
	}

	void bdayDance()
	{
		float angleR = (3.18 / 180)*this->angle;
		this->x += r*cos(angle);
		this->y += r*sin(angle);
		this->angle += 0.4;
	}

	float angMain()
	{
		return this->angle;
	}

};

class Texture
{
public:
	Texture();
	~Texture();
	void freeTexture();
	bool textureFromPixel(GLuint *pixel, GLuint width, GLuint height);
	bool LoadTextureFromPath(std::string path);
	void renderTexture(int i);
	void snowFall();
	void Explosion();
	void Fire();
	void fountain();
	void illuminate();
	void flow();

	void setXY(int i,float x, float y)
	{
		particle[i].bdayXY(x, y,50);
	}

	void initialise()
	{
		for (int i = 0; i <= 2000; i++)
		{
			particle[i].setXY();
		}
	}
	Particles particle[200000];



private:
	GLuint TextureID;
	GLuint TextureWidth;
	GLuint TextureHeight;
	int colorFlag;
	bool dec = true;
	
	
};





class founTainBase
{
public: 
	
		founTainBase()
		{
			
			this->angle = 30;
		}

		float x;
		float y;
		int r;
		float angle;
		void setXY(float x, float y)
		{
			this->x = x;
			this->y = y;
		}

		void rot()
		{
			float angR = angle*(3.14 / 180);
			this->x = this->x + r*cos(angR);
			this->y = this->y +r*sin(angR);
		}


		void drawFountain()
		{
			glColor3f(1, 0, 0);
			glBegin(GL_QUADS);
			glVertex2f(x - 100, y);
			glVertex2f(x + 100, y);
			glVertex2f(x + 100, y + 100);
			glVertex2f(x - 100, y + 100);
			glEnd();
		//	rot();
		}


};


