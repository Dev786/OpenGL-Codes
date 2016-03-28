#include<stdlib.h>
#include<freeglut.h>
#include<math.h>

int SCREEN_WIDTH = 1000;
int SCREEN_HEIGHT = 1000;

float theta = 45;
float dl = 20;
float x = 500, y = 80;
float length = 200;

bool init()
{

	
	glClearColor(0, 0, 0, 1);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, -100, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	GLenum erro = glGetError();

	if (erro != GL_NO_ERROR)
	{
		return false;
	}

	return true;
}


void tree(float xm ,float ym,float length,int theta)
{
	glLoadIdentity();

	if (length < 10)
		return;

	theta += 5;
	//first branch
	float theta1 = 90 - (theta / 2);
	float theta2 = 90 + (theta / 2);

	float x1 = length*cos((3.14/180)*theta1) + xm;
	float y1 = length*sin((3.14 / 180)*theta1) + ym;

	glColor3f(0, 1, 1);

	glBegin(GL_LINES);
	glVertex2f(xm, ym);
	glVertex2f(x1, y1);
	glEnd();
	glFlush();

	Sleep(100);
	//second branch
	float x2 = length*cos((3.14 / 180)*theta2) + xm;
	float y2 = length*sin((3.14 / 180)*theta2) + ym;
	

	glColor3f(1, 0, 1);
	glBegin(GL_LINES);
	glVertex2f(xm, ym);
	glVertex2f(x2, y2);
	glEnd();

	glFlush();

	Sleep(100);

	tree(x1, y1, length - dl, theta+10);
	tree(x2, y2, length - dl, theta+10);
	
	

}


void render()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_LINES);
	glVertex2f(x, y);
	glVertex2f(500, 40);
	glEnd();

	tree(x, y, length, 30);
}


void main(int argc, char ** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("TREE");

	if (!init())
	{
		return;
	}


	glutDisplayFunc(render);
	glutMainLoop();


}