#include "LTexture.h"
#include<ilu.h>


LTexture::LTexture()
{
	mTextureID = 0;
	mTextureHeight = 0;
	mTextureWidth = 0;

	mImageHeight = 0;
	mImageWidth = 0;
	angle = 0;
	rot = true;
}


LTexture::~LTexture()
{
	freeTexture();
}

void LTexture::freeTexture()
{
	if (mTextureID != 0)
	{
		glDeleteTextures(1, &mTextureID);
		mTextureID = 0;
	}

	mTextureHeight = 0;
	mTextureWidth = 0;
}

bool LTexture::getTextureFromPixel(GLuint *pixel, GLuint width, GLuint height)
{

	freeTexture();
	mTextureWidth = width;
	mTextureHeight = height;

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	glBindTexture(GL_TEXTURE_2D, NULL);

	GLenum error = glGetError();
	
	if (error != GL_NO_ERROR)
		return false;

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
		glTexCoord2f(0, 1); glVertex2f(-2.5, -2.5); 
		glTexCoord2f(1, 1); glVertex2f(2.5, -2.5);
		glTexCoord2f(1, 0); glVertex2f(2.5, 2.5);
		glTexCoord2f(0, 0); glVertex2f(-2.5, 2.5);
		glEnd();

	}
}




bool LTexture::loadImageToTexture(std::string path)
{
	bool textureLoaded = false;
	ILuint ImageID = 0;

	ilGenImages(1, &ImageID);
	ilBindImage(ImageID);

	ILboolean success = ilLoadImage((ILstring)path.c_str());


	if (success = IL_TRUE)
	{
		
		bool converted = ilConvertImage(IL_RGBA,IL_UNSIGNED_BYTE);

		if (converted)
		{

			GLuint imgWidth = (GLuint)ilGetInteger(IL_IMAGE_WIDTH);
			GLuint imgHeight = (GLuint)ilGetInteger(IL_IMAGE_HEIGHT);

			GLuint texWidth = powerOfTwo(imgWidth);
			GLuint texHeight = powerOfTwo(imgHeight);

			if (imgWidth != texWidth || imgHeight != texHeight)
			{
				iluImageParameter(ILU_PLACEMENT, ILU_UPPER_LEFT);
				iluEnlargeImage((int)texWidth, (int)texHeight, 1);
			}

			textureLoaded = getTextureFromPixel((GLuint *)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
		}

		ilDeleteImages(1, &ImageID);
	}


	if (!textureLoaded)
	{
		std::cout << "\nError Loading texture";
		return false;
	}


	return textureLoaded;

}

void LTexture::rotate()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	if (rot)
	{
		angle++;
	}
	else
	{
		angle--;
	}

	if (angle > 70)
	{
		rot = false;
	}
	
	if (angle < -70)
	{
		rot = true;
	}

	glPushMatrix();
	
	glTranslatef(2.5, 2.5, 0);
	glRotatef(angle, 0, 1, 0);

	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glBegin(GL_QUADS);
	glTexCoord2f(0, 1); glVertex2f(-2, -2);
	glTexCoord2f(1, 1); glVertex2f(2, -2);
	glTexCoord2f(1, 0); glVertex2f(2, 2);
	glTexCoord2f(0, 0); glVertex2f(-2, 2);
	glEnd();

	glPopMatrix();
}


GLuint LTexture::powerOfTwo(GLuint num)
{
	if (num != 0)
	{
		num--;

		num |= (num >> 1);
		num |= (num >> 2);
		num |= (num >> 4);
		num |= (num >> 6);
		num |= (num >> 8);
		num |= (num >> 16);
	}
}