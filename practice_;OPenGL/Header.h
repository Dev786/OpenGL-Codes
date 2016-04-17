#include<iostream>
#include<conio.h>
#include<freeglut.h>
#include<IL\il.h>


class Texture
{
public: 
	static int no;
	Texture();
		~Texture();
		void freeTexture();
		void render(float r, float g, float b, float alpha);
		bool loadTexture(GLuint *pixel,GLuint width,GLuint height);
		bool loadImageToTexture(std::string path);
		GLuint getTextureID();
		GLuint getTextureHeight();
		GLuint getTextureWidth();
		void drizzle()
		{
			y += (rand() % 100)/1000+0.02;
			
			int ch = rand() % 2;

				switch (ch)
			{
			case 0: x -= 0.02;
				break;
			case 1: x += 0.02;
			}
			
		}
		void setXY(float x,float y)
		{
			this->x = x;
			this->y = y;
			this->ix = x;
			this->iy = 0;
		}
		
		void reset(GLfloat maxY)
		{
			if (this->y > maxY + 10)
			{
				this->x = ix;
				this->y = iy;
			}
		}
private: GLuint TextureID;
		 GLuint TextureHeight;
		 GLuint TextureWidth;
		 float x;
		 float y;
		 float z;
		 float ix;
		 float iy;
};

Texture::Texture()
{
	TextureWidth = 0;
	TextureID = 0;
	TextureHeight = 0;
	y = 500;
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

	TextureHeight = 0;
	TextureWidth = 0;
}


bool Texture::loadTexture(GLuint *pixel, GLuint width, GLuint height)
{
	TextureWidth = width;
	TextureHeight = height;

	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixel);

	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);


	glBindTexture(GL_TEXTURE_2D, NULL);

	GLenum err = glGetError();

	if (err != GL_NO_ERROR)
	{
		std::cout << "\nError: " << glGetString(err)<<std::endl;
		return false;
	}


	return true;
}



bool Texture::loadImageToTexture(std::string path)
{	
	ILuint ImgID = 0;
	bool texture = false;

	ilGenImages(1, &ImgID);
	ilBindImage(ImgID);

	ILboolean success = ilLoadImage((ILstring)path.c_str());

	if (success == IL_TRUE)
	{
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		if (success == IL_TRUE)
		{
			texture = loadTexture((GLuint *)ilGetData(), (GLuint)ilGetInteger(IL_IMAGE_WIDTH), (GLuint)ilGetInteger(IL_IMAGE_HEIGHT));
		}
		ilDeleteImages(1, &ImgID);
	}

	if (!texture)
	{
		std::cout << "\nUnable to load texture\n";
		_getch();
	}
	return texture;
}


void Texture::render(float r, float g, float b,float alpha)
{

	glBindTexture(GL_TEXTURE_2D, TextureID);

		
		glColor4f(r,g,b,alpha);
		glBegin(GL_QUADS);
		glTexCoord2f(0, 0); 
		glVertex2f(x-10, y-10);
		glTexCoord2f(1, 0); 
		glVertex2f(x+10, y-10);
		glTexCoord2f(1, 1); 
		glVertex2f(x+10, y+10);
		glTexCoord2f(0, 1); 
		glVertex2f(x-10, y+10);
		glEnd();
	
		drizzle();
}


