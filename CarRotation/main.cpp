#include<iostream>
#include<conio.h>
#include<freeglut.h>
#include"car.h"
using namespace std;

int ang = 0;
int SCREEN_HEIGHT = 500;
int SCREEN_WIDTH = 500;

car cr;
bool init()
{
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	glViewport(0, 0, 500, 500);
	glOrtho(0, 500, 0, 500, -1000, 1000);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLenum error = glGetError();
glEnable(GL_SMOOTH);
	
	if (error != GL_NO_ERROR)
	{
		cout << "\nError in Initialisation"<<endl;
		getch();
		return false;
	}

	glTranslatef(250, 250, 0);
	return true;
}


void render()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glRotatef(-20, 0, 1,0);
	glRotatef(10, 1, 0, 0);
	cr.drawCarFloor();
	//cr.drawCar();
	glutSwapBuffers();

}

void TimerFunc(int val)
{
	render();
	glutTimerFunc(1000 / 20, TimerFunc, 0);
}

void reshape(int w, int h)
{
	glClearColor(0, 0, 0, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	glOrtho(0, w, 0, h, -1000, 1000);
	glTranslatef(w/2, h/2, 0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB|GLUT_DEPTH);
	glutInitWindowSize(500, 500);
	glutCreateWindow("Car");
	
	if (!init)
	{
		return 1;
	}

	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_SMOOTH);
	glutMainLoop();
	return 0;

}


