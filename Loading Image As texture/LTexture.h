#include<iostream>
#include <freeglut.h>

#include<il.h>

#pragma once
class LTexture
{
public:
	LTexture();
	~LTexture();
	void freeTexture();
	bool getTextureFromPixel(GLuint *pixel, GLuint width, GLuint height);
	void render(GLfloat x, GLfloat y);
	bool loadImageToTexture(std::string path);
	GLuint getTextureID() {
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
	
	void rotate();

private: 
	GLuint mTextureID;
	GLuint mTextureWidth;
	GLuint mTextureHeight;
	GLuint powerOfTwo(GLuint num);
	GLuint mImageWidth;
	GLuint mImageHeight;

	int angle;
	bool rot;
};

