#include<cstdlib>
#include "Texture.h"


GLfloat color[][3] = 
{
	{1,0,0},{0,1,0},{ 0,0,1 },{ 1,1,0 },{ 1,0,1 },{ 0,1,1 },{ 0.5,0,0 },{ 0,0.5,0 },{ 0,0,0.5 },{ 0.5,0.5,0 },{ 0,0.5,0.5 },{ 0.5,0,0.5 } };


Texture::Texture()
{
	TextureID = 0;
	TextureHeight = 0;
	TextureWidth = 0;
	for (int i = 0; i <= 200000; i++) {
		
		particle[i].z = rand()%10;
		particle[i].Life = 1;
		particle[i].LifeTime = 1;
		particle[i].xg = -0.02;
		particle[i].yg = -0.04;
		particle[i].zg = -0.01;
		particle[i].velocity = 4;
		particle[i].grav = 1;
		particle[i].xi = (float)(rand() % 500) / 5000 + 0.004;
		particle[i].yi = (float)(rand() % 500) / 5000 + 0.003;
		particle[i].zi = (float)(rand() % 500) / 5000 + 0.006;
		particle[i].r = color[(rand() % 12 / 100) * 10][(rand() % 24 / 50)*10];
		particle[i].g = color[(rand() % 24 / 50) * 10][(rand() % 12 / 100) * 10];
		particle[i].b = color[(rand() % 48 / 25) * 10][(rand() % 48 / 25)*10];
		particle[i].angle = 90;
	}

}

Texture::~Texture()
{
	freeTexture();
}

void Texture::freeTexture()
{
	if (TextureID != 0)
	{
		glDeleteTextures(1, &TextureID);
		TextureID = 0;
	}
	TextureWidth = 0;
	TextureHeight = 0;
}

bool Texture::textureFromPixel(GLuint * pixel, GLuint width, GLuint height)
{
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		std::cout << "\nError loading Pixel\n";
		return false;
	}

	return true;

}

bool Texture::LoadTextureFromPath(std::string path)
{
	bool texLoaded = false;
	ILuint imgID = 0;

	ilGenImages(1, &imgID);
	ilBindImage(imgID);

	ILboolean success = ilLoadImage((ILstring)path.c_str());

	if (success == IL_TRUE)
	{
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		if (success = GL_TRUE)
		{
			texLoaded = textureFromPixel((GLuint *)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
		}
	}

	return texLoaded;
}

void Texture::renderTexture(int i)
{
		glBindTexture(GL_TEXTURE_2D, TextureID);
		glColor4f(particle[i].r, particle[i].g, particle[i].b, particle[i].Life);
		glBegin(GL_TRIANGLE_STRIP);
		glTexCoord2f(0, 0); glVertex3f(particle[i].x - 10, particle[i].y - 10, particle[i].z);
		glTexCoord2f(1, 0); glVertex3f(particle[i].x + 10, particle[i].y - 10, particle[i].z);
		glTexCoord2f(0, 1); glVertex3f(particle[i].x - 10, particle[i].y + 10, particle[i].z);
		glTexCoord2f(1, 1); glVertex3f(particle[i].x + 10, particle[i].y + 10, particle[i].z);
		glEnd();

}


void Texture::illuminate()
{


	for (int i = 0; i < 100; i++) {
		if (particle[i].Life < 0)
			dec = false;
		else if (particle[i].Life > 1)
			dec = true;


		if (dec) {
			this->particle[i].Life -= 0.0001;
			colorFlag = 0;

		}
		else
			if (!dec)
			{
				this->particle[i].Life += 0.000001;
				colorFlag = 0;
			}

		renderTexture(i);
	}
}



void Texture::fountain()
{
	float ang = 0;
	float o = 0;
	bool inc = true;
	float xi = 0;
	for (int i = 0; i <= 100; i++)
	{
		float angR = ang*(3.14 / 180);
		float x = 250 + 40*xi;
		float y = 250 + 40* sin(angR);
		particle[i].x = x;
		particle[i].y = y;
		ang++;
		if(ang>180)
			ang = 0;
	}

	for (int i = 0;i<=100; i++) {

		if (particle[i].LifeTime >= 0.02) {
			particle[i].angle = rand() % 180;
			particle[i].x = particle[i].x + cos((3.14 / 180)*particle[i].angle)*particle[i].velocity;
			particle[i].y = particle[i].y + sin((3.14 / 180)*particle[i].angle)*particle[i].velocity - particle[i].grav*particle[i].LifeTime;

			particle[i].angle -= 1;

			particle[i].LifeTime -= 0.001;

			renderTexture(i);

			if (particle[i].LifeTime < 0.02)
			{
				particle[i].reset();
			}

			//particle[i].Life -= 0.01;

			if (particle[i].Life < 0)
				particle[i].Life = 1;
		}

		i %= 101;
	}

}



void Texture::flow()
{
	for (int i = 0; i <2000; i++)
	{
		particle[i].project();
		renderTexture(i);
	}
}