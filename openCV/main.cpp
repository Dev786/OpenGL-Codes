
#include<iostream>
#include<freeglut.h>
#include"parts.h"
#include<conio.h>
RoboBase r;
int SCREEN_HEIGHT = 250;
int SCREEN_WIDTH = 250;

bool init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();



	glViewport(0, 0, SCREEN_WIDTH*2, SCREEN_HEIGHT*2);
	glOrtho(-SCREEN_WIDTH / 2, SCREEN_WIDTH / 2, -SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2,-1000,1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	GLenum error = glGetError();

	if (error != GL_NO_ERROR)
	{
		return false;
	}

	return true;
	
}

void reshape(int w , int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	glOrtho(-w,w, -h, h, -1000, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void render()
{

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	r.drawBase(0, -100, 0);
	glutSwapBuffers();
	glutPostRedisplay();
	Sleep(100);
}



void main(int argc, char ** argv)
{
	glutInitContextVersion(2, 1);
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(SCREEN_WIDTH*2, SCREEN_HEIGHT*2);
	glutCreateWindow("CRAZY");
	if (!init())
	{
		return;
	}

	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return;
}
