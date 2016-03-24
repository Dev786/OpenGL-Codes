#pragma once
#include<iostream>
#include<math.h>
#include<freeglut.h>
#include<il.h>


class LTexture
{

private: GLuint TextureID;
		 GLuint TextureWidth;
		 GLuint TextureHeight;


public: LTexture();
		~LTexture();
		float originalX;
		float originalY;
		float width;
		float height;
		float x;
		float radius;
		bool rot;
		float y;
		float angle;
		float angC;
		void freeTexture();
		bool loadTexture(GLuint *pixel, GLuint width, GLuint height);
		bool loadTextureFromImage(std::string path);
		void render();
		GLuint getTextureID();
		GLuint getTextureWidth();
		void rotate();
		GLuint getTextureHeight();
		void setWH(int w, int h);
		void setInitialPosition();
		void moveIt();
		void reset();

};


LTexture::LTexture()
{
	TextureID = 0;
	TextureHeight = 0;
	TextureWidth = 0;
	x = 0;
	y = 0;
	rot = true;
	angC = rand() % 360;
	radius = 3;

}

LTexture::~LTexture()
{
	freeTexture();
}

void LTexture::freeTexture()
{
	if (TextureID != 0)
	{
		glDeleteTextures(1, &TextureID);
		TextureID = 0;
	}

	TextureHeight = 0;
	TextureWidth = 0;
}


bool LTexture::loadTexture(GLuint *pixel, GLuint width, GLuint height)
{

	freeTexture();
		TextureWidth = width;
		TextureHeight = height;

		glGenTextures(1, &TextureID);
		glBindTexture(GL_TEXTURE_2D, TextureID);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, NULL);

		GLenum error = glGetError();

		if (error != GL_NO_ERROR)
		{
			std::cout << "/nUnable To load Texture"<<std::endl;
			return false;
		}

		return true;
}


void LTexture::setInitialPosition()
{
	this->originalX = x;
	this->originalY = y;
	angle = 0;
}


bool LTexture::loadTextureFromImage(std::string path)
{
	ILboolean textureLoaded = false;
	ILuint ImgId = 0;

	ilGenImages(1, &ImgId);
	ilBindImage(ImgId);

	ILboolean success = ilLoadImage((ILstring)path.c_str());

	if (!success)
	{
		cout << "\nError Loading File";
		return false;
	}

	if (success == IL_TRUE)
	{

		bool converted = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
		if (converted)
		{
			textureLoaded = loadTexture((GLuint *)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
		}

		ilDeleteImages(1, &ImgId);

	}
	

	

	return textureLoaded;

}


void LTexture::render()
{
	if (TextureID != 0) {
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	glPushMatrix();
	
	glTranslatef(x, y, 0);

	glBindTexture(GL_TEXTURE_2D, TextureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 0); glVertex2f(-width, -height);
	glTexCoord2f(1, 0); glVertex2f(width, -height);
	glTexCoord2f(1, 1); glVertex2f(width, height);
	glTexCoord2f(0, 1); glVertex2f(-width, height);
	glEnd();

	glPopMatrix();
}

}

GLuint LTexture::getTextureID()
{
	return TextureID;
}

GLuint LTexture::getTextureWidth()
{
	return TextureWidth;
}




void LTexture::setWH(int w, int h)
{
	this->width = w;
	this->height = h;
}


void LTexture::rotate()
{
	if (TextureID != 0) {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		if (angle > 70)
			rot = false;
		
		if (angle < -70)
			rot = true;

		if (rot)
		{
			angle++;
		}
		else
		{
			angle--;
		}


		if (angle == 0)
			Sleep(30);


		glPushMatrix();

		glTranslatef(x, y, 0);
		glRotatef(angle, 0, 1, 0);
		glRotatef(angle, 1, 0, 0);
		glRotatef(angle, 0, 0, 1);

		glBindTexture(GL_TEXTURE_2D, TextureID);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(-width, -height);
		glTexCoord2f(1, 0); glVertex2f(width, -height);
		glTexCoord2f(1, 1); glVertex2f(width, height);
		glTexCoord2f(0, 1); glVertex2f(-width, height);
		glEnd();

		glPopMatrix();
	}
}

GLuint LTexture::getTextureHeight()
{
	return TextureHeight;
}



void LTexture::moveIt()
{

	float Rc = angC*(3.14 / 180);

	x += radius*cos(Rc);
	y += radius*sin(Rc);


	if (TextureID != 0) {
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		if (angle > 70)
			rot = false;

		if (angle < -70)
			rot = true;

		if (rot)
		{
			angle++;
		}
		else
		{
			angle--;
		}




		glPushMatrix();
		glTranslatef(x, y, 0);
	
		glBindTexture(GL_TEXTURE_2D, TextureID);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(-width, -height);
		glTexCoord2f(1, 0); glVertex2f(width, -height);
		glTexCoord2f(1, 1); glVertex2f(width, height);
		glTexCoord2f(0, 1); glVertex2f(-width, height);
		glEnd();

		glPopMatrix();

		angC++;
	}
}









void LTexture::reset()
{
	this->x = originalX;
	this->y = originalY;
}