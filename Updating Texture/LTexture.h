#pragma once
#include<freeglut.h>

class LTexture
{
private: GLuint powerOfTwo(GLuint num);
		 GLuint mTextureID;
		 GLuint *mpixel;
		 GLuint mTextureWidth;
		 GLuint mTextureHeight;
		 GLuint mImageWidth;
		 GLuint mImageHeight;
public: 
	LTexture();
	~LTexture();
		bool lock();
		void freeTexture();
		bool unlock();
		GLuint getPixel32(GLuint x, GLuint y);
		void setPixel32(GLuint x, GLuint y, GLuint pixel);
};

LTexture::LTexture()
{
	mTextureID = 0;
	mpixel = NULL;

	mImageWidth = 0;
	mImageHeight = 0;

	mTextureWidth = 0;
	mTextureHeight = 0;
}

void LTexture::freeTexture()
{
	if (mTextureID != 0)
	{
		glDeleteTextures(1, &mTextureID);
		mTextureID = 0;
	}

	if (mpixel != NULL)
	{
		delete[] mpixel;
		mpixel = NULL;
	}

	mImageWidth = 0;
	mImageHeight = 0;
	mTextureHeight = 0;
	mTextureWidth = 0;

}

bool LTexture::lock()
{
	if (mTextureID != 0 && mpixel == NULL)
	{

	}
}

