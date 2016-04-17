#include<iostream>
#include<conio.h>
#include<il.h>
#include<freeglut.h>
#include "LTexture.h"

int SCREEN_WIDTH = 500;
int SCREEN_HEIGHT = 500;

LTexture texture;


bool init()
{

	glClearColor(0, 0, 0, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glOrtho(0, 5, 0, 5, -10, 10);
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);


	GLenum error = glGetError();
	
	if (error != GL_NO_ERROR)
	{
		return false;
	}

	ilInit();
	ilClearColor(255, 255, 255, 000);

	ILenum err = ilGetError();
	if (err != IL_NO_ERROR)
	{
		return false;
	}

	return true;
}



void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 5, 0, 5, -10, 10);
	glViewport(0, 0, w, h);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}


void render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	texture.rotate();

	glutSwapBuffers();

	glutPostRedisplay();
	Sleep(20);

}


bool loadMedia()
{
	if (!texture.loadImageToTexture("a.jpg"))
			return false;
	
	return true;
}

int main(int argc,char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("texture");

	if (!init())
		return false;

	if (!loadMedia())
	{
		std::cout << "Error loading media";
		_getch();
	}

	glutReshapeFunc(reshape);
	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
}