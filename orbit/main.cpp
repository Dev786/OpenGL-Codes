#include<freeglut.h>
#include"gravity.h"
#include<conio.h>

int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 1000;


positionV sun(500, 500, 0, 0,8000);
positionV earth(500, 350, 150,1, 1);

bool init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -100, 100);

	glClearColor(0, 0, 0, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	GLenum err = glGetError();

	if (err != GL_NO_ERROR)
	{
		return false;
	}

	return true;
}


void drawRect(positionV ob)
{
	glBegin(GL_QUADS);

	glVertex2f((ob.x - 5), (ob.y - 5));
	glVertex2f((ob.x + 5), (ob.y - 5));
	glVertex2f((ob.x + 5), (ob.y + 5));
	glVertex2f((ob.x - 5), (ob.y + 5));

	glEnd();
}


void render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	drawRect(sun);
	drawRect(earth);

	earth = gravityTo(sun, earth);
	
	glutSwapBuffers();

	Sleep(100);


	glutPostRedisplay();
}



void main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("Orbit");

	if (!init())
		return;

	glutDisplayFunc(render);
	glutMainLoop();
}