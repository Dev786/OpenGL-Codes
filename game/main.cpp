
#include<freeglut.h>
#include "gameObjects.h"

int SCREEN_HEIGHT = 500;
int SCREEN_WIDTH = 500;
position playerPos;
player p1;

void initGameObject()
{
	//Player 
	playerPos.x = 0;
	playerPos.y = 0;
	p1.initialisePlayer(playerPos, 20, 20);
	//Player
}
bool init()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	glOrtho(-SCREEN_WIDTH,SCREEN_WIDTH,-SCREEN_HEIGHT,SCREEN_HEIGHT, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(0, 0, 0, 1);

	GLenum error = glGetError();
	
	if (error != GL_NO_ERROR)
		return false;

	return true;
}


void render()
{

	glClear(GL_COLOR_BUFFER_BIT);
//
	p1.drawPlayer();


	glutSwapBuffers();

}

void reshape(int w, int h)
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	glOrtho(-w, w, -h, h, -1, 1);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void Timer(int val)
{
	render();
	glutTimerFunc(1000 / 60, Timer, 0);
}


void specialFunc(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_DOWN:
		p1.MovePlayer(0, -2);
		break;

	case GLUT_KEY_UP:
		p1.MovePlayer(0, 2);
		break;

	case GLUT_KEY_LEFT:
		p1.MovePlayer(-2,0);
		break;

	case GLUT_KEY_RIGHT:
		p1.MovePlayer(2,0);
		break;
	case GLUT_KEY_SHIFT_L: p1.shot();

	default:
		break;
	}
}

void main(int argc, char ** argv)
{

	initGameObject();
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(SCREEN_WIDTH, SCREEN_HEIGHT);
	glutCreateWindow("game");

	if (!init)
	{
		return;
	}

	glutDisplayFunc(render);
	glutSpecialFunc(specialFunc);
	glutTimerFunc(1000 / 60, Timer, 0);
	glutReshapeFunc(reshape);
	glutMainLoop();
}