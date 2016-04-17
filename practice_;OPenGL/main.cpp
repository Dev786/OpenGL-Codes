#include<iostream>
#include<conio.h>
#include<freeglut.h>
#include<IL\ilu.h>
#include<IL\il.h>
#include"Header.h"

#define MAX 80
Texture tex[MAX+1];
float life[MAX] = { 1 };
int x = 0;
int y = 500;
bool init()
{
	glClearColor(0, 0, 0, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	

	glViewport(0, 0, 500, 500);
	glOrtho(-100, 100, -100, 100, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	ilInit();
	ilClearColour(255, 255, 255, 000);
	ILenum err0 = ilGetError();

	if (err0 != IL_NO_ERROR)
	{
		std::cout << "\nILU error\n";
		return false;
	}

	GLenum err = glGetError();
	if (err != GL_NO_ERROR)
	{
		std::cout << "\nGL error\n";
		return false;
	}

	return true;
}


void reshape(int w, int h)
{

	glLoadIdentity();
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	glOrtho(0, 500, 500, 0, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	int i = 0;
	
	float fade = (rand()%1000)/10000+0.0000100;
	for (int i = 0; i < MAX; i++)
	{
		
		life[i] -= fade;
		tex[i].render(1, 1, 1, life[i]);
		tex[i].reset(500);
	}

	glutSwapBuffers();
	glutPostRedisplay();
}


bool loadMedia()
{
	for (int i = 0; i < MAX; i++) {
		tex[i].loadImageToTexture("snow.png");
		tex[i].setXY(x+10,(rand()%500)-500);
		x = (x + 20) % 500;;
	}


	return true;
}


int main(int argc, char ** argv)
{
	for (int i = 0; i < MAX; i++)
		life[i] = 1;
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowSize(500, 500);
	glutCreateWindow("PRACTICe");

	if (!init())
		return -1;

	if (!loadMedia())
	{
		std::cout << "\nError loading image";
		_getch();
		return -1;
	}


	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutMainLoop();
}