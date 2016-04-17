#include "LTexture.h"
#include<freeglut.h>
#include<il.h>
#include<ilu.h>

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

bool LTexture::loadPixelsFromFile(std::string path)
{
	freeTexture();

	bool pixelsLoaded = false;
	ILuint imgID = 0;
	ilGenImages(1, &imgID);
	ilBindImage(imgID);

	ILboolean success = ilLoadImage((ILstring)path.c_str());

	if (success == IL_TRUE)
	{
		GLuint imgWidth = (GLuint)ilGetInteger(IL_IMAGE_WIDTH);
		GLuint imgHeight = (GLuint)ilGetInteger(IL_IMAGE_HEIGHT);

		GLuint texWidth = powerOfTwo(imgWidth);
		GLuint texHeight = powerOfTwo(imgHeight);

		if (texHeight != imgHeight && texWidth != imgWidth)
		{
			iluImageParameter(ILU_PLACEMENT, ILU_UPPER_LEFT);
			iluEnlargeImage((int)texWidth, (int)texHeight, 1);
		}

		GLuint size = texWidth * texHeight;
		mPixels = new GLuint[size];

	}
	
}


GLuint LTexture::powerOfTwo(GLuint num)
{
	if (num != 0)
	{
		num--;
		num |= (num >> 1); //Or first 2 bits
		num |= (num >> 2); //Or next 2 bits
		num |= (num >> 4); //Or next 4 bits
		num |= (num >> 8); //Or next 8 bits
		num |= (num >> 16); //Or next 16 bits
		num++;
	}

	return num;
}
