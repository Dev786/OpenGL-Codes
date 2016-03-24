#pragma once
#include<cstdio>
#include<il.h>
#include<ilu.h>
#include<freeglut.h>

class LTexture
{
public: LTexture();
		~LTexture();
		bool getImageFromPixel32(GLuint *pixel, GLuint width, GLuint height);
		void render(GLfloat x, GLfloat y);
		void freeTexture();
		bool loadTextureFromFile(std::string path);
		GLuint getMTextureID()
		{
			return mTextureID;
		}
		GLuint getTextureWidth()
		{
			return mTextureWidth;
		}
		GLuint getTextureHeight()
		{
			return mTextureHeight;
		}
		
private: 
	GLuint mTextureID;
	GLuint mTextureWidth;
	GLuint mTextureHeight;
};


LTexture::LTexture()
{
	mTextureID = 0;
	mTextureWidth = 0;
	mTextureHeight = 0;
}

LTexture::~LTexture()
{
	freeTexture();
}

bool LTexture::getImageFromPixel32(GLuint *pixel, GLuint width, GLuint height)
{

	freeTexture();
	mTextureHeight = height;
	mTextureWidth = width;

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, NULL);

	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		printf("\nerror in loading texture");
		return false;
	}
	return true;
}


void LTexture::render(GLfloat x, GLfloat y)
{
	if (mTextureID != 0)
	{
		
		glLoadIdentity();
		glTranslatef(x, y, 0);

		glBindTexture(GL_TEXTURE_2D, mTextureID);
		
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); glVertex2f(0, 0);
		glTexCoord2f(1, 0); glVertex2f(200, 0);
		glTexCoord2f(1, 1); glVertex2f(200, 200);
		glTexCoord2f(0, 1); glVertex2f(0, 200);
		glEnd();
	}
}

void LTexture::freeTexture()
{
	if (mTextureID != 0)
	{
		glDeleteTextures(1, &mTextureID);
		mTextureID = 0;
	}

	mTextureWidth = 0;
	mTextureHeight = 0;
}

bool LTexture::loadTextureFromFile(std::string path)
{
	bool textureLoaded = false;

	ILuint imgID = 0;
	
	ilGenImages(1, &imgID);
	ilBindImage(imgID);

	ILboolean success = ilLoadImage((ILstring)path.c_str());

	if (success == IL_TRUE)
	{
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		if (success == IL_TRUE)
		{
			textureLoaded = getImageFromPixel32((GLuint *)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
		}

		ilDeleteImages(1, &imgID);
	}

	if (!textureLoaded)
	{
		printf("\nUnable to Load");
		_getch();
	}

	return textureLoaded;

}