#include<iostream>
#include<freeglut.h>

#include"obj.h"
int SCREEN_WIDTH = 500;
int SCREEN_HEIGHT = 500;

object single(100, 400);
int newX = 0;
int newY = 0;
bool init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glOrtho(0, SCREEN_WIDTH,0,SCREEN_HEIGHT,-100,100);

	glClearColor(0, 0, 0, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLenum err = glGetError();

	if (err != GL_NO_ERROR)
		return false;

	return true;
}

void reshape(int w, int h)
{

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	glOrtho(0, w, 0,h, -100, 100);

	glClearColor(0, 0, 0, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	single.draw();
	
	glutSwapBuffers();

	glutPostRedisplay();
}

void mouseFun(int b, int s, int x, int y)
{

}

void MouseMotion(int x, int y)
{
	if ((single.x - x) < 0)
	{
		single.move(1, x);

	}
	else if((single.x - x)>0)
	{
		single.move(-1, x);

	}
	std::cout << " x: " << x << " y: " << y<<std::endl;
}


int main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("mouse Motion");

	if (!init())
		return -1;


	glutMouseFunc(mouseFun);
	glutPassiveMotionFunc(MouseMotion);
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}
