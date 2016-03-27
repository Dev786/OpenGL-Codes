#pragma once
#include<iostream>
#include<freeglut.h>

class LTexture
{

private: GLuint mTextureID;
		 GLuint mTextureHeight;
		 GLuint mTextureWidth;
public:
	LTexture();
	~LTexture();
	bool loadPixelsFromFile(std::string);
	bool loadTextureFromFileWithColorKey(std::string path, GLubyte r, GLubyte g, GLubyte b, GLubyte a = 000);
	bool loadTextureFromPixel32();
	void freeTexture();
	void render(GLfloat x, GLfloat y);
	GLuint powerOfTwo(GLuint num);
};

